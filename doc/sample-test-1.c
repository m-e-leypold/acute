
#include "acute/testsuite.h"

void testsuite(){

  test (foo) {
    int y = -2;
    EXPECT( y*y == -4);
  }

  test (bar) {
    int x = 2;
    int y = 2;
    EXPECT (int, EQ(x*y,x*3));

    float f = 2.0;
    EXPECT (float, EQ(f*f,5.0));
  }
}

