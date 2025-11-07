#include <stdio.h>

//быстро
long long fib_iterative(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

//медленно
long long fib_recursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib_recursive(n - 2) + fib_recursive(n - 1);
}

int main() {
    int i;
    
    while (scanf("%d", &i) == 1) {
        //быстрая итеративня версия
        long long result_iter = fib_iterative(i);
        printf("Итеративно: %lld\n", result_iter);
        
        //медленная рекурсивная версия
        long long result_rec = fib_recursive(i);
        printf("Рекурсивно: %lld\n", result_rec);
        printf("---\n");
    }
    
    return 0;
}
