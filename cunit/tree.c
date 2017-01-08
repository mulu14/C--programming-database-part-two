#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"


/*!\struct node
 *  element is member of node struct and it is void pointer
 *  left is member of  struct node
 * right is member of  struct node
 * struct for  node holds void pointer as element and left and right nodes,
 * which provide a bulding block for larger database creation  
 *A tree is composed of a collection of nodes, where each node has some associated data and a set of children.
 */
struct node{
  void *key;             /*!< void pointer to */
  void *data;
  struct node *left;
  struct node *right;
	
};

/*!\struct tree
 *  root is member of tree and  pointer to  structure node
 * struct tree is a building block for large database which hold pointer to the root of the tree 
 */

struct tree{
  struct node*root;	 
};

/*\fn node_t*node_new(void*element)
 *\param element is  void pointer
 * The function create new node 
*/

node_t* node_new(void*data, void*key){
  node_t * newNode = malloc(sizeof(node_t));
  newNode-> data = data;
  newNode-> key = key;
  newNode -> left = NULL;
  newNode -> right = NULL;
  return newNode; 
};


/*\fn tree_t*tree_new(void)
 *The function create a new tree, which is also basic nalock for building data structure
*/

tree_t *tree_new(){
	tree_t *result = malloc(sizeof(tree_t));
	result -> root = NULL;  
	return result; 
					  
}

/*\fn void*return_node_name(node_t*node)
 *\param node pointer to  node_t
 * The function return the name of the node, which is a key to node
*/
void *return_Node_name(node_t *node){
	return get_name(node -> data); 
}
/*\fn node_t*node_head(tree_t*tree)
 *\param tree is pointer to  tree_t
 * The function return the root of the tree
*/

node_t*return_node_head(tree_t *tree){
	return tree -> root; 
}
/*\fn void*return_ware(tree*tree)
 *\param  tree pointer to tree_t 
 * The function return  item from the root tree 
*/
void *return_ware(tree_t *tree){
	return tree -> root ->data; 
}
/*\fn returnNodeware(node_t*node)
 *\param  node pointer to  node_t
 * The function return item from a given node
*/

void *returnNodeware(node_t*node){
	return node -> data; 
}

void*returnNodekey(node_t*node){
  return node -> key; 
}

/*\fn  tree_size(node_t*node)
 *\param node pointer to  node_t
 * The function calculate the number of nodes on the binary tree
*/

int tree_size(node_t* node){
  if(node == NULL){
    return 0;}
  else{
    return (tree_size(node-> left) + 1 + tree_size(node->right));
  }
}


/*\fn insertaux(node_t**node, void*element)
 *\param node pointer to  node_t
 *\param element void
 * insertaux is auxiliary function to insert node into tree. If the node is inserted, the function return true else it return false
*/

bool insertaux(node_t**node, void *dataKey,  void *data, cmp_func cmp){

  if(*node == NULL){
    *node =  node_new(data, dataKey);
    return true; 
  }

  else if(cmp((*node)->key,dataKey ) == 0){
    return false; 
  }
  else if(cmp((*node) ->key ,dataKey) < 0){

    insertaux(&((*node)->left),dataKey, data, cmp);
  }
	
  else{
 
    insertaux(&((*node) ->right),dataKey, data, cmp); 
  }
  return false; 
}
/*\fn inserNode(tree_t*tree, void*element)
 *\param tree pointer to  tree_t
 *\param element pointer to  void
 * The function insert node into tree
*/

bool insertNode(tree_t *tree, void*dataKey, void*data, cmp_func cmp){
  if(tree -> root == NULL){
    tree ->root = node_new(data, dataKey);
    return true; 	
  }
  insertaux(&(tree -> root), dataKey, data, cmp);
  return true; 
}


/*\fn isShelftakenaux(node_t*node, shelf*shelfName)
 *\param node pointer to node_t
 *\param shelfName pointer to  shelf
 * The function is auxiliary functio to check if the shelf is taken or not. The function return false, if the shelf is taken  
*/

