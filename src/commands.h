#pragma  once
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


#include "gargs.h"
#include "macro-machinery.h"
#include "string.h"

typedef void (*acute_command_procedure)();


structdef(acute_command_entry) {
  const char* word;
  const acute_command_procedure procedure;
};


static void acute_list_tests();
static void acute_run_tests();

acute_command_entry acute_commands [] =
  {
   { "run",  &acute_run_tests },
   { "list", &acute_list_tests },
   { 0 }
  };


static acute_command_procedure acute_get_command(){
  
  acute_command_entry* command = acute_commands;
  
  if (acute_gargc==0){
    return command->procedure;
  }
  
  char* word = acute_gargs_getword();
 
  while (command->word){
    if (strcmp(command->word,word) == 0){
      return command->procedure;
    }
    command++;
  }

  ACUTE_PANIC("unknown command: %s", word);
  return 0;
}

