#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "project_2.h"

struct shipNode *head = NULL;

int getNextNumber() {
    if (!head) {
        return 0;
    }
    return head->number + 1;
}

struct shipNode* createNode(char *flag, shipType type, int length, int dwt) {
    struct shipNode *node = malloc(sizeof(struct shipNode));
    node->data.flag = flag;
    node->data.type = type;
    node->data.length = length;
    node->data.dwt = dwt;
    return node;
}

void addNode(struct shipNode *node) {
    node->number = getNextNumber();
    node->next = head;
    head = node;
}

char* getFlag() {
    char *flag = malloc(128 * sizeof(char));
    scanf("%s", flag);
    flag[0] = toupper(flag[0]);
    return flag;
}

int getType() {
    char *tmp = malloc(128 * sizeof(char));
    while (1) {
        scanf("%s", tmp);
        if (tmp[1] != '\0' || (tmp[0] != 'M' && tmp[0] != 'D')) {
            printf("Podaj poprawny rodzaj typu - M lub D: ");
        } else {
            break;
        }
    }
    return tmp[0] == 'M' ? 0 : 1;
}

int getLength() {
    char *tmp = malloc(128 * sizeof(char));
    int length;
    while (1) {
        scanf("%s", tmp);
        if (!sscanf(tmp, "%3d", &length) || length < 1 || 999 < length) {
            printf("Podaj poprawna wartosc dlugosci - (1 - 999): ");
        } else {
            break;
        }
    }
    return length;
}

int getDwt() {
    char *tmp = malloc(128 * sizeof(char));
    int dwt;
    while (1) {
        scanf("%s", tmp);
        if (!sscanf(tmp, "%6d", &dwt) || dwt < 1 || 999999 < dwt) {
            printf("Podaj poprawna wartosc DWT - (1 - 999999): ");
        } else {
            break;
        }
    }
    return dwt;
}

struct shipNode* readNodeFromUser() {
    char *flag, type;
    int length, dwt;
    printf("Podaj bandere: "); flag = getFlag();
    printf("Podaj indeks typu (M/D): "); type = getType();
    printf("Podaj dlugosc w metrach (do 3 cyfr): ");  length = getLength();
    printf("Podaj noscnosc DWT w tonach (do 6 cyfr): ");  dwt = getDwt();
    printf("\n");
    return createNode(flag, type, length, dwt);
}

void printNode(struct shipNode *node) {
    printf("%3d. %4c %10d %15s %10d\n", node->number, node->data.type ? 'D' : 'M', node->data.dwt, node->data.flag, node->data.length);
}

void sort(int (*comparator)(struct shipNode*, struct shipNode*)) {
    int swapped;
    struct shipNode *ptr, *lptr = NULL;
    printf("Sorting\n");

    do {

        swapped = 0;
        ptr = head;
        while (ptr->next != lptr) {
            if (comparator(ptr, ptr->next)) {
                swap(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}

void swap(struct shipNode *n1, struct shipNode *n2) {
    struct shipNode temp;
    temp.number = n1->number;
    temp.data = n1->data;
    n1->number = n2->number;
    n1->data = n2->data;
    n2->number = temp.number;
    n2->data = temp.data;
}

int comparator1(struct shipNode *n1, struct shipNode *n2) {
    return n1->number < n2->number;
}

int comparator2(struct shipNode *n1, struct shipNode *n2) {
    return n1->data.dwt > n2->data.dwt;
}

int comparator3(struct shipNode *n1, struct shipNode *n2) {
    if (!strcmp(n1->data.flag, n2->data.flag)) {
        return n1->data.length > n2->data.length;
    }
    return strcmp(n1->data.flag, n2->data.flag) < 0;
}

void printNodesInOrder(struct shipNode *node) {
    if (!node) {
        return;
    }
    if (node->next) {
        printNodesInOrder(node->next);
    }
    printNode(node);
}

void printNodesByType(struct shipNode *node, shipType type) {
    if (!node) {
        return;
    }
    if (node->next) {
        printNodesByType(node->next, type);
    }
    if (node->data.type == type) {
        printNode(node);
    }
}

void showMenu() {
    int option;
    char type;
    struct shipNode *node;
    printf("1. Dodaj statek.\n");
    printf("2. Wyswietl statki w kolejnosci dodawania.\n");
    printf("3. Wyswietl statki wybranego typu wedlug nosnosci.\n");
    printf("4. Wyswietl statki alfabetycznie wedlug dlugosci.\n");

    printf("Wybierz opcje: "); scanf("%d", &option);
    switch (option) {
        case 1:
            node = readNodeFromUser();
            sort(&comparator1);
            addNode(node);
            printf("Pomyslnie dodano statek.\n\n");
            break;
        case 2:
            printf("\n");
            sort(&comparator1);
			printf("%4s %4s %10s %15s %10s\n", "ID", "Typ", "DWT", "Bandera", "Dlugosc");
            printNodesInOrder(head);
            printf("\n");
            break;
        case 3:
            printf("\n");
            printf("Podaj typ statku - (M/D): "); type = getType();
            printf("\n");
            sort(&comparator2);
			printf("%4s %4s %10s %15s %10s\n", "ID", "Typ", "DWT", "Bandera", "Dlugosc");
            printNodesByType(head, type);
            printf("\n");
            break;
        case 4:
            printf("\n");
            sort(&comparator3);
			printf("%4s %4s %10s %15s %10s\n", "ID", "Typ", "DWT", "Bandera", "Dlugosc");
            printNodesInOrder(head);
            printf("\n");
            break;
        default:
            printf("Bledna opcja!\n\n");
            break;
    }
}

int main() {
    addNode(createNode("Albania", M, 1, 2));
    addNode(createNode("Bahamy", M, 1, 4));
    addNode(createNode("Australia", M, 1, 3));
    addNode(createNode("Liberia", D, 12, 12));
    addNode(createNode("Polska", D, 13, 221));
    addNode(createNode("Irlandia", D, 13, 221));
    addNode(createNode("Indie", D, 131, 2321));
    addNode(createNode("Szwajcaria", D, 9, 99));
    addNode(createNode("Niemcy", M, 31, 452));
    addNode(createNode("Wlochy", M, 15, 6444));
    addNode(createNode("Ghana", M, 71, 3333));
    addNode(createNode("Czechy", M, 155, 5462));
    addNode(createNode("Litwa", M, 16, 466));
    addNode(createNode("Litwa", M, 14, 53));
    addNode(createNode("Litwa", D, 162, 1452));
    while (1) {
        showMenu();
    }

    return 0;
}

