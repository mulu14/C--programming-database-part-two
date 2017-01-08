#ifndef _uppgift1_h
#define _uppgift1_h
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "ware.h"

ware*insertInfo_at_ware();
char *set_name(ware*item); 
char *set_des(ware*item); 
int set_price(ware*item);
void remove_inserted_info(ware*item, tree_t*tree);

#endif
