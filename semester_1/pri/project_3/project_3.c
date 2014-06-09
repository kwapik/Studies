#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "project_3.h"

ToolNode *toolHead;
StoreNode *storeHead;
int modified;

ToolNode* createToolNode(int id, ToolType typeId, int type, char* desc) {
    ToolNode *node = malloc(sizeof(ToolNode));
    node->data = malloc(sizeof(Tool));
    node->data->id = id;
    node->data->typeId = typeId;
    node->data->type = type;
    node->data->desc = desc;
    return node;
}

StoreNode* createStoreNode(char *name) {
    StoreNode *node = malloc(sizeof(StoreNode));
    node->data = malloc(sizeof(Store));
    node->data->name = name;
    node->tools = NULL;
    node->next = NULL;
    return node;
}

void addToolNode(ToolNode *node) {
    node->next = toolHead;
    toolHead = node;
}

void addStoreNode(StoreNode *node) {
    node->next = storeHead;
    storeHead = node;
}

void addToolToStore(char *name, int id) {
    StoreNode *store = getStoreNodeByName(storeHead, name);
    ToolNode *tool = getToolNodeById(toolHead, id);
    ToolNode *newTool = createToolNode(9999, 1, 1, "");
    free(newTool->data);
    newTool->data = tool->data;
    newTool->next = store->tools;
    store->tools = newTool;
}

void addStoreToTool(int id, char *name) {
    StoreNode *store = getStoreNodeByName(storeHead, name);
    ToolNode *tool = getToolNodeById(toolHead, id);
    StoreNode *newStore = createStoreNode("");
    free(newStore->data);
    newStore->data = store->data;
    newStore->next = tool->stores;
    tool->stores = newStore;
}

ToolNode* readToolNodeFromUser() {
    int id;
    ToolType typeId;
    int type;
    char* desc;

    printf("Podaj numer narzędzia: "); id = getInt(10000);
    printf("Podaj indeks typu narzedzia (M lub D): "); typeId = getType();
    printf("Podaj typ narzedzia: "); type = getInt(1000);
    printf("Podaj opis narzedzia: "); desc = getString();

    return createToolNode(id, typeId, type, desc);
}

StoreNode* readStoreNodeFromUser() {
    char *name;

    printf("Podaj opis narzedzia: "); name = getString();

    return createStoreNode(name);
}

int getInt(int max) {
    char *tmp = malloc(64 * sizeof(char));
    int result;

    while (1) {
        scanf("%s", tmp);
        if (!sscanf(tmp, "%d", &result) || result < 0 || result > max) {
            printf("Podaj poprawna wartosc: ");
        } else {
            break;
        }
    }
    free(tmp);
    return result;
}

int getType() {
    char *tmp = malloc(64 * sizeof(char));
    char result;
    while (1) {
        scanf("%s", tmp);
        if (tmp[1] != '\0' || (tmp[0] != 'D' && tmp[0] != 'M')) {
            printf("Podaj poprawna wartosc: ");
        } else {
            break;
        }
    }
    result = tmp[0];
    free(tmp);
    return result == 'D' ? 0 : 1;
}

char* getString() {
    char *result = malloc(64 * sizeof(char));
    while (!scanf("%s", result)) {
        printf("Podaj poprawna wartosc: ");
    }
    return result;
}

ToolNode* getToolNodeById(ToolNode *node, int id) {
    if (!node) {
        return NULL;
    }
    if(node->data->id == id) {
        return node;
    }
    return node->next ? getToolNodeById(node->next, id) : NULL;
}

StoreNode* getStoreNodeByName(StoreNode *node, char *name) {
    if (!node) {
        return NULL;
    }
    if(!strcmp(node->data->name, name)) {
        return node;
    }
    return node->next ? getStoreNodeByName(node->next, name) : NULL;
}

