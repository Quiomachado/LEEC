#include <stdio.h>
#include <stdlib.h>
#include <string.h> //ISTO
#include <math.h>   //ISTO

/*
 * Program to calculate the square root of a floating point number.
 *
 * Note: a valid floating point number for atof using the "C" locale is formed by an optional
 * sign character (+ or -), followed by a sequence of digits, optionally containing a decimal-point
 * character (.), optionally followed by an exponent part (an e or E character followed by an optional
 * sign and a sequence of digits).
 */

int main(int argc, char **argv)
{
  int i, size, dots = 0;
  double x; // era int x;

  printf("I am a mathematical genius and can calculate the square root of any number!!!\n\n");

  if (argc != 2) // era argc < 2 || argc > 20
  {              // ISTO
    printf("A single number is needed as an argument!\n");
    exit(EXIT_FAILURE);
  } // ISTO

  if (strlen(argv[1]) > 1) // era size == strlen(argv[1]) > 1
  {
    size = strlen(argv[1]);
    i = 0;
    if (argv[1][0] == '-' || argv[1][0] == '+')
      i = 1;
    for (; i < size; i++)
      if (argv[1][i] < '0' || argv[1][i] > '9')
      {
        if (argv[1][i] == '.' && dots == 0)
        {
          dots = 1;
          continue;
        }
        printf("Not a valid number! Pay attention. I'm fragile\n");
        exit(EXIT_FAILURE);
      }
  }
  else
  {
    if (argv[1][0] < '0' || argv[1][0] > '9')
    {
      printf("Not a valid number! Pay attention. I'm fragile\n");
      exit(EXIT_FAILURE);
    }
  }

  x = atof(argv[1]);

  if (x < 0)
  {
    printf("Today, i'm not in the mood for negative numbers! Try tommorow that I may accomodate your request...\n");
    exit(EXIT_FAILURE);
  }
  else
    printf("Square root of %.2lf is %.4lf\n", x, sqrt(x));

  exit(EXIT_SUCCESS);
}