bool isShelftakenaux(node_t *node, void *shelfName, cmp_func cmp){
  if(node ==NULL)
    return false;
  else {
    if(isexist(return_list(returnNodeware(node)) ,shelfName, comparevoid) == true){
      return true;
	
    }}
  return isShelftakenaux(node -> left, shelfName, cmp) || isShelftakenaux(node -> right, shelfName, cmp); 
}

/*\fn isShelftaken(tree_t*tree, shelf*shelfName)
 *\param tree pointer to tree_t
 *\param shelfName pointer to  shelf
 * The function check if the shelf is taken or not. The function return false, if the shelf is taken.
*/

bool isShelftaken(tree_t *tree, void *shelfName,  cmp_func cmp){
  if(tree ==NULL)
    return false;
  return isShelftakenaux(tree -> root, shelfName, cmp); 
}



/*\fn node_t*findaux(node_t*node, void*element)
 *\brief crate a node with element
 *\param node pointer to node_t
 *\param element pointer to void
 * The function is auxiliary function to search the node on the tree, if the node existed, it will return the node. 
   Otherwise it will return NULL; 
*/

node_t*findaux(node_t *node, void*searched_element, cmp_func cmp ){
  if (node == NULL){
  return NULL;}
  
  else {
		
    if(cmp(node->key, searched_element)== 0){
      
      return node;
    }
    else if(cmp(node->key, searched_element) < 0){						
      return findaux(node -> left, searched_element, cmp);
    }
    else {
      return findaux(node -> right, searched_element, cmp);
    }
  }
}
   

/*\fn node_t*find_node(tree_t*tree, char*element)
 *\brief crate a node with element
 *\param node pointer to  node_t 
 *\param element pointer to char
 * The function search the node on the tree, if the node existed, it will return the node. Otherwise it will return NULL. 
*/


node_t*find_node(tree_t*tree, void*searched_element, cmp_func cmp){
  if(tree -> root == NULL){
    return NULL; }
  return findaux(tree -> root, searched_element, cmp); 
}



/*\fn node_t*min_Value(node_t*node)
 *\param node pointer to node_t
 * The function search and find the minimum value from tree, which is auxiliary function for delete node
*/

node_t * min_value_right(node_t* node){
  if(node == NULL){
    return NULL; 
  }
  else {
    node_t *current =node ; 
	
    while (current -> left!=NULL){
      current= current ->left;}
    return current;
  }
}

/*\fn bool removeaux (node_t**root, void*element)
 *\param node pointer to  node_t 
 *\param element pointer to  void
 * The function is auxiliary functio which remove the item if it exist on the tree and return true if succesfull, otherwise return false; 
*/
bool removeaux(node_t **node, void*node_to_remove, cmp_func cmp){

  if(*node == NULL) {
    return false;
  }
  else if(cmp((*node) ->key, node_to_remove) < 0){
    return removeaux(&((*node)-> left), node_to_remove, cmp);
  }
  else if(cmp((*node) ->key, node_to_remove) > 0){
    return removeaux(&(*node)-> right, node_to_remove, cmp); 
      }

  else{
    /* delete root and the root has no left or right child*/
		
    if( (*node)-> left == NULL && (*node) -> right == NULL){
      free(*node);
      *node = NULL;
      return true; 
    }
    /* delete root when the root has only right child*/
    else if( (*node) -> left == NULL && (*node) -> right != NULL){
      node_t*var  = *node; 
      *node = (*node) -> right; 
      free(var); 
      return true;
    }
    /* delete root when the root has  only left child*/
    else if((*node) -> left != NULL && (*node) ->right == NULL){
      node_t *var = *node;
      *node = (*node) -> left;  
      free(var); 
      return true; 
    }
    /* delete root when the root has two child*/
    else{
      node_t *min = min_value_right((*node) ->right);
      void*min_key = returnNodekey(min); 
      *node = min; 
      return removeaux(node, min_key, cmp);
    }
	
		}
	return true; 
	}

/*\fn bool remove_Node(tree_t*tree, void*element)
 *\param tree  pointer to  tree_t 
 *\param  element pointer to  void
 * The function remove the element if it exist on the tree and return true if succesfull, otherwise return false; 
*/
bool remove_Node(tree_t*tree, void*node_to_remove, cmp_func cmp){
  if(tree -> root == NULL)
    return true;
  removeaux(&(tree -> root), node_to_remove, cmp);
  return true; 
}

