
#ifndef mymalloc_h
#define mymalloc_h

#define malloc(s)   mymalloc(s, __FILE__, __LINE__)
#define free(p)     myfree(p, __FILE__, __LINE__)

void *mymalloc(int size, char *file, int line);
void myfree(void *ptr, char *file, int line);
int prntArray();

#endif