#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/*начальная вместимость списка */
#define in_capacity 10

void init_list(StringList *list) {
    list->size = 0;
    list->capacity = in_capacity;
    list->items = malloc(list->capacity * sizeof(char *));
    if (list->items == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память для списка\n");
        exit(1);
    }
}

int add_to_list(StringList *list, const char *str) {
    /*проверка, нужно ли увеличить вместимость */
    if (list->size >= list->capacity) {
        int new_capacity = list->capacity * 2;
        char **new_items = realloc(list->items, new_capacity * sizeof(char *));
        if (new_items == NULL) {
            fprintf(stderr, "Ошибка: не удалось увеличить список\n");
            return -1;
        }
        list->items = new_items;
        list->capacity = new_capacity;
    }
    
    /*копируем*/
    list->items[list->size] = malloc(strlen(str) + 1);
    if (list->items[list->size] == NULL) {
        fprintf(stderr, "Ошибка: не удалось выделить память для строки\n");
        return -1;
    }
    strcpy(list->items[list->size], str);
    list->size++;
    
    return 0;
}

/*вспомогательная функция для сравнения строк (для сортировки) */
static int compare_strings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

void sort_list(StringList *list) {
    /*сортировка пузырьком */
    int i, j;
    for (i = 0; i < list->size - 1; i++) {
        for (j = 0; j < list->size - i - 1; j++) {
            if (strcmp(list->items[j], list->items[j + 1]) > 0) {
                /*меняем местами указатели */
                char *temp = list->items[j];
                list->items[j] = list->items[j + 1];
                list->items[j + 1] = temp;
            }
        }
    }
}

void print_list(const StringList *list) {
    printf("%d\n", list->size);
    for (int i = 0; i < list->size; i++) {
        printf("%s\n", list->items[i]);
    }
}

void free_list(StringList *list) {
    for (int i = 0; i < list->size; i++) {
        free(list->items[i]);
    }
    free(list->items);
    list->size = 0;
    list->capacity = 0;
    list->items = NULL;
}
