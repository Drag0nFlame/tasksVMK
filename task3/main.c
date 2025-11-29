#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"

/*размер блока для чтения */
#define BLOCK_SIZE 256
/*начальный размер буфера для слова */
#define INITIAL_WORD_SIZE 32

/*специальные слова */
static const char *SPECIAL_WORDS[] = {">>>", ">>", ">", "||", "|", "&&", "&", ";", "<", "(", ")", NULL};

/*функция, является ли символ частью простого слова */
int is_regular_char(char c) {
    return isalnum(c) || c == '_' || c == '.' || c == '/' || c == '\\' || c == '-';
}

/*функция, является ли строка специальным словом */
int is_special_word(const char *str, int len) {
    for (int i = 0; SPECIAL_WORDS[i] != NULL; i++) {
        if (strncmp(str, SPECIAL_WORDS[i], len) == 0 && SPECIAL_WORDS[i][len] == '\0') {
            return 1;
        }
    }
    return 0;
}

/*функция максимальная длина специального слова с начала строки */
int get_special_word_length(const char *str) {
    int max_len = 0;
    for (int i = 0; SPECIAL_WORDS[i] != NULL; i++) {
        int len = strlen(SPECIAL_WORDS[i]);
        if (strncmp(str, SPECIAL_WORDS[i], len) == 0 && len > max_len) {
            max_len = len;
        }
    }
    return max_len;
}

/*основная функция обработки строки */
void process_line(const char *line, StringList *list) {
    int i = 0;
    int line_len = strlen(line);
    
    while (i < line_len) {
        /*пропускаем пробелы */
        if (isspace(line[i])) {
            i++;
            continue;
        }
        
        /*проверяем, не начинается ли специальное слово */
        int special_len = get_special_word_length(&line[i]);
        if (special_len > 0) {
            char *word = malloc(special_len + 1);
            if (word == NULL) {
                fprintf(stderr, "Ошибка памяти при создании специального слова\n");
                return;
            }
            strncpy(word, &line[i], special_len);
            word[special_len] = '\0';
            add_to_list(list, word);
            free(word);
            i += special_len;
            continue;
        }
        
        /*если обычное то читаем до следующего разделителя */
        int start = i;
        while (i < line_len && is_regular_char(line[i])) {
            i++;
        }
        
        if (i > start) {
            int word_len = i - start;
            char *word = malloc(word_len + 1);
            if (word == NULL) {
                fprintf(stderr, "Ошибка памяти при создании слова\n");
                return;
            }
            strncpy(word, &line[start], word_len);
            word[word_len] = '\0';
            add_to_list(list, word);
            free(word);
        }
    }
}

int main() {
    StringList list;
    char buffer[BLOCK_SIZE + 1];
    char *line = NULL;
    int line_size = 0;
    int line_len = 0;
    
    init_list(&list);
    
    printf("Введите строки (Ctrl+D для завершения):\n");
    
    /*чтение строк из stdin */
    while (fgets(buffer, BLOCK_SIZE, stdin) != NULL) {
        int buffer_len = strlen(buffer);
        
        /*увеличиваем буфер для строки при необходимости */
        if (line_len + buffer_len + 1 > line_size) {
            line_size = (line_len + buffer_len + 1) * 2;
            char *new_line = realloc(line, line_size);
            if (new_line == NULL) {
                fprintf(stderr, "Ошибка: не удалось выделить память для строки\n");
                free(line);
                free_list(&list);
                return 1;
            }
            line = new_line;
        }
        
        /*добавляем прочитанный блок к текущей строке */
        strcpy(line + line_len, buffer);
        line_len += buffer_len;
        
        /*если строка завершена (есть символ новой строки), обрабатываем ее */
        if (line_len > 0 && line[line_len - 1] == '\n') {
            line[line_len - 1] = '\0'; /*убираем символ новой строки */
            
            /*обрабатываем строку */
            process_line(line, &list);
            
            /*выводим исходный порядок */
            printf("Исходный порядок:\n");
            print_list(&list);
            
            /*сортируем и выводим в лексикографическом порядке */
            sort_list(&list);
            printf("Лексикографический порядок:\n");
            print_list(&list);
            
            /*очищаем список для следующей строки */
            free_list(&list);
            init_list(&list);
            
            /*сбрасываем буфер строки */
            line_len = 0;
        }
    }
    
    /*обработка последней строки, если она не завершена символом новой строки */
    if (line_len > 0) {
        line[line_len] = '\0';
        process_line(line, &list);
        
        printf("Исходный порядок:\n");
        print_list(&list);
        
        sort_list(&list);
        printf("Лексикографический порядок:\n");
        print_list(&list);
    }
    
    /*освобождение памяти */
    free(line);
    free_list(&list);
    
    return 0;
}
