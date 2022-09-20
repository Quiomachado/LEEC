#include <stdlib.h>
#include <math.h>
#include "Complex.h"

#define M_PI 3.141592653589793

struct _complex
{
  double Real;
  double Imaginary;
};

Complex *ComplexInit(double a, double b)
{

  Complex *res;

  res = (Complex *)malloc(sizeof(Complex));
  if (res == NULL)
    exit(1);
  res->Real = a;
  res->Imaginary = b;

  return res;
}

void ComplexFree(Complex *T)
{
  free(T);
}

double ComplexNorm(Complex *T)
{
  if (T == NULL)
    exit(2);
  return sqrt(T->Real * T->Real + T->Imaginary * T->Imaginary);
}

double ComplexReal(Complex *T)
{
  if (T == NULL)
    exit(2);
  return T->Real;
}

double ComplexImaginary(Complex *T)
{
  if (T == NULL)
    exit(2);
  return T->Imaginary;
}

Complex *ComplexMultiply(Complex *T1, Complex *T2)
{
  Complex *res;

  if (T1 == NULL || T2 == NULL)
    exit(2);

  res = (Complex *)malloc(sizeof(Complex));
  if (res == NULL)
    exit(1);

  res->Real = T1->Real * T2->Real - T1->Imaginary * T2->Imaginary;
  res->Imaginary = T1->Real * T2->Imaginary + T1->Imaginary * T2->Real;

  return res;
}

double ComplexPhase(Complex *T)
{
  if (T == NULL)
    exit(2);
  if (T->Real >= 0)
    return atan(T->Imaginary / T->Real);
  else if (T->Imaginary > 0)
    return M_PI - atan(-T->Imaginary / T->Real);
  else
    return -M_PI + atan(T->Imaginary / T->Real);
}

Complex *ComplexInverse(Complex *T)
{
  Complex *res;
  double norm, phase;

  if (T == NULL)
    exit(2);
  res = (Complex *)malloc(sizeof(Complex));
  if (res == NULL)
    exit(1);
  norm = ComplexNorm(T);
  phase = ComplexPhase(T);
  if (norm == 0)
    exit(3);
  res->Real = 1 / norm * cos(-phase);
  res->Imaginary = 1 / norm * sin(-phase);

  return res;
}
