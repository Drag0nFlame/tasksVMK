#include <stdio.h>

int main() {
    double x;
    scanf("%lf", &x);

    double result = 0.0;
    double derivative = 0.0;
    double coefficient;

    while (scanf("%lf", &coefficient) == 1) {
        //схема Горнера
	derivative = derivative * x + result;
        result = result * x + coefficient;
    }

    printf("%.10g\n", result);
    printf("%.10g\n", derivative);
    return 0;
}

