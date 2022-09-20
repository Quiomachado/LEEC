typedef struct _complex Complex;

Complex * ComplexInit(double, double);

Complex * ComplexMultiply(Complex *, Complex *);

Complex * ComplexInverse(Complex *);

double ComplexReal(Complex *);

double ComplexImaginary(Complex *);
  
double ComplexNorm(Complex *);

void ComplexFree(Complex *);

double ComplexPhase(Complex *);
