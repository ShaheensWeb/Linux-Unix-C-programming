/*
Name: Shaheen Ghazazani
www.shaiwanghazazani.com
*/

//standard c imports
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//files given with a3, struct definitions + function declarations
#include "mhDefs.h"
#include "stuDefs.h"

int main(){
	HeapType *heap = calloc(1, sizeof(HeapType));; //initialize HeapType struct
	// all 'ptrx' variables are my testing
	void  *ptr1, *ptr2, *ptr3, *ptr4, *ptrx1, *ptrx2, *ptrx3, *ptrx4, *ptrx5;  
	//initialize heap variable using block count set to 0 and calloc of mem		
	mh_init(heap);

  ptr1 = mh_alloc(heap, 5*sizeof(int), "ints");
  ptr2 = mh_alloc(heap, 10*sizeof(double), "doubles");
  ptr3 = mh_alloc(heap, 8*sizeof(char), "chars");
  ptr4 = mh_alloc(heap, 12*sizeof(StudentType), "Students");

  printf("\nDUMP 1, byte count = %d\n", mh_count(heap));

  mh_dump(heap);

  mh_dealloc(heap, ptr1);
  mh_dealloc(heap, ptr2);
  mh_dealloc(heap, ptr3);

  printf("\nDUMP 2, byte count = %d\n", mh_count(heap));
  mh_dump(heap);

  mh_collect(heap);

  printf("\nDUMP 3, byte count = %d\n", mh_count(heap));
	mh_dealloc(heap, ptr4); 
  mh_dump(heap);

	//below ptrx1-5 are my personal tests. 

	printf("\n\nBELOW are allocations of each individual ptrx1-5\n\n");
	
	//declare void variable to memory allocation type 
	ptrx1 = mh_alloc(heap, 9*sizeof(HumanTesterOne), "HumanTester-One"); 
	//print out count of memory to user in proper format
  printf("\nDUMP 4, byte-count= %d\n", mh_count(heap)); 
	mh_dump(heap); 

	ptrx2 = mh_alloc(heap, 12*sizeof(HumanTesterTwo), "HumanTester-Two");
	printf("\nDUMP 5, byte-count= %d\n", mh_count(heap));
	mh_dump(heap);

	ptrx3 = mh_alloc(heap, 3*sizeof(HumanTesterThree), "HumanTester-Three");
	printf("\nDUMP 6, byte-count= %d\n", mh_count(heap));
	mh_dump(heap);

	ptrx4 = mh_alloc(heap, 8*sizeof(CollegeType), "CollegeType");
	printf("\nDUMP 7, byte-count= %d\n", mh_count(heap));
	mh_dump(heap);

	ptrx5 = mh_alloc(heap, 21*sizeof(IncomeType), "IncomeType");
	printf("\nDUMP 8, byte-count= %d\n", mh_count(heap));
	mh_dump(heap);

	printf("\n\nBELOW are de-allocations of each individual ptrx1-5\n\n");

	mh_dealloc(heap, ptrx1); //deallocate certain tester off the heap
	printf("\nDUMP 9, byte-count= %d\n", mh_count(heap)); //count after dealloc
	mh_dump(heap); 

	mh_dealloc(heap, ptrx2);
	printf("\nDUMP 10, byte-count= %d\n", mh_count(heap));
	mh_dump(heap);

	mh_dealloc(heap, ptrx3);
	printf("\nDUMP 11, byte-count= %d\n", mh_count(heap));
	mh_dump(heap);

	mh_dealloc(heap, ptrx4);
	printf("\nDUMP 12, byte-count= %d\n", mh_count(heap));
	mh_dump(heap);

	mh_dealloc(heap, ptrx5);
	printf("\nDUMP 13, byte-count= %d\n", mh_count(heap));
	mh_dump(heap);
		
	//collect, cleanup, and free the remaining HeapType *heap
	mh_collect(heap);
	printf("\n\n\n");
	mh_cleanup(heap);
	free(heap);
	return 0;
}

void mh_init(HeapType *heap){
	/*FUNCTION_NAME: mh_init ; INPUTS: pointer looking at heap variable;
	PURPOSE: init the heap variables numBlocks, and blocks */
	heap->start = NULL; //declare the starting node to null
}	

