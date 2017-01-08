#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "shelf.h"
#include "utilise.h"

shelf *new_shelf(){
	char *shelfname = ask_question_shelf("insert shelf : ");
	int quantity = ask_question_int("insert item quantity: ");
	shelf *add = makeShelf(shelfname, quantity); 
    return add;
}

/*
int set_quantity(shelf*address){
     int quantity  = get_quantity(address);  
	 quantity = ask_question_int("insert quantity: ");
	 return quantity; 
	 }*/
 

char *set_shelf(shelf *address){	 
	return strcpy(get_shelf(address), ask_question_shelf("insert shelf : "));
	}

void remove_inserted_shelf(shelf*address){
	address = new_shelf(); 
	free(get_shelf(address));
	free(address); 
}
