# include <stdio.h>
# include <math.h>

#define PI 3.14159265

int main()
{
  double i, sinus, cosinus;
  i = 0.0;
  sinus = 0.0;
  cosinus = 0.0;

  for (i; i<360; i+=10) {
    cosinus = cos(180/PI * i);
    sinus = sin(180/PI * i);
    printf("%2.2f,\t %2.2f,\t %2.2f \n", i, sinus, cosinus);
  }

  return 0;
}