void *mh_alloc(HeapType *heap, int n, char *label){
	/*FUNCTION_NAME: *mh_alloc, INPUTS: pointer to heap, size of new block mem 
	in bytes, use of the new block ; PURPOSE: allocate new block of memory of 
	size n bytes dynamically*/
  NodeType *nodeStart = heap->start; //go to front of list
	if (nodeStart == NULL){ //if it is null
		nodeStart = (NodeType*) calloc(1, sizeof(NodeType)); //allocate node 
		nodeStart->data = (BlockType*) calloc(1, sizeof(BlockType)); //allocate data
		nodeStart->next = NULL; //make next null for next mh_alloc call
		nodeStart->data->size = n; //set size to given input param n
		nodeStart->data->addr = calloc(1, n); 
		strncpy(nodeStart->data->tag, label, MAX_STR);
		nodeStart->data->tag[MAX_STR - 1] = '\0';
		heap->start = nodeStart;		
		return nodeStart;
	}
	while(C_TRUE){ //otherwise not null
		if(nodeStart->next == NULL){ //if next is null
			nodeStart->next = (NodeType*) calloc(1, sizeof(NodeType));
			nodeStart->next->data = (BlockType*) calloc(1, sizeof(BlockType));	
			nodeStart->next->next = NULL;
			nodeStart->next->data->size = n;
			nodeStart->next->data->addr = calloc(1, n);
			strncpy(nodeStart->next->data->tag, label, MAX_STR);		
			nodeStart->next->data->tag[MAX_STR -1] = '\0';
			return nodeStart->next;	
		}
	nodeStart = nodeStart->next;
	}
}

void mh_cleanup(HeapType *heap){
	/*FUNCTION_NAME: mh_cleanup ; INPUTS: pointer looking at heap variable; 
	PURPOSE: free memory allocated for all blocks in heap parameter */
  NodeType *hold, *nodeStart = heap->start;
	while(C_TRUE){
		heap->start = nodeStart;	//from start of node
		if (nodeStart == NULL){ //if the node is null
			return; //break
		}
		free(nodeStart->data->addr); //otherwise not null, lets free addr
		free(nodeStart->data);//free data
		hold = nodeStart->next; //hold next node in temp holder named hold
		free(nodeStart); //free final node
		nodeStart = hold;  //go back to next node
	}
}

void mh_collect(HeapType *heap){
	/*FUNCTION_NAME: mh_collect ; INPUTS: pointer to heap variable; 
	PURPOSE: deallocaed all memory tracked in the blocks of the heap */
	NodeType *hold, *nodeStart = heap->start;
	while(C_TRUE){
		heap->start = nodeStart; 
		if (nodeStart == NULL){
			return;
		}
		free(nodeStart->data->addr);
		free(nodeStart->data);
		hold = nodeStart->next;
		free(nodeStart);
		nodeStart = hold; 
	}
}

void mh_dealloc(HeapType *heap, void *addr){
	/* FUNCTION_NAME: mh_dealloc ; INPUTS: pointer to heap variable, 
	address of a memory block ; PURPOSE: find block element in heap and 
	set to not reserved. Deallocates memory at the specific memory address */
	NodeType *hold, *nodeStart = heap->start;
	if (nodeStart == NULL){ //loop is empty
		return;
	}
	if (addr == nodeStart){ //if addr is equal to nodeStart we found a node
		if(nodeStart->next == NULL){
			heap->start = NULL; //set heap start to null if the next node is Null
		}else{
			heap->start = nodeStart->next; //go to next block so we dont lose pointer
		}
		free(nodeStart->data->addr); //free the addr
		free(nodeStart->data); //free the data
		free(nodeStart); //free the node
		return; 
	}
	while(C_TRUE){ //otherwise
		if (addr == nodeStart->next){ //if addr is next node
			hold = nodeStart->next; //hold the node we want
			if (hold->next == NULL){ //if null set nodeStart next to null
				nodeStart->next = NULL;			
			}else{
				nodeStart->next = hold->next; 			
			}
			free(hold->data->addr); //free all three aspects of hold var
			free(hold->data);
			free(hold);		
			return;		
	}
	nodeStart = nodeStart->next; //used to iterate
	if(nodeStart == NULL){ //if null break, we reached end
		break;
	}
	}
}

void mh_dump(HeapType *heap){
	/*FUNCTION_NAME: mh_dump ; INPUTS: pointer to heap variable ; 
	PURPOSE: prints info about every block in the heap*/
	NodeType *nodeStart = heap->start;
	while(C_TRUE){	
		if (nodeStart == NULL){
			return;		
		}	
		printf("%20s:%7d bytes are being stored at %p \n", 
			nodeStart->data->tag, nodeStart->data->size, nodeStart->data->addr); 
		nodeStart = nodeStart->next; 
	}	
}

int mh_count(HeapType *heap){
	/*FUNCTION_NAME: mh_count ; INPUTS: pointer to heap variable ; 
	PURPOSE: returns number of bytes reserved in all blocks of heap */
  NodeType *nodeStart = heap->start;
	int totalVal = 0;  
	while(C_TRUE){  
		if (nodeStart == NULL){
			return totalVal;
		}
		totalVal += nodeStart->data->size; 	
		nodeStart = nodeStart->next;
	}
}
