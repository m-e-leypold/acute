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


#define ACUTE_DEFINE_EXPECT_TYPE(IDENT,TYPE,METHODS)			\
  typedef TYPE ACUTE_PASTE_3(acute_operand_type,_,IDENT);		\
  typedef ACUTE_PASTE_3(acute_method_table_type,_,METHODS) ACUTE_PASTE_3(acute_method_table_type_for,_,IDENT); \
  ACUTE_PASTE_3(acute_method_table_type_for,_,IDENT)* ACUTE_PASTE_3(acute_method_table_for,_,IDENT) = &ACUTE_PASTE_3(acute_method_table,_,METHODS)


#define ACUTE_DEFINE_METHOD_TABLE(TAG,TYPE)			\
  structdef (ACUTE_PASTE_3(acute_method_table_type,_,TYPE)){		\
    size_t bufsize;							\
    void (*render) (TYPE value, char* buffer, size_t bufsize );		\
    int  (*equals) (TYPE opd1, TYPE opd2);				\
  };									\
  static ACUTE_PASTE_3(acute_method_table_type,_,TYPE) ACUTE_PASTE_3(acute_method_table,_,TYPE)

/* ----------------------------------------------------------------------------- */

static void acute_type_int_render(int k, char* buffer, size_t bufsize ){
  snprintf(buffer,bufsize,"%d",k);
}

static int acute_type_int_equals(int j,int k){
  return j == k;
}

ACUTE_DEFINE_METHOD_TABLE(int,int) =
  {
   .bufsize = 100,
   .render  = &acute_type_int_render,
   .equals  = &acute_type_int_equals
  };

ACUTE_DEFINE_EXPECT_TYPE(int,int,int);

/* ----------------------------------------------------------------------------- */

static void acute_type_float_render(float k, char* buffer, size_t bufsize ){
  snprintf(buffer,bufsize,"%f",k);
}

static int acute_type_float_equals(float j,float k){
  return j == k;
}


ACUTE_DEFINE_METHOD_TABLE(float,float) =
  {
   .bufsize = 100,
   .render  = &acute_type_float_render,
   .equals  = &acute_type_float_equals
  };

ACUTE_DEFINE_EXPECT_TYPE(float,float,float);

