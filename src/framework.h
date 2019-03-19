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


#include "runtime.h"
#include "gargs.h"
#include "commands.h"
#include "registry.h"
#include "tap.h"
#include "control.h"
#include "expectations.h"

#include <sys/types.h>
#include <unistd.h>

static const char* acute_main_source;
static const char* acute_suite_name = 0;

static void acute_set_suite_name();

void acute_init(){
  acute_set_suite_name();
}

void testsuite();

enumdef ( acute_phase,
	  NONE, COLLECT, RUN
);

acute_phase acute_current_phase = NONE;



static void acute_test_begin(){
  printf("-- running: %s\n", acute_current_test->name);
  acute_current_test->state = RUNNING;
}

static void acute_test_end(){
  if (acute_current_test->state == SUBPROCESS) {
    printf("** subprocess done: %s\n", acute_current_test->name);
    exit(0);
  } else {
    printf("-> done: %s\n", acute_current_test->name);
  
    switch(acute_current_test->state) {
    case PASSED:
      ACUTE_TAP("ok %d\n", acute_current_test->index);
      break;
    case FAILED:
      ACUTE_TAP("not ok %d\n", acute_current_test->index);
      break;
    default: break; /* XXX */
    }
  }
}

static int acute_test_done(){
  return
    acute_current_test->state != RUNNING
    && acute_current_test->state != SUBPROCESS;
}

static void acute_test_check_outcome(){
  int status = acute_current_test->status;
  if (status) {
    acute_current_test->state = FAILED;
  } else {
    acute_current_test->state = PASSED;
  }
}

static int acute_test_isolate(){
    pid_t pid = acute_current_test-> pid = fork();
  if (pid){
    ACUTE_CHECK( pid>0, "fork failed");
    pid_t pid2 = waitpid(pid,&(acute_current_test->status),0);    
    ACUTE_ASSERT( pid = pid2 );
    acute_test_check_outcome();    
    return 0;
  } else {
    acute_current_test->state = SUBPROCESS;
    printf("** subprocess: %s\n", acute_current_test->name);
    return 1;      
  }
}


#define ACUTE_SUBTEST(NAME)						\
  static acute_test_entry ACUTE_LID(acute_test);			\
  if (acute_current_phase==COLLECT) {					\
    acute_register_test(#NAME,&(ACUTE_LID(acute_test)));		\
  } else {								\
    acute_current_test = &(ACUTE_LID(acute_test));			\
  }									\
  if (acute_current_phase==RUN)						\
    for (acute_test_begin();!acute_test_done();acute_test_end())	\
      if (acute_test_isolate())						\

static void acute_collect_tests(){
  acute_current_phase = COLLECT;
  testsuite();
}


static void acute_list_tests(){
  ACUTE_CHECK( acute_gargc==0, "trailing unused commandline arguments" );
  acute_collect_tests();

  printf("file  %s\n", acute_main_source );

  if (acute_suite_name){
    printf("suite %s\n", acute_suite_name );
  }
  
  FOR_ALL_TESTS(test){
    printf("test  %s\n", test->name );
  }
}

static void acute_run_tests(){
  acute_collect_tests();

  ACUTE_TAP("1..%d\n",acute_test_count);
  
  acute_current_phase = RUN;
  testsuite();
  
  /* XXX get possible pattern, possible cmdline args */
  /* XXX select tests */
  /* XXX run selected tests */  
}


int main(int argc,char** argv){
  
  acute_gargs_init (argc,argv);
  acute_init();
  
  acute_command_procedure procedure = acute_get_command();
  procedure();
  
  return 0;
}

#define test ACUTE_SUBTEST
