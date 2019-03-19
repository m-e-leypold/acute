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


#include "runtime.h"

static int     acute_gargc;
static char**  acute_gargv;
static char*   acute_program_name;

static inline void
acute_gargs_init(int argc, char** argv){

  acute_program_name = argv[0];
  
  acute_gargc  = argc - 1;
  acute_gargv  = argv + 1;
}

static inline char*
acute_gargs_getword(){
  ACUTE_CHECK( acute_gargc>0, "out of commandline parameters" );
  char* word = *acute_gargv;
  acute_gargc--;
  acute_gargv++;
  return word;
}
