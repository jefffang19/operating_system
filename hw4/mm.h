#ifndef MM_H
#define MM_H

void* mymalloc(int size);
void* mycalloc(int n, int size);
void* myrealloc(void* tar1, int size);
void myfree(void* target);

#endif