ToolNode* deleteToolNodeById(ToolNode *node, int id) {
    ToolNode *tmp;
    if (!node) {
        return NULL;
    }
    if (node->data->id == id) {
        tmp = node->next;
        free(node);
        return tmp;
    }
    node->next = deleteToolNodeById(node->next, id);
    return node;
}

void deleteToolNodeFromStoreByIdRecursive(StoreNode *node, int id) {
    if (!node) {
        return;
    }
    if (node->next) {
        deleteToolNodeFromStoreByIdRecursive(node->next, id);
    }
    node->tools = deleteToolNodeById(node->tools , id);
}

StoreNode* deleteStoreNodeByName(StoreNode *node, char *name) {
    StoreNode *tmp;
    if (!node) {
        return NULL;
    }
    if (!strcmp(node->data->name, name)) {
        tmp = node->next;
        free(node);
        return tmp;
    }
    node->next = deleteStoreNodeByName(node->next, name);
    return node;
}

void deleteStoreNodeFromToolByNameRecursive(ToolNode *node, char *name) {
    if (!node) {
        return;
    }
    if (node->next) {
        deleteStoreNodeFromToolByNameRecursive(node->next, name);
    }
    node->stores = deleteStoreNodeByName(node->stores , name);
}

void printToolNodeHeader() {
    printf("%-4s %-7s %-4s %-10s\n", "ID", "ID typu", "Typ", "Opis");
}

void printStoreNodeHeader() {
    printf("Nazwa\n");
}

char *getToolNodeAsString(ToolNode *node) {
    char *str = malloc(128 * sizeof(char));
    sprintf(str, "%-4d %-7s %-4d %-10s", node->data->id, node->data->typeId ? "M" : "D", node->data->type, node->data->desc);
    return str;
}

char *getStoreNodeAsString(StoreNode *node) {
    char *str = malloc(128 * sizeof(char));
    sprintf(str, "%s", node->data->name);
    return str;
}

void printToolNode(ToolNode *node, int printStores) {
    printf("%s\n", getToolNodeAsString(node));
    if (printStores) {
        printStoreNodeRecursive(node->stores, 0);
    }
}

void printStoreNode(StoreNode *node, int printTools) {
    printf("%s\n", getStoreNodeAsString(node));
    if (printTools) {
        printToolNodeRecursive(node->tools, 0);
    }
}

void printToolNodeRecursive(ToolNode *node, int printStores) {
    if (!node) {
        return;
    }
    if (node->next) {
        printToolNodeRecursive(node->next, printStores);
    }
    printToolNode(node, printStores);
}

void printStoreNodeRecursive(StoreNode *node, int printTools) {
    if (!node) {
        return;
    }
    if (node->next) {
        printStoreNodeRecursive(node->next, printTools);
    }
    printStoreNode(node, printTools);
}

void showToolNodesById(ToolNode *node, int id) {
    if (!node) {
        return;
    }
    if (node->data->id == id) {
        printf("\n");
        printToolNode(node, 1);
    }
    showToolNodesById(node->next, id);
}

void showToolNodesByTypeId(ToolNode *node, ToolType type) {
    if (!node) {
        return;
    }
    if (node->data->typeId == type) {
        printf("\n");
        printToolNode(node, 1);
    }
    showToolNodesByTypeId(node->next, type);
}

void showToolNodesByType(ToolNode *node, int type) {
    if (!node) {
        return;
    }
    if (node->data->type == type) {
        printf("\n");
        printToolNode(node, 1);
    }
    showToolNodesByType(node->next, type);
}

void showToolNodesByDesc(ToolNode *node, char *desc) {
    if (!node) {
        return;
    }
    if (!strcmp(node->data->desc, desc)) {
        printf("\n");
        printToolNode(node, 1);
    }
    showToolNodesByDesc(node->next, desc);
}

