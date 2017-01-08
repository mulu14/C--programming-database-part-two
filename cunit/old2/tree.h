#ifndef __tree_h__
#define __tree_h__

#include <stdbool.h>
#include "shelf.h"
#include "list.h"
#include "ware.h"
#include "shelf.h"
//#include "compare.h"

/// Define struct tree in your .c file not here! (why?)
typedef struct node node_t;
typedef struct tree tree_t; 
void print (node_t*root); 
tree_t *tree_new();
node_t* node_new(); 
bool isShelftaken(tree_t *root, shelf *shelfName);
int tree_size(node_t*root);
tree_t *tree_head(tree_t*root);
void *return_Node_name(node_t*name); 
void*get_name_node(tree_t *root);
node_t*find_node(tree_t*root, char*Itemname);
int tree_depth(node_t *node);
node_t**insertNode(tree_t *root, void*data);
void  print_order(tree_t * root);
bool find_shelf(tree_t *root, void*shelfName); 
node_t * min_Value(node_t* root);
bool remove_Node(tree_t *root, void*ware_name); 
void* return_ware(tree_t*root);
node_t*return_node_head(tree_t *root);
void *returnNodeware(node_t*wareName);
void print_tree_nodes(tree_t*root);
void printTree(tree_t*root); 
void free_tree(node_t*node);
void blanced_tree(tree_t *tree); 

#endif