/*\fn void print(node_t*node)
 *\param node pointer to  node_t
 * The function print all the element at tree
*/

void print (node_t*node){
  if(node == NULL)
    return; 
  {
    print(node -> left); 
    printf("%s\n", get_name(returnNodeware(node)));
    print(node -> right);
  }
}

/*\fn int cmpstringp(const void*p1, const void*p2)
 *\param p1 const void pointer
 \*param p2  const void pointer
 * The function takes two void pointer argument and compare two of them and return the computed result.
 * In the body part, the void pointers are casted struct node 
*/

int compareStruct(const void *a, const void *b) 
{ 
  node_t *ia = (node_t *)a;
  node_t *ib = (node_t *)b;
  return strcmp(ia->key, ib->key);

} 
 
/*\fn void dumpTree(node_t*node, node_t*arry[], int *p_t)
 *\param node is pointer to node_t
 *\param arry  is  ponter to char array
 *\param p_t  is pointer to int 
 * The function turn binary tree into node array
*/
void dumpTree(node_t *node, node_t *array[], int *p_t){
  if(node){
    array[*p_t] = node;
    * p_t += 1;
    dumpTree(node-> left, array, p_t);   
    dumpTree(node -> right, array, p_t);
  }
  else {
  } 
}
/*\fn void free_tree(node_t*node)
 *\param node node_t
 * The function recursively free all the node pointer from tree; 
*/


void free_tree(node_t*node){
  if(node != NULL){ 
    free_tree(node -> left);
    free_tree(node -> right); 
    destroy_ware(returnNodeware(node));
 
    free(node);
  }
		
}

/*\fn void sortNode(node_t*nodeArray[], int size, node_t*node)
 *\param  nodeArray is pointer  to array of node 
 *\param  size is int that specify the size of array
 *\param  node is pointer to node_t 
 *The  function sort a node array in ascending order
*/

void dump_sort_Node(node_t*nodeArray[], int size, node_t*node){
  int j; 
  dumpTree(node, nodeArray, &j); 
  qsort(nodeArray, size -1, sizeof(node_t*), compareStruct); 	
}

/*\fn node_t** balance_node(node_t*array[], int first, int last)
 *\param  array is pointer  to array of node 
 *\param  first is int that point to the fist element of the array
 *\param  last is int that point the last element of the array
 * The function is  auxiliary function for createing balanced binary node from a given sorted array node
*/

node_t**balance_node_insert(node_t**node, node_t*array[], int first, int last){
  int middel = (first + last)/2;
	
  if (first < last){
    *node = node_new(returnNodeware(array[middel]), get_name(returnNodeware(array[middel]))); 
    (*node) = array[middel];
    (*node)-> left = NULL;
    (*node)-> right = NULL;
    balance_node_insert(&((*node)->left),array, first, middel);
    balance_node_insert(&((*node)->right), array, middel+1, last);
  }
  return node; 
}


/*\fn void blanced_tree(node_t*node)
 *\param tree is pointer to tree_t
 * The function build balanced tree from balanced nodes
*/

void blanced_tree(tree_t*tree){
	tree_t*t = tree_new();
	int size = tree_size(tree->root);
	node_t*array[size];
	dump_sort_Node(array, size, tree->root);
	balance_node_insert(&(t ->root) , array, 0, size);
	print(t -> root); 
}




/*\fn printTree(tree_t*tree)
 *\param tree is pointer to tree_t 
 * The function print the node elemet with option. The user print the first every 20 element at a time. 
*/

void printTree(tree_t*tree){
  int i = 0 , j = 1, index =0; 
  int size = tree_size(tree-> root); 
  node_t* nodeArray[size];
  dumpTree(tree -> root, nodeArray, &i);
  for(i = 0, j = 1; i < size; i++, ++j){
    printf("%d. %s\n", j, get_name(returnNodeware(nodeArray[i+ index])));
    if(i == 19 && nodeArray[20 + index] !=NULL){
      index +=20;
      i = 0;
    }
  }
	
}







		



