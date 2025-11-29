#ifndef LIST_H
#define LIST_H

/*для хранения списка строк */
typedef struct {
    char **items;      /*массив указателей на строки */
    int capacity;      /*текущая вместимость массива */
    int size;          /*текущее количество элементов */
} StringList;

/*функции для работы со списком строк */

/**
 *инициализирует пустой список строк
 *@param list Указатель на список для инициализации
 */
void init_list(StringList *list);

/**
 *добавляет строку в конец списка
 *@param list указатель на список
 *@param str строка для добавления
 *@return 0 при успехе, -1 при ошибке памяти
 */
int add_to_list(StringList *list, const char *str);

/**
 *cортирует список строк в лексикографическом порядке
 *@param list указатель на список для сортировки
 */
void sort_list(StringList *list);

/**
 *выводит список строк в stdout
 * @param list указатель на список для вывода
 */
void print_list(const StringList *list);

/**
 *освобождает память
 *@param list указатель на список для очистки
 */
void free_list(StringList *list);

#endif
