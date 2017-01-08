#ifndef _shelf2_h
#define _shelf2_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "shelf.h"
shelf *new_shelf();
//int set_quantity(shelf*address);
char *set_shelf(shelf *address);
void remove_inserted_shelf(shelf*address); 

#endif
