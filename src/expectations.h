#pragma once
/*
 * Acute - A C Unit Testing Environment
 * Copyright (C) 2019 M E Leypold
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "control.h"
#include "typehandlers.h"

#define EXPECT_UNREACHABLE TEST_FAIL("expected location to be unreachable")

/* EXPECT can occur in 2 forms:
 *
 *    EXPECT( a<3 );     // single conditional expression, no operand introspection
 *
 *    EXPECT( int, EQ(x*y, x/y));  // with operand inspection.
 *
 * The form with operand inspection requires
 *
 *    - a type specification (acutally the name of a method table)
 *    - the condition as one of a limited number of condition macros: EQ, NEQ, GT, ...
 *
 * The ROI for the extra restrictions: EXPECT_2 will be able to print
 * the values of the operands when the condiation fails.
 */

#define EXPECT_(N,...) ACUTE_DISPATCH2(EXPECT,N,__VA_ARGS__)
#define EXPECT(...)    EXPECT_(ACUTE_COUNT_ARGS(__VA_ARGS__),__VA_ARGS__)

#define EXPECT_1(EXPR)							\
  {									\
    if (!(EXPR))							\
      {									\
	static char* expr     = #EXPR;					\
	ACUTE_TEST_FAILCOND(expr,0);					\
      }									\
  }

/* EXPECT_2 will have to expand to a code block like the following (the example is for 
 * EXPECT( int, EQ(OP1, OP2) ) where OP1 and OP2 a two int-valued C expression):
 *
 *  {
 *    typedef int T;
 *    acute_method_table_type_for_int* methods = acute_method_table_for_int;
 *
 *    T op1 = (OP1);
 *    T op2 = (OP2);
 *   
 *     if (!(methods->equal(op1,op2))){
 *       static char* expr     = #OP1 " == " #OP1;
 *       static char* op1_expr = #OP1;
 *       static char* op2_expr = #OP2;
 *       char op1_value_image[methods->bufsize];
 *       char op2_value_image[methods->bufsize];
 *       methods->render(op1,op1_value_image,methods->bufsize);
 *       methods->render(op2,op2_value_image,methods->bufsize);
 *   
 *       ACUTE_TEST_FAILCOND
 *         (expr, "with: %s => %s; %s => %s.n",
 *          op1_expr, op1_value_image, op2_expr, op2_value_image);
 *      }
 *   }
 *
 * With a bit of squinting, it becomes obvious that the first paragraph only depends on the type,
 * and the rest only on the condition checked and the operands.
 *
 * This motivates the definition of EXPECT_2 as below (note, that
 * ACUTE_GENERATE_EXPECT_ASSERTION_##ASSERTION) actually expands to
 * ACUTE_GENERATE_EXPECT_ASSERTION_EQ(OP1,OP2) if invoked as in the
 * example -- ASSERTION contains the call arguments as well):
 */

#define EXPECT_2( TYPE, ASSERTION )			\
  { ACUTE_GENERATE_EXPECT_TYPE_SETUP(TYPE);		\
    ACUTE_GENERATE_EXPECT_CHECK_##ASSERTION;	\
  }

/* The generation of the part that depends only on the type (
 * ACUTE_GENERATE_EXPECT_TYPE_SETUP) is simple.
 */

#define ACUTE_GENERATE_EXPECT_TYPE_SETUP(TYPE)				\
  typedef ACUTE_PASTE_3(acute_operand_type,_,TYPE) acute_operand_T;	\
  ACUTE_PASTE_3(acute_method_table_type_for,_,TYPE)* acute_methods =	\
    ACUTE_PASTE_3(acute_method_table_for,_,TYPE)

/* Regarding the part that depends on operation ond operands, we can formulate (see below)
   a macro
   
     #define ACUTE_GENERATE_EXPECT_CHECK(MACRO,...)

   that takes the name of the operation (not the complete call) and the operands. But what we have is 
   an invocation

     ACUTE_GENERATE_EXPECT_CHECK_EQ(OP1,OP2)

   instead. Therefore we have to define ACUTE_GENERATE_EXPECT_CHECK_EQ
   as follows below. Every condiation macro XYZ will have to have a
   companion macro ACUTE_GENERATE_EXPECT_CHECK_##XYZ that separates
   the operation name from the operands and dispatches to
   ACUTE_GENERATE_EXPECT_CHECK.
*/

#define ACUTE_GENERATE_EXPECT_CHECK_EQ(OP1,OP2)	\
  ACUTE_GENERATE_EXPECT_CHECK(EQ,OP1,OP2)

