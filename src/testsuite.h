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


#include "framework.h"
#include <string.h>

#define ACUTE_PATHBUF_SIZE 1024
char acute_suite_name_buf[ACUTE_PATHBUF_SIZE];


void testsuite();

static void acute_set_suite_name(){

  size_t len = strlen(acute_main_source);
  
  ACUTE_CHECK( len<ACUTE_PATHBUF_SIZE,
	       "path buffer overflow: Suite path length can at most be (%d-1)",
	       ACUTE_PATHBUF_SIZE
	       );

  strcpy(acute_suite_name_buf,acute_main_source);
  acute_suite_name = acute_suite_name_buf;

  for (char* p = acute_suite_name_buf+len;p!=acute_suite_name_buf;p--){
    if(*p=='.') { (*p=0); break; };
    if(*p=='/') break;
  }
}

#define testsuite						\
  testsuite();							\
  static const char* acute_main_source = __FILE__;		\
  void testsuite

#define test ACUTE_SUBTEST


