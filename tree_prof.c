#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


int main(int argc, char*argv[]){
  if(argc !=2){
    printf("You provide enogh argument");
    exit(-1);
  }

  else {
  int n = atoi(argv[1]); 
  tree_t *tree = tree_new();
  char buff[10];
  while(n < 100000){
    list_t* shelf_list = list_new(); 
    snprintf(buff, 10, "%d", n);
    ware *type_ware = createNewWare(strdup(buff), "Place holder", n, shelf_list);
    insertNode(tree, get_name(type_ware),  type_ware, comparevoid);
    ++n; 
  }
  }
  return 0; 
}
