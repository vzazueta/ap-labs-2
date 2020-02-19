#include <stdio.h>

#define   STEP   20      /* step size */

/* print Fahrenheit-Celsius table */

int main(int argc, char **argv)
{
    int i;

    for (i = 1; argv[i] != NULL; i++)
	printf("Fahrenheit: %3d, Celcius: %6.1f\n", atoi(argv[i]), (5.0/9.0)*(atoi(argv[i])-32));

    return 0;
}
