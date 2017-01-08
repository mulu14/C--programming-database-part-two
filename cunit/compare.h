#ifndef _ASK_H_
#define _ASK_H_
#include<stdbool.h>


typedef int(*cmp_func)(void *, void *);
int compare(void *p1, void*p2);
int comparevoid( void *a,void *b); 
#endif