/* ACUTE_GENERATE_EXPECT_CHECK writes the part that checks the
 * condition using the type definitions and the local method table
 * created by ACUTE_GENERATE_EXPECT_TYPE_SETUP.
 *
 * It uses the macro name MACRO, to get at the actual method to be
 * called (by expanding ACUTE_OPERATION_##MACRO) and the form of the
 * (purely hypothetical) conditional expression to be displayed in
 * case of a failure (by expanding ACUTE_EXPRESSION_IMAGE_##MACRO).
 *
 * So every  condiation macro MACRO must also have companion macros
 * ACUTE_OPERATION_##MACRO and ACUTE_EXPRESSION_IMAGE_##MACRO.
 */

#define ACUTE_EXPRESSION_IMAGE_EQ(OP1,OP2) (#OP1 " == " #OP2)
#define ACUTE_OPERATION_EQ  acute_methods->equals

#define ACUTE_GENERATE_EXPECT_CHECK(MACRO,...);				\
  									\
  /* The following beauty writes statements of the form			\
   *   acute_operand_T acute_op##N = (OP##N);					\
   * one for every operand.						\
   */									\
  ACUTE_EXPAND_CODE_ENUMERATED(ACUTE_EXPECT_EVAL_EXPR,__VA_ARGS__);	\
									\
  /* Expands to something like						\
   *   !(acute_methods->equals(op1,op2)					\
   */									\
  if (!(ACUTE_OPERATION_##MACRO						\
	(ACUTE_EXPECT_OPERAND_VALUE_LIST				\
	 (ACUTE_COUNT_ARGS(__VA_ARGS__)))))				\
    {									\
      static char* acute_expr_as_string =				\
	ACUTE_EXPRESSION_IMAGE_##MACRO(__VA_ARGS__);			\
									\
      /* The following generates code blocks to capture the expressions	\
       * for every single operand as string and render string		\
       * representations of their values. It generates statements	\
       * like the following for every operand				\
       *								\
       *    static char* acute_op##N##_expr_as_string = (#OP##N);	\
       *    char acute_op##N##_value_as_string[acute_methods->bufsize];	\
       *    acute_methods->render(					\
       *      acute_op##N,						\
       *      acute_op##N##_value_as_string,				\
       *      acute_methods->bufsize					\
       *    );								\
       */								\
      ACUTE_EXPAND_CODE_ENUMERATED					\
	(ACUTE_EXPECT_RENDER_OPERANDS,__VA_ARGS__);			\
      									\
      ACUTE_TEST_FAILCOND						\
      ( acute_expr_as_string, "with:"					\
	ACUTE_EXPAND_CODE /* generate format string */			\
	(ACUTE_EXPECT_FMT_FRAGMENT,ACUTE_COUNT_ARGS(__VA_ARGS__)) "\n",	\
	ACUTE_UNPACK	  /* generate argument list */			\
	( ACUTE_TIMES							\
	  ( ACUTE_COUNT_ARGS(__VA_ARGS__),ACUTE_EXPECT_RENDERED_OPERANDS))	\
	);								\
      }

/* Noteworthy above are "generate format strings" and "generate argument list"
 *
 * generate format strings
 * -----------------------
 *
 * The expression given there expands to the string " %s => %s;"
 * repeated once for every operand. In example: For two operands we get the format string
 * " with:  %s => %s;  %s => %s;\n".
 *
 * generate argument list
 * ----------------------
 *
 * Expands to an argumentlist containing the variable names
 *
 *   acute_op##N##_expr_as_string,acute_op##N##_value_as_string
 *
 * once for every operand. E.g. for two operands we get:
 *
 *   acute_op1_expr_as_string, acute_op1_value_as_string,
 *     acute_op2_expr_as_string, acute_op2_value_as_string
 *
 * This list is fed into the format string generated above to print
 * the values of the operands.
 */

/* The following macros are repeatedly expanded to generate the code
 * blocks where one piece of code needs to be generated for every
 * operand.
 */

#define ACUTE_EXPECT_EVAL_EXPR(N,EXPR) acute_operand_T acute_op##N = (EXPR);
#define ACUTE_EXPECT_OPERAND_VARS(N)           acute_op##N
#define ACUTE_EXPECT_OPERAND_VALUE_LIST(N)  ACUTE_TIMES(N,ACUTE_EXPECT_OPERAND_VARS)

#define ACUTE_EXPECT_RENDER_OPERANDS(N,EXPR)				\
  static char* acute_op##N##_expr_as_string = (#EXPR);			\
  char acute_op##N##_value_as_string[acute_methods->bufsize];		\
  acute_methods->render(acute_op##N,acute_op##N##_value_as_string,acute_methods->bufsize); \

#define ACUTE_EXPECT_FMT_FRAGMENT(N) " %s => %s;"
#define ACUTE_EXPECT_RENDERED_OPERANDS(N) (acute_op##N##_expr_as_string,acute_op##N##_value_as_string)

/* More expect operations ---------------------------------------------------- */


