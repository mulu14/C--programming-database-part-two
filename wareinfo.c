#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "tree.h"
#include "ware.h"
#include "shelfinfo.h"
#include "utilise.h"
ware*insertInfo_at_ware(tree_t *t){
	char *name = ask_question_string("insert item name : ");
	char *description = ask_question_string("insert item description: "); 
	int price =   ask_question_int("insert price : ");
        list_t* shelf_list = list_new();
        shelf *Newshelf = new_shelf();

	while(isShelftaken(t, get_shelf(Newshelf),( cmp_func)Newshelf)){
			printf("The shelf is already taken please insert new shelf\n");
			Newshelf = new_shelf();
			}

	ware *item = createNewWare(name, description, price, shelf_list);
	list_append(item-> shelf_list, get_shelf(Newshelf), Newshelf);
	return item; 

	
}

char *set_name(ware*item){
	char *string = ask_question_string("Please insert item name: ");
	char *tmp = item->name;
	item -> name = string;
	free(tmp); 
}

char *set_des(ware*item){
	char *string = ask_question_string("Please insert description: ");
	char *tmp = item->description;
	item -> description = string;
	free(tmp);
}

int set_price(ware*item){
		return item -> price = ask_question_int("Please insert price: "); 
}
void remove_inserted_info(ware*item, tree_t*tree){
	item = insertInfo_at_ware(tree);
	//remove_inserted_shelf(get_shelf(return_shelf(return_list(item)))); 
	remove_inserted_shelf(return_shelf(return_list(item))); 
        free(item -> description);
	free(item -> name);
	free(item); 
 
  
}