void sortTools(ToolNode *node, int (*comparator)(ToolNode*, ToolNode*)) {
    int swapped;
    ToolNode *ptr, *lptr = NULL;
    do {
        swapped = 0;
        ptr = node;
        while (ptr->next != lptr) {
            if (comparator(ptr, ptr->next)) {
                swapTool(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        lptr = ptr;
    } while (swapped);
}

void swapTool(ToolNode *node1, ToolNode *node2) {
    ToolNode tmp;
    tmp.data = node1->data;
    tmp.stores = node1->stores;
    node1->data = node2->data;
    node1->stores = node2->stores;
    node2->data = tmp.data;
    node2->stores = tmp.stores;
}

int toolComparator1(ToolNode *node1, ToolNode *node2) {
    return node1->data->id < node2->data->id;
}

int showMenu() {
    int choice, id;
    char *name = malloc(64 * sizeof(char));
    Tool *tool;
    Store *store;
    ToolType type;
    ToolNode *toolNode, *toolPtr;
    StoreNode *storeNode, *storePtr;
    printf("\n\n-------------------------\n");
    printf("1. Dodaj narzedzie\n"); 
    printf("2. Dodaj magazyn\n\n");
    printf("3. Edytuj narzedzie\n"); 
    printf("4. Edytuj magazyn\n\n");
    printf("5. Przenies narzedzie do innego magazynu\n\n");
    printf("6. Usun narzedzie z calego zbioru\n");
    printf("7. Usun narzedzie z magazynu\n");
    printf("8. Usun magazyn\n\n");
    printf("9. Wyswietl narzedzia\n");
    printf("10. Wyswietl magazyny\n");
    printf("11. Wyswietl narzedzia w magazynie\n");
    printf("12. Wyswietl narzedzia z podanym numerem\n");
    printf("13. Wyswietl narzedzia z podanym indeksem typu\n");
    printf("14. Wyswietl narzedzia z podanym typem\n");
    printf("15. Wyswietl narzedzia z podanym opisem\n\n");
    printf("16. Zapisz dane do pliku\n");
    printf("0. Zakoncz program\n");
    printf("Wybierz opcje: "); scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            toolNode = readToolNodeFromUser();
            addToolNode(toolNode);
            printf("Pomyslnie dodano narzedzie.\n\n");
            modified = 1;
            break;
        case 2:
            storeNode = readStoreNodeFromUser();
            addStoreNode(storeNode);
            printf("Pomyslnie dodano magazyn.\n\n");
            modified = 1;
            break;
        case 3:
            printf("Podaj numer narzedzia do edycji: "); id = getInt(10000);
            toolPtr = getToolNodeById(toolHead, id);
            if (!toolPtr) {
                printf("Narzedzie o podanym ID nie istnieje!\n\n");
                break;
            }
            printf("Podaj nowe dane narzedzia: \n");
            toolNode = readToolNodeFromUser();
            toolPtr->data = toolNode->data;
            printf("Pomyslnie zmieniono narzedzie.\n\n");
            modified = 1;
            break;
        case 4:
            printf("Podaj nazwe magazynu do edycji: "); name = getString();
            storePtr = getStoreNodeByName(storeHead, name);
            if (!storePtr) {
                printf("Magazyn o podanej nazwie nie istnieje!\n\n");
                break;
            }
            printf("Podaj nowe dane magazynu:\n");
            storeNode = readStoreNodeFromUser();
            storePtr->data->name = storeNode->data->name;
            printf("Pomyslnie zmieniono magazyn.\n\n");
            modified = 1;
            break;
        case 5:
            printf("Podaj nazwe magazynu Z ktorego przeniesc: "); name = getString();
            storePtr = getStoreNodeByName(storeHead, name);
            printf("Podaj nazwe magazynu DO ktorego przeniesc: "); name = getString();
            if (!strcmp(storePtr->data->name, name)) {
                printf("To ten sam magazyn!\n");
                break;
            }
            printf("Podaj numer narzedzia do przeniesienia: "); id = getInt(10000);
            toolPtr = getToolNodeById(storePtr->tools, id);
            if (!toolPtr) {
                printf("Narzedzie nie istnieje w magazynie!\n");
                break;
            }
            storePtr->tools = deleteToolNodeById(storePtr->tools, id);
            toolPtr->stores = deleteStoreNodeByName(toolPtr->stores, name);
            addToolToStore(name, id);
            addStoreToTool(id, name);
            modified = 1;
            break;
        case 6:
            printf("Podaj numer narzedzia do usuniecia: "); id = getInt(10000);
            toolPtr = getToolNodeById(toolHead, id);
            tool = toolPtr->data;
            if (!toolPtr) {
                printf("Narzedzie o podanym ID nie istnieje!\n\n");
                break;
            }
            deleteToolNodeFromStoreByIdRecursive(storeHead, id);
            toolHead = deleteToolNodeById(toolHead, toolPtr->data->id);
            free(tool);
            modified = 1;
            break;
        case 7:
            printf("Podaj nazwe magazynu z ktorego usunac narzedzie: "); name = getString();
            storePtr = getStoreNodeByName(storeHead, name);
            if (!storePtr) {
                printf("Magazyn o podanej nazwie nie istnieje!\n\n");
                break;
            }
            printf("Podaj numer narzedzia do usuniecia: "); id = getInt(10000);
            toolPtr = getToolNodeById(storePtr->tools, id);
            if (!toolPtr) {
                printf("Narzedzie o podanym ID nie istnieje!\n\n");
                break;
            }
            storePtr->tools = deleteToolNodeById(storePtr->tools, id);
            toolPtr->stores = deleteStoreNodeByName(toolPtr->stores, name);
            modified = 1;
            break;
        case 8:
            printf("Podaj nazwe magazynu do usuniecia: "); name = getString();
            storePtr = getStoreNodeByName(storeHead, name);
            store = storePtr->data;
            if (!storePtr) {
                printf("Magazyn o podanej nazwie nie istnieje!\n\n");
                break;
            }
            deleteStoreNodeFromToolByNameRecursive(toolHead, name);
            storeHead = deleteStoreNodeByName(storeHead, storePtr->data->name);
            free(store);
            printf("Pomyslnie usunieto magazyn.\n\n");
            modified = 1;
            break;
        case 9:
            printToolNodeHeader();
            printToolNodeRecursive(toolHead, 0);
            break;
        case 10:
            printStoreNodeHeader();
            printStoreNodeRecursive(storeHead, 0);
            break;
        case 11:
            printf("Podaj nazwe magazynu do wyswietlenia: "); name = getString();
            storePtr = getStoreNodeByName(storeHead, name);
            sortTools(storePtr->tools, toolComparator1);
            printStoreNode(storePtr, 1);
            break;
        case 12:
            printf("Podaj numer narzedzia do wyswietlenia: "); id = getInt(10000);
            printToolNodeHeader();
            showToolNodesById(toolHead, id);
            break;
        case 13:
            printf("Podaj indeks typu narzedzia do wyswietlenia: "); type = getType();
            printToolNodeHeader();
            showToolNodesByTypeId(toolHead, type);
            break;
        case 14:
            printf("Podaj typ narzedzia do wyswietlenia: "); id = getInt(10000);
            printToolNodeHeader();
            showToolNodesByType(toolHead, id);
            break;
        case 15:
            printf("Podaj opis narzedzia do wyswietlenia: "); name = getString();
            printToolNodeHeader();
            showToolNodesByDesc(toolHead, name);
            break;
        case 16:
            writeDatabaseToFile("Dane.txt", "Dane.bak");
            printf("Pomyslnie zapisano dane do pliku.\n");
            break;
        case 0:
            if (modified) {
                while (1) {
                    printf("Czy zapisac zmiany do pliku? (T/N): "); name = getString();
                    switch (name[0]) {
                        case 'T':
                        case 't':
                            writeDatabaseToFile("Dane.txt", "Dane.bak");
                        case 'N':
                        case 'n':
                            return 0;
                        default:
                            printf("Nierozpoznana opcja.");
                            break;
                    }
                }
            }
            return 0;
        default:
            printf("Bledna opcja!\n\n");
            break;
    }
    free(name);
    return 1;
}

void readDatabaseFromFile(char *filename) {
    int i, j, stores, tools, id, type;
    char *name, *desc, typeIdChar;
    ToolType typeId;
    FILE *file = fopen(filename, "rt");
    if (!file) {
        printf("Blad przy otwieranie pliku!\n");
    }
    printf("Wczytuje dane z pliku %s\n", filename);

    /* Reading stores */
    fscanf(file, "%d", &stores);
    for (i = 0; i < stores; ++i) {
        name = malloc(128 * sizeof(char));
        fscanf(file, "%s", name);
        if (getStoreNodeByName(storeHead, name)) {
            printf("Blad przy dodawaniu magazynu: %s. Magazyn istnieje.\n", name);
            continue;
        }
        addStoreNode(createStoreNode(name));
        printf("Wczytano magazyn: %s\n", name);
    }

    /* Reading tools */
    fscanf(file, "%d", &tools);
    for (i = 0; i < tools; ++i) {
        desc = malloc(128 * sizeof(char));
        fscanf(file, "%d %s %d %s", &id, &typeIdChar, &type, desc);
        typeId = typeIdChar == 'D' ? 0 : 1;
        if (getToolNodeById(toolHead, id)) {
            printf("Blad przy dodawaniu narzedzia: %d. Narzedzie istnieje.\n", id);
            continue;
        }
        addToolNode(createToolNode(id, typeId, type, desc));
        printf("Wczytano narzedzie:\n");
        printToolNode(createToolNode(id, typeId, type, desc), 0);
    }

    /* Reading connections */
    fscanf(file, "%d", &stores);
    printf("%d\n", stores);
    for (i = 0; i < stores; ++i) {
        name = malloc(128 * sizeof(char));
        fscanf(file, "%s", name);
        fscanf(file, "%d", &tools);
        printf("%s %d\n", name, tools);
        for (j = 0; j < tools; ++j) {
            fscanf(file, "%d", &id);
            addToolToStore(name, id);
            addStoreToTool(id, name);
        }
        free(name);
    }
    fclose(file);
}

void writeDatabaseToFile(char *filename, char *tempName) {
    FILE *file;
    int stores;
    StoreNode *storePtr = storeHead;
    ToolNode *toolPtr = toolHead;

    rename(filename, tempName);
    file = fopen(filename, "wt");
    stores = countStores(storeHead);
    fprintf(file, "%d\n", stores);
    while (storePtr) {
        fprintf(file, "%s\n", getStoreNodeAsString(storePtr));
        storePtr = storePtr->next;
    }
    fprintf(file, "\n%d\n", countTools(toolHead));
    while (toolPtr) {
        fprintf(file, "%s\n", getToolNodeAsString(toolPtr));
        toolPtr = toolPtr->next;
    }
    fprintf(file, "\n%d\n", stores);
    storePtr = storeHead;
    while (storePtr) {
        fprintf(file, "%s %d\n", getStoreNodeAsString(storePtr), countTools(storePtr->tools));
        toolPtr = storePtr->tools;
        while (toolPtr) {
            fprintf(file, "%d ", toolPtr->data->id);
            toolPtr = toolPtr->next;
        }
        fprintf(file, "\n");
        storePtr = storePtr->next;
    }
}

int countStores(StoreNode *node) {
    if (!node) {
        return 0;
    }
    return 1 + countStores(node->next);
}

int countTools(ToolNode *node) {
    if (!node) {
        return 0;
    }
    return 1 + countTools(node->next);
}

int main() {
    readDatabaseFromFile("Dane.txt");
    while (showMenu());
    return 0;
}
