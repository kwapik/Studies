typedef enum {D, M} ToolType;

typedef struct Tool {
    int id;
    ToolType typeId;
    int type;
    char* desc;
} Tool;

typedef struct ToolNode {
    Tool *data;
    struct ToolNode *next;
    struct StoreNode *stores;
} ToolNode;

typedef struct Store {
    char *name;
} Store;

typedef struct StoreNode {
    Store *data;
    ToolNode *tools;
    struct StoreNode *next;
} StoreNode;

/* Creating and adding objects */

ToolNode* createToolNode(int id, ToolType typeId, int type, char* desc);
StoreNode* createStoreNode(char *name);

void addToolNode(ToolNode *node);
void addStoreNode(StoreNode *node);

void addToolToStore(char *name, int id);
void addStoreToTool(int id, char *name);

ToolNode* readToolNodeFromUser();
StoreNode* readStoreNodeFromUser();

int getInt(int max);
int getType();
char* getString();


/* Getting objects */

ToolNode* getToolNodeById(ToolNode *node, int id);
StoreNode* getStoreNodeByName(StoreNode *node, char *name);


/* Deleting objects */

StoreNode* deleteStoreNodeByName(StoreNode *node, char *name);
void deleteStoreNodeFromToolByNameRecursive(ToolNode *node, char *name);

ToolNode* deleteToolNodeById(ToolNode *node, int id);
void deleteToolNodeFromStoreByIdRecursive(StoreNode *node, int id);


/* Printing objects */

char *getStoreNodeAsString(StoreNode *node);
char *getToolNodeAsString(ToolNode *node);

void printToolNodeHeader();
void printStoreNodeHeader();

void printToolNode(ToolNode *node, int printStores);
void printStoreNode(StoreNode *node, int printTools);

void printToolNodeRecursive(ToolNode *node, int printStores);
void printStoreNodeRecursive(StoreNode *node, int printTools);

void showToolNodesById(ToolNode *node, int id);
void showToolNodesByTypeId(ToolNode *node, ToolType type);
void showToolNodesByType(ToolNode  *node, int type);
void showToolNodesByDesc(ToolNode *node, char *desc);


/* Reading from database */

void readDatabaseFromFile(char *filename);


/* Writing to database */

void writeDatabaseToFile(char *filename, char *tempName);
int countStores(StoreNode *node);
int countTools(ToolNode *node);

/* Sorting */
void sortTools(ToolNode *node, int (*comparator)(ToolNode*, ToolNode*));
/*void sortStores(ToolNode *node, int (*comparator)(StoreNode*, StoreNode*);*/

void swapTool(ToolNode *tool1, ToolNode *tool2);

int toolComparator1(ToolNode *node1, ToolNode *node2);

/* Menu showing */

int showMenu();
