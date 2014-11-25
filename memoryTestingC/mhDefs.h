/*
Name: Shaheen Ghazazani
www.shaiwanghazazani.com 
*/

#define MAX_BLK 16 
#define MAX_STR 32
#define C_TRUE  1 //used in while loop iterations.  
#define C_FALSE 0


typedef struct {
		void *addr;
		int size;
		char tag[MAX_STR];
} BlockType;

typedef struct Node{ 
	BlockType *data;//store all the blocks data
	struct Node *next;  //get the next one in the list
} NodeType;

typedef struct {
	NodeType *start; 
} HeapType;

//below are function declarations
void  mh_init(HeapType *);
void  mh_cleanup(HeapType*);
void* mh_alloc(HeapType*, int, char*);
void  mh_dealloc(HeapType*, void*);
int   mh_count(HeapType*);
void  mh_dump(HeapType*);
void  mh_collect(HeapType*);
