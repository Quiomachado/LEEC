#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Complex.h"

int main(int argc, char **argv)
{
  int operation;
  double a, b;
  printf("I am an expert in complex numbers algebra!\n\n");

  if (argc < 4)
  {
    printf("Please provide a and b for a+ib being the complex you want to generate, followed by a digit between 0 and 5\n");
    exit(1);
  }
  if (argc > 4)
  {
    printf("You've entered too much data.\n");
    exit(2);
  }

  a = atof(argv[1]);
  b = atof(argv[2]);
  operation = atoi(argv[3]);
  Complex *t, *u;

  switch (operation)
  {
  case 0:
    t = ComplexInit(a, b);
    printf("The norm of your complex is %0.3lf\n", ComplexNorm(t));
    ComplexFree(t);
    break;
  case 1:
    t = ComplexInit(a, b);
    u = ComplexMultiply(t, t);
    printf("The real part of the square of your complex is %0.3lf\n", ComplexReal(u));
    ComplexFree(t);
    ComplexFree(u);
    break;
  case 2:
    t = ComplexInit(a, b);
    u = ComplexMultiply(t, t);
    printf("The imaginary part of the square of your complex is %0.3lf\n", ComplexImaginary(u));
    ComplexFree(t);
    ComplexFree(u);
    break;
  case 3:
    t = ComplexInit(a, b);
    u = ComplexInverse(t);
    printf("The real part of the inverse of your complex is %0.3lf\n", ComplexReal(u));
    ComplexFree(t);
    ComplexFree(u);
    break;
  case 4:
    t = ComplexInit(a, b);
    u = ComplexInverse(t);
    printf("The imaginary part of the inverse of your complex is %0.3lf\n", ComplexImaginary(u));
    ComplexFree(t);
    ComplexFree(u);
    break;
  case 5:
    t = ComplexInit(a, b);
    printf("The phase of your complex id %0.3lf\n", ComplexPhase(t));
    ComplexFree(t);
    break;
  default:
    printf("No such option\n");
    exit(3);
    break;
  }
}
