#include "mm.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#define MINUNIT 1024 /*minimum units to request*/

union block{
	struct {
		union block *next; /*next block*/
		int size; /*size of block*/
	}s;
	long x; /*force aligment of blocks*/
};
typedef union block Block;
static Block freelist;
static Block *freeliststart = NULL;

/*ask OS for more space*/
static Block *morespace(int num_units){
	void *p;
	Block *up;
	if(num_units<MINUNIT) num_units=MINUNIT;
	p=sbrk(num_units*sizeof(Block));
	if(p==(void*)-1) /*no more space*/
		return NULL;
	up=(Block*) p;
	up->s.size=num_units;
	myfree((void*)(up+1));
	return freeliststart;
}

void* mymalloc(int size) {
	Block *current, *prev;
	int num_units = (size+sizeof(Block)-1)/sizeof(Block)+1;
	prev=freeliststart;
	if(prev==NULL){ /*no free list yet*/
		freelist.s.next = freeliststart = prev = &freelist; /*points to self*/
		freelist.s.size = 0;
	}
	for(current=prev->s.next;;prev=current,current=current->s.next){
		if(current->s.size>=num_units){ /*big enough*/		
			if(current->s.size==num_units) /*exactly same*/
				prev->s.next=current->s.next;
			else{
				current->s.size-=num_units;
				current+=current->s.size;
				current->s.size=num_units;
			}
			freeliststart=prev;
			return (void*)(current+1);
		}
		if(current==freeliststart){ /*wrapped around free list*/
			current=morespace(num_units);
			if(current==NULL) return NULL; /*no more space*/
		}
	}
}

void* mycalloc(int n, int size){
	void* temp = (void*)mymalloc(n*size);
	memset(temp,0,size);
	return temp;
 }
 
void* myrealloc(void* tar1, int size){
	if(!tar1) return mymalloc(size); /*if tar1 is null, realloc acts like malloc*/
	Block *tar_info = (Block*)tar1-1;
	if(tar_info->s.size>=size){
		/*we have enough space, free the once don't need*/
		/*free code*/
		return tar1;
	}
	/*Need to realloc, malloc new space and free old space
	copy old data to new space*/
	void* new_ptr = mymalloc(size);
	if(!new_ptr) return NULL; /*no more space*/
	memcpy(new_ptr,tar1,tar_info->s.size);
	myfree(tar1);
	return new_ptr;
}
 
void myfree(void* target){
	Block *bp, *p;
	bp = (Block*)target-1; /*points to block header*/
	for(p=freeliststart;!(bp>p && bp<p->s.next); p=p->s.next)
		if(p>=p->s.next && (p<bp || p->s.next>bp)) break;
	if(bp+bp->s.size == p->s.next){ /*join to upper*/
		bp->s.size+=p->s.next->s.size;
		bp->s.next=p->s.next->s.next;
	}
	else bp->s.next=p->s.next;
	if(p+p->s.size == bp){ /*join to lower*/
		p->s.size+=bp->s.size;
		p->s.next=bp->s.next;
	}
	else p->s.next=bp;
	freeliststart=p;
}

