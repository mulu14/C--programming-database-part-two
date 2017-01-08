#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include<stdbool.h>

/*!\struct link
 *  shelf is member of link struct and it is void pointer
 *  next is member of  struct link
 * struct for  link  holds void pointer as element and next. the next point next lemenet on the link
 * Link struct provide a bulding block for larger database creation  
 */
struct link {
	void *shelfName;
	struct link *next; 
};

/*!\struct list
 *  first is member of list struct and it point the fisrt element or the head of the link
 *  last is  member of list struct and it point the last element of the link
 * list struct provide a bulding block for larger database creation  
 */
struct list{
	struct link  *first;
	struct link *last; 
};

link_t *link_new(){
	link_t*l = malloc(sizeof(struct link));
	return l; 
}

/*\fn list_t* list_new(
 *The  function create empty list
 */
list_t *list_new(){
	list_t *n = calloc(1,sizeof(struct list));
	return n; 
};

/*\fn bool list_prepend(list_t*list, void*address)
 *\param  list is pointer  to list_t
 *\param  address is pointer to  void data type
 *The  function insert new elemet at the beginning of the list. It return true if the element inserted at the beginning of the link list
  or return fasle otherwise 
 */
bool list_prepend (list_t *list, void*address){
	struct link *listHead = link_new();
	
	if(list -> first == NULL){
	listHead -> shelfName = address;
	list -> first = listHead;
	list -> last = listHead;
	listHead -> next = NULL;
	return true; 
	}
	else
	{
		listHead -> shelfName = address; 
		listHead -> next = list -> first; 
		list->first = listHead;
		return true; 
	}
	return false; 
};

/*\fn void*return_shelf(list_t*list)
 *\param  list is pointer  to list_t
 *The  function return the first elemet from linked list
 */

void*return_shelf(list_t *list){
	return list -> first -> shelfName; 
}

/*\fn bool list_append(list_t*list, void*address)
 *\param  list is pointer  to list_t
 *\param  address is pointer to  void data type
 * The  function insert new elemet at the beginning of the list if the list is empty, otherwise it it insert each new element at
   the end of the link list. It return true if the element inserted the link list or return fasle otherwise 
 */
bool list_append (list_t *list, void *address){
	struct link *listTail = link_new();
	if(list -> first == NULL){
		list_prepend(list, address);
		return true ; 
	}
	else {
	list-> last -> next = listTail;
	list -> last = listTail;
	listTail -> shelfName = address; 
	listTail -> next = NULL;
	return true; 
	}
	
	return false; 
};

/*\fn bool list_length(list_t*list)
 *\param  list is pointer  to list_t
 *The  function calcualte the number of element on the linked list, if the linked list is emptyt it will return zero
  otherwise it will return the calcualted number of element on the linked list. 
 */
int list_length(list_t* list)
{
	if(list-> first == NULL)
	return 0;

	
	struct link *current = list-> first;
	int size = 0;

  while (current!= NULL)
  {
    current = current->next;
	++size;
  }

  return size;
}


 /*\fn bool list_insert(list_t*list, int index, void*address)
 *\param  list is pointer  to list_t
 *\param index is int 
 *\param  address is pointer to  void data type
 *The  function insert new elemet at given index. It return true if the element inserted at given index or return fasle otherwise 
 */

bool list_insert(list_t*list, int index, void*address){

	int max = list_length(list);
	struct link*temp = list -> first;
	
	if(index == 0){
		list_prepend(list, address);
		return true;
		}
	
	if(index < max){
	struct link *current = list-> first;
	int i;
	for( i = 0; i <= index-1; ++i){
			current = current -> next;
		}
	temp->next = current -> next;
	current -> next = temp;
	temp-> shelfName = address; 
	return true;
	}
	if(index > max){
		return false;
	}
	if(index == max){
		list_append(list, address);
		return true; 
	}
	if(index < 0){
		int i = 0;
		struct link * current = list -> first; 
		for(i = 0; i < max + 1 - index; ++i){
			current = current -> next; 
		}
		temp -> next = current -> next;
		current -> next = temp;
		temp -> shelfName = address;
		return true; 
	}

	return true;

}


/*\fn bool list_remove(list_t*list, int index, void*address)
 *\param  head is pointer  to list_t
 *\param index is int 
 *\param  address is pointer to  void data type
 *The  function remove element from given index. It return true if the element removed from given index or return fasle otherwise 
 */
		
bool list_remove(list_t *list, int index, void*address){

	int length = list_length(list);
	struct link *current = list -> first; 
	if(index > length){
		return false;
	}
	if(index == 0){
	   current = list-> first;
	   list -> first = list-> first-> next;
		free(current);
		return true; 
	}

	int i;
	for(i = 0; i <= index -1; i++){
		current = current -> next;
	}
		struct link *temp = current -> next;
		current -> next = temp -> next;
		free(temp);
	  return true;
	}



/*\fn  void* list_get_shelf(list_t*list, int index)
 *\param  head is pointer  to list_t
 *\param index is int 
 *The  function return element from given index. It return element if the element existed on the link list otherwise it will return NULL;  
 */
void *list_get_shelf(list_t *list, int index){
	struct link  *current = list -> first; 
	int length = list_length(list);
	int i = 0;
	if(current == NULL)
		return NULL;
	if(index > length){
		printf("ERROR: no item \n");
		return NULL; 
	}

	
	if(index < length){
		for(i = 0; i < index; ++i) {
		current = current -> next; 
	}
		return current ->shelfName;
	}
	
	return NULL;
}


/*\fn void*list_first(list_t*list, int index)
 *\param  list is pointer  to list_t
 *The  function return the value of the head of the link list. It return value if the element existed on the link list
 * otherwise it will return NULL;  
 */

void *list_first(list_t *list){
	if(list -> first != NULL)
		return get_shelf(list -> first->shelfName);
	return NULL; 
} 

/*\fn void*list_last(list_t*head, int index)
 *\param  head is pointer  to list_t
 *The  function return the value of the last element on the link list. It return value if the element existed on the link list
 * otherwise it will return NULL;  
 */
void * list_last(list_t *list){
	if(list -> last !=NULL)
		return get_shelf(list -> last->shelfName);
	return NULL; 
}

/*\fn bool isexist(list_t*head, void*address)
 *\param  list is pointer  to list_t
 *\param address is void pointer
 *The  function return true if the address /element existed on the link list otherwise return false; 
 */
bool isexist(list_t * list, void*address){
	struct link *current = list -> first;

	if(current == NULL)
		return false;

	while(current != NULL){
		if(compare(get_shelf(current ->shelfName), get_shelf(address)) == 0)
			return true;
		current = current -> next; 
}
	return false; 
}

/*\fn print_link_list(list_t*list)
 *\param  list is pointer  to list_t
 *The  function print all the element existed on the link list
 */

void print_link_list(list_t*list){
	int i = 0; 
	if(list -> first == NULL){
		printf("There is no item to print");
		return; 
	} else{
		struct link *current = list -> first;
		while(current != NULL){
			printf("%d. %s:  %d \n", i, get_shelf(current-> shelfName), get_quantity(current -> shelfName));
			++i; 
			current = current -> next; 
		}
	}
}

/*\fn void freeList(list_t*list)
 *\param  list is pointer  to list_t
 *The  function delete all the element from link list; 
 */

void freeList(list_t*list){
	struct link *current = list-> first; 
	while(current !=NULL){
		free(current -> shelfName);
		current = current -> next;
	}
	free(list); 
}  
