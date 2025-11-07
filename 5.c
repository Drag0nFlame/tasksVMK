#include <stdio.h>
#include <stdlib.h>
struct Words {
    char *word;
    struct Words *next;
};

int main() {
    char input[1000];
    struct Words *first_elem = NULL;
    struct Words *end_elem = NULL;
    struct Words *current = NULL;
    struct Words *prev = NULL;
    struct Words *temp = NULL;

    printf("Введите строку: ");
    fgets(input, sizeof(input), stdin);

    int i = 0;
    int word_start = -1;
    int word_length = 0;

    //строку на слова и создаем список
    while (input[i] != '\0' && input[i] != '\n') {
        //пробелы и табуляции
        if (input[i] == ' ' || input[i] == '\t') {
            if (word_start != -1) {
                //конец слова
                struct Words *new_node = (struct Words*)malloc(sizeof(struct Words));
                new_node->word = (char*)malloc(word_length + 1);
                new_node->next = NULL;

                //копируем
                for (int j = 0; j < word_length; j++) {
                    new_node->word[j] = input[word_start + j];
                }
                new_node->word[word_length] = '\0';

                //добавляем в конец списка
                if (first_elem == NULL) {
                    first_elem = new_node;
                    end_elem = new_node;
                } else {
                    end_elem->next = new_node;
                    end_elem = new_node;
                }

                word_start = -1;
                word_length = 0;
            }
        } else {
            //ачало нового слова
            if (word_start == -1) {
                word_start = i;
            }
            word_length++;
        }
        i++;
    }

    //последнее слово (если строка не заканчивается пробелом)
    if (word_start != -1) {
        struct Words *new_node = (struct Words*)malloc(sizeof(struct Words));
        new_node->word = (char*)malloc(word_length + 1);
        new_node->next = NULL;

        //копируем слово
        for (int j = 0; j < word_length; j++) {
            new_node->word[j] = input[word_start + j];
        }
        new_node->word[word_length] = '\0';

        //в конец списка
        if (first_elem == NULL) {
            first_elem = new_node;
            end_elem = new_node;
        } else {
            end_elem->next = new_node;
            end_elem = new_node;
        }
    }

    //если список пустой то выводим пустую строку и завершаем
    if (first_elem == NULL) {
        printf("\n");
        return 0;
    }

    //длина последнего слова
    int last_word_length = 0;
    char *temp_ptr = end_elem->word;
    while (*temp_ptr != '\0') {
        last_word_length++;
        temp_ptr++;
    }

    //удаляем слова такой же длины, как последнее слово (кроме самого последнего)
    current = first_elem;
    prev = NULL;

    while (current != NULL) {
        //длина текущего слова
        int current_word_length = 0;
        char *length_ptr = current->word;
        while (*length_ptr != '\0') {
            current_word_length++;
            length_ptr++;
        }

        //проверяем, нужно ли удалять текущее слово
        //если длина совпадает с последним и это не последний элемент
        if (current_word_length == last_word_length && current != end_elem) {
            //удаляем
            if (prev == NULL) {
                //удаляем первый элемент
                first_elem = current->next;
                free(current->word);
                free(current);
                current = first_elem;
            } else {
                //удаляем элемент из середины
                prev->next = current->next;
                free(current->word);
                free(current);
                current = prev->next;
            }
        } else {
            //след элемент
            prev = current;
            current = current->next;
        }
    }

    //выводим результат
    current = first_elem;
    while (current != NULL) {
        printf("%s", current->word);
        if (current->next != NULL) {
            printf(" ");
        }
        current = current->next;
    }
    printf("\n");

    //память
    current = first_elem;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp->word);
        free(temp);
    }

    return 0;
}
