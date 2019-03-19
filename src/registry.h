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

#include "macro-machinery.h"

#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>


enumdef ( acute_test_state,
	  NOTRUN, RUNNING, SUBPROCESS, PASSED, FAILED
);


structdef(acute_test_entry){
  const char* name;
  int   index;
  int   selected;
  pid_t pid;
  int   status;
  acute_test_state state;
  acute_test_entry* next;
};

static acute_test_entry* acute_current_test = 0;
static acute_test_entry* acute_test_list = 0;
static int acute_test_count = 0;

static void acute_register_test( const char* name, acute_test_entry* entry){

  if (!acute_test_list) { acute_test_list = entry; }
  
  (*entry) = (struct acute_test_entry) {
    .name     = name,
    .selected = 1,
    .pid      = 0,
    .status   = 0,
    .state    = NOTRUN,
    .next     = 0
  };

  if (acute_current_test) { acute_current_test->next = entry; }
  
  acute_current_test = entry; 
  acute_test_count++;
  entry->index = acute_test_count;
}


#define FOR_ALL_TESTS(VAR) for (acute_test_entry* VAR = acute_test_list; VAR; VAR = VAR->next)



  
