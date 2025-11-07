#include <stdio.h>
#include <stdlib.h>

// Структура для узла дерева
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Функция для создания нового узла
struct Node* createNode(int key) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Функция для добавления элемента в дерево
struct Node* insert(struct Node* root, int key) {
    // Если дерево пустое, создаем новый узел
    if (root == NULL) {
        return createNode(key);
    }
    
    // Ищем место для вставки
    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    }
    // Если ключ уже есть, ничего не делаем
    
    return root;
}

// Функция для поиска минимального элемента в дереве
struct Node* findMin(struct Node* root) {
    while (root != NULL && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Функция для удаления элемента из дерева
struct Node* delete(struct Node* root, int key) {
    if (root == NULL) {
        return NULL;
    }
    
    // Ищем узел для удаления
    if (key < root->key) {
        root->left = delete(root->left, key);
    } else if (key > root->key) {
        root->right = delete(root->right, key);
    } else {
        // Нашли узел для удаления
        
        // Случай 1: у узла нет потомков или только один потомок
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        // Случай 2: у узла два потомка
        struct Node* temp = findMin(root->right);
        root->key = temp->key;
        root->right = delete(root->right, temp->key);
    }
    
    return root;
}

// Функция для поиска элемента в дереве
int search(struct Node* root, int key) {
    if (root == NULL) {
        return 0; // не найден
    }
    
    if (key == root->key) {
        return 1; // найден
    } else if (key < root->key) {
        return search(root->left, key);
    } else {
        return search(root->right, key);
    }
}

// Функция для освобождения памяти дерева
void freeTree(struct Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    struct Node* root = NULL;
    char operation;
    int number;
    
    // Читаем ввод пока не конец файла
    while (scanf(" %c%d", &operation, &number) != EOF) {
        if (operation == '+') {
            // Добавление элемента
            root = insert(root, number);
        } else if (operation == '-') {
            // Удаление элемента
            root = delete(root, number);
        } else if (operation == '?') {
            // Поиск элемента
            if (search(root, number)) {
                printf("%d yes\n", number);
            } else {
                printf("%d no\n", number);
            }
        }
    }
    
    // Освобождаем память
    freeTree(root);
    
    return 0;
}
