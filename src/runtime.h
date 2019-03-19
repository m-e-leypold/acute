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


#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdarg.h>

#ifdef __STRICT_ANSI__
#  define ACUTE_FUNCTION 0
#else
#  ifdef __FUNCTION__
#    define ACUTE_FUNCTION 0
#  else
#    define ACUTE_FUNCTION __FUNCTION__
#  endif
#endif

static inline void
acute_panic
(
  const char* file, int line, const char* function,
  const char* cond, const char* message, ...
)
{
  fflush(stderr);

  if (cond) {
    fprintf(stderr,"%s:%d: *** CHECK/ASSERTION FAILED: %s ***\n",file,line,cond);
  } else {
    fprintf(stderr,"%s:%d: *** PANIC ***\n",file,line);
  }
  
  if (function){
    fprintf(stderr,"  in: %s()",function);
  };

  if (message){
    
    va_list ap;
    va_start(ap,message);
    if (function) fprintf(stderr,",\n");
    fprintf(stderr,"  =>  ");
    vfprintf(stderr,message,ap);
    fprintf(stderr,".\n");
    va_end(ap);	      
  } else {
    if (function) fprintf(stderr,".\n");
  }
  fprintf(stderr,"\n");
  fflush(stderr);
  abort();
}

#define ACUTE_CHECK(COND,...)					\
  do {									\
    if (!(COND))							\
      acute_panic(__FILE__,__LINE__,ACUTE_FUNCTION, #COND, __VA_ARGS__); \
  } while(0)

#define ACUTE_ASSERT(COND)						\
  do {									\
    if (!(COND))							\
      acute_panic(__FILE__,__LINE__,ACUTE_FUNCTION, #COND, 0);	\
 } while(0)


#define ACUTE_PANIC(...)						\
  acute_panic(__FILE__,__LINE__,ACUTE_FUNCTION, 0, __VA_ARGS__)


static inline void
acute_out
(
 const char* format, ...
)
{
  va_list ap;
  va_start(ap,format);
  vfprintf(stdout,format,ap);
  va_end(ap);	      
  fflush(stdout);
}

static inline void
acute_log
(
 const char* format, ...
)
{
  va_list ap;
  va_start(ap,format);
  vfprintf(stderr,format,ap);
  va_end(ap);	      
  fflush(stderr);
}

static inline void
acute_test_abort
(
  const char* file, int line, const char* function,
  const char* cond, const char* message, ...
)
{
  fflush(stderr);

  if (cond) {
    fprintf(stderr,"%s:%d: *** EXPECTATION FAILED: %s ***\n",file,line,cond);
  } else {
    fprintf(stderr,"%s:%d: *** FAILURE ***\n",file,line);
  }
  
  if (function){
    fprintf(stderr,"  in: %s()",function);
  };

  if (message){
    
    va_list ap;
    va_start(ap,message);
    if (function) fprintf(stderr,",\n");
    fprintf(stderr,"  =>  ");
    vfprintf(stderr,message,ap);
    fprintf(stderr,".\n");
    va_end(ap);	      
  } else {
    if (function) fprintf(stderr,".\n");
  }
  fprintf(stderr,"\n");
  fflush(stderr);
  abort();
}


#define ACUTE_TEST_ABORT(...)						\
  acute_test_abort(__FILE__,__LINE__,ACUTE_FUNCTION, 0, __VA_ARGS__)

#define ACUTE_TEST_FAILCOND(COND,...)					\
  acute_test_abort(__FILE__,__LINE__,ACUTE_FUNCTION, COND, __VA_ARGS__)
