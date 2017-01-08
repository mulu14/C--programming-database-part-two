#ifndef _shelf_h
#define _shelf_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


typedef struct _shelf shelf;
shelf * makeShelf(char *shelfname, int quantity); 
char *get_shelf(shelf*address);
int get_quantity(shelf*address);
void add_amount(shelf *s, int *sum);
void destroy_shelf(shelf *address);


#endif
