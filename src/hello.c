#include <stdio.h>
#include "macro-machinery.h"

enumdef( state,
  RUN,PASS,FAIL
);

  
int main(){
  printf("Hello! %s\n", string_from_state(RUN) );
  printf("Hello! %s\n", string_from_state(15) );
}

