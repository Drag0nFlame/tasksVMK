#include <stdio.h>

int main() {
    double epsilon;
    scanf("%lf", &epsilon);
    
    double x;
    while (scanf("%lf", &x) == 1) {
        if (x < 0) {
            fprintf(stderr, "Ошибка: отрицательное число\n");
            continue;
        }
        
        if (x == 0) {
            printf("%.10g\n", 0.0);
            continue;
        }
        
        double current = 1.0;
        double previous;
        
        do {
            previous = current;
            current = 0.5 * (previous + x / previous);
        } while (current - previous >= epsilon || previous - current >= epsilon);
        
        printf("%.10g\n", current);
    }
    
    return 0;
}
