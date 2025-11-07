#include <stdio.h>

int main() {
    double x;
    scanf("%lf", &x);
    
    double result = 0.0;
    double coefficient;
    
    while (scanf("%lf", &coefficient) == 1) {
        //схема Горнера
        result = result * x + coefficient;
    }
    
    printf("%.10g\n", result);
    return 0;
}
