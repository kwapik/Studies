typedef enum {M, D} shipType;

struct ship {
    char *flag;
    shipType type;
    int length;
    int dwt;
};

struct shipNode {
    int number;
    struct ship data;
    struct shipNode *next;
};

int getNextNumber();
struct shipNode* createNode(char *flag, shipType type, int length, int dwt);
void addNode(struct shipNode *node);
char* getFlag();
int getType();
int getLength();
int getDwt();
struct shipNode* readNodeFromUser();
void sort(int (*ccomparator)(struct shipNode*, struct shipNode*));
void swap(struct shipNode *n1, struct shipNode *n2);
int comparator1(struct shipNode *n1, struct shipNode *n2);
int comparator2(struct shipNode *n1, struct shipNode *n2);
int comparator3(struct shipNode *n1, struct shipNode *n2);
void printNode(struct shipNode *node);
void printNodesInOrder(struct shipNode *node);
void printNodesByType(struct shipNode *node, shipType type);
void showMenu();
