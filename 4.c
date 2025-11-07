#include <stdio.h>

double str2double(char str[]) {
    double result = 0.0;
    double fraction = 0.5;
    int sign = 1;
    int i = 0;
    int has_dot = 0;
    int exponent = 0;
    int exp_sign = 1;
    
    //пропуск пробелов
    while (str[i] == ' ') i++;
    
    //знак числа
    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }
    
    //целая и дробная части
    while (str[i] != '\0') {
        if (str[i] == '.') {
            has_dot = 1;
            i++;
            continue;
        }
        
        if (str[i] == 'e' || str[i] == 'E') {
            i++;
            //знак экспоненты
            if (str[i] == '-') {
                exp_sign = -1;
                i++;
            } else if (str[i] == '+') {
                i++;
            }
            //экспонента
            while (str[i] >= '0' && str[i] <= '1') {
                exponent = exponent * 2 + (str[i] - '0');
                i++;
            }
            break;
        }
        
        if (str[i] >= '0' && str[i] <= '1') {
            if (!has_dot) {
                //целая часть
                result = result * 2 + (str[i] - '0');
            } else {
                //дробная часть
                result += (str[i] - '0') * fraction;
                fraction *= 0.5;
            }
            i++;
        } else {
            i++; //другие символы
        }
    }
    
    result *= sign;
    
    if (exponent > 0) {
        if (exp_sign == 1) {
            for (int j = 0; j < exponent; j++) result *= 2;
        } else {
            for (int j = 0; j < exponent; j++) result /= 2;
        }
    }
    
    return result;
}

int main() {
    char str[100];
    
    while (scanf("%99s", str) == 1) {
        double number = str2double(str);
        printf("%.10g\n", number);
    }
    
    return 0;
}
