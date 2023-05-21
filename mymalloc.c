#include <stdio.h>
#include "mymalloc.h"

#define SIZE_MEMORY 4096 //size of memory array

static char memory[SIZE_MEMORY];

//size of block = 16 bytes, 8 for struct, and 8 for struct*
struct block{ 
    int size;
    int free;
    struct block *next;
};

//create head of list  and iniitliaze to index 0 in memory;
struct block *head = (struct block*)(&memory[0]);

//creates node
int *addNode(int _size_){
    
    struct block *temp = head;
    int bytes_used = 0; //debugging line
    if(search_EmptyBlock()!=0){
        int *ptr = search_EmptyBlock();
        return ptr;
    } 
    //intialization of head
    if(head->size==NULL){
        head->size=_size_;
        head->free=0;
        head->next= NULL;
        bytes_used = bytes_used+temp->size+sizeof(struct block);
    }else{
        
        //iterate
        while(temp!=NULL){
            bytes_used = bytes_used+temp->size+sizeof(struct block);
            if(temp->next==NULL){
                break;
            }
            temp = temp->next;
        }
        //bounds check before creating a new block
        if(_size_>bytes_used+_size_){
            printf("CANNOT CREATE BLOCK, OUT_OF_BOUNDS\n"); //temp error message
        } else{
            printf("BLOCK CREATED\n");  //debugging line 
            struct block *newNode = (struct block*)(&memory[bytes_used]);
            temp->next = newNode;
            newNode->size = _size_;
            newNode->free = 0;
            newNode->next = NULL;
            temp = newNode;

            bytes_used = bytes_used+temp->size+sizeof(struct block); //debugging line
            printf("size of block: %d\n",temp->size+sizeof(struct block));//debugging line
        }
    }

    printf("bytes used: %d\n", bytes_used); //debbuing line

    return temp;    
}

//coalesce( *ptr ) takes a ptr to a block, then checks if adjacent blocks are free, then coalesces them
void coalesce(struct block* ptr){ 
    struct block* current = head;

    //iterate through linkde list
    while(current!=NULL){
        if(current->next==ptr){
            printf("found previous\n"); //debugging line
            if(current->free==1 && ptr->free==1){
                //make the current->next point to the ptr->next; which in turn will combine both blocks
                //if you had blocks a, b, c, d: current = B, free(C), current->next = D
                // current->size = B->size + C->size
                // current->free = 0;

                current->next=ptr->next;
                printf("size of current: %d\n", current->size); //debugging line
                printf("size of previous: %d\n", ptr->size);    //debugging line
                current->size=current->size+ptr->size;
                current->free=1;
                printf("size of coalesced: %d\n", current->size); //debugging line
                break;
            }
        } 
        current = current->next;
    }
}

//changes block 'free' parameter to '1' (TRUE), "freeing" up the block
void myfree(void *ptr, char*file, int line){
    struct block* target = ptr;
    target->free = 1;
    
    //call coalesce function to check if there are adjacent chunks which could be freed up
    coalesce(target);
}

//function for debugging purposes
int prntArray(){
    for(int i=0; i<75;i++){
        printf("index; %d, value: %d\n",i,memory[i]);
    }
    return 0;
}

//searches the list for an empty block
int *search_EmptyBlock(int target_size){
    struct block* temp = head;
    
    //iterate through list
    while(temp!=NULL){
        if(temp->next=NULL){    //return 0 if it gets to the end with no free block
            printf("NO FREE BLOCKS");
            return 0;   
        }
        if(temp->free=1){   //return ptr to the free block
            if(temp->size==target_size){
                printf("FOUND A FREE BLOCK\n");
                return temp;
            } else if(temp->size<target_size){
                //INSERT A FUNCTION TO PARTITION BLOCKS
                printf("PARTITIONING FUNCTION REQURED\n");    //debugging line
            }
        }
        temp=temp->next;
    }
    
}

void *mymalloc(int size, char*file, int line){
    int *ptr = addNode(size);
    return ptr;
}

/*
TO-DO:
    1)  int *partition(){
            if memory blocks cannot be created, find a free memory block and partition it 
                if size_requested<size_of_free_block
        }
    2)  boolean boundsChecker(){
            if(size_requested+sizeof(Struct block) > size_available){
                ERROR
            } else{ 
                return true;
            }}
    3)  int byte_used(){
        int bytes_used;
        while(block!=NULL){
            bytes_used = bytes_used+block->size+sizeof(struct block);
            block = block->next;
        }
        return bytes_used;
    }
*/

/*
-> ideas from class, coalesce when you free()
    -> check adjascent blocks if they are free, then combine them
*/





