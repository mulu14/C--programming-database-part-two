#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tree.h"
#include "ware.h"
#include "wareinfo.h"
#include "shelfinfo.h"
#include "list.h"
#include "utilise.h"
#include "compare.h"
int lastupdate;


typedef struct _action {
  int type;
  ware *merch;
  ware* copy;
}action; 
action trace_action;


void print_menu(){
  puts("[A] add  item"); 
  puts("[R] remove item");
  puts("[E]edit  item");
  puts("[U]ndo lates change");
  puts("[L]ist the whole database");
  puts("[D]isplay content of a item");
  puts("[S]ort tree");
  puts("[Q]ite");

}

void edit_insert(ware *item){
  int f;
  printf("%d,[N]ame \n", 1);
  printf("%d,[D]escription \n",2);
  printf("%d,[S]helf_adress \n", 3);
  printf("%d,[P]rice \n", 4);
  printf("%d, [Q]antity\n",5);
  printf("Which row you wann edit?\n");
  scanf("%d", &f);
  switch(f){
  case 1:
    printf("Please insert new name?\n");
    set_name(item); 
    printf("The new name is %s\n", get_name(item));
    break;
  case 2:
    printf("Please insert new description?\n");
    set_des(item); 
    printf("The new description %s:\n" , get_des(item));
    break;
  case 3:
    printf("Please insert new shelf_adress?\n");
    set_shelf(return_shelf(return_list(item)));
    printf("The new shelf is %s:\n", get_shelf((return_shelf(return_list(item)))));
    break;
  case 4:
    printf("-------------------------------------\n");
    printf("Please insert new price:\n");
    set_price(item); 
    printf("The new  price %d\n", get_price(item));
    break;
  case 5:
		
    printf("-------------------------------------\n");
    printf("Please insert new quantity:\n");
    //set_quantity(return_shelf(return_list(item)));
    printf("The old quantity %d\n", get_quantity(return_shelf(return_list(item))));
    break;	
  default:
    printf("May be you insert wrong item");	
  }
}



void alternativ (){
  printf("%d.Add to database\n", 1);
  printf("%d.Edit information\n", 2);
  printf("%d.Cancel action\n", 3);
}

void add_goods(tree_t *tree , void*datakey,  ware *warePointer){
  int see;
  node_t*node_search = find_node(tree, get_name(warePointer), comparevoid); 
  printf("What you wann do?\n");
  alternativ ();
  scanf("%d", &see);
  switch(see){
  case 1:
    if(node_search !=NULL){
      printf("The item exist, Insert shelf : ");
      ware*ware_name = returnNodeware(node_search); 
      shelf*add_only_shelf = new_shelf();
      list_append(return_list(ware_name), get_shelf(add_only_shelf), add_only_shelf);
    }
		
    else {
      insertNode(tree, get_name(warePointer), warePointer,comparevoid); 
    }
		
    break;
  case 2: 
    edit_insert(warePointer);
    insertNode(tree, get_name(warePointer), warePointer, comparevoid); 
    break;
  case 3:
    memset(warePointer, 0, sizeof(ware));
    break;
  default:
    break;
  }
  lastupdate = 1;
  trace_action.merch = warePointer;
  trace_action.type = 1; 
}


void remove_goods(tree_t * tree){
  print(return_node_head(tree)); 
  char ware_name_array[100]; 
  printf("Delete Item: \n");
  scanf("%s", ware_name_array); 
  node_t*node_search = find_node(tree, ware_name_array, comparevoid); 

  if (node_search == NULL)
    return;
	
  else {
    ware*ware_name = returnNodeware(node_search);
    trace_action.merch = createNewWare(get_name(ware_name), get_des(ware_name),get_price(ware_name),return_list(ware_name));
    trace_action.type = 2;
    if(list_length(return_list(ware_name)) == 1){
      remove_Node(tree, ware_name_array, comparevoid);
    }
		
    else {
      print_link_list(return_list(ware_name));
      int index; 
      printf("Delete index shelf: ");
      scanf("%d", &index); 
      list_remove(return_list(ware_name), index, list_get_shelf(return_list(ware_name), index)); 
    }
  }
}  

void edit_alternative(){
  printf("Please insert edit\n"); 
  printf("%d.Name\n", 1); 
  printf("%d.Price\n", 2);
  printf("%d.Description\n", 3);
  printf("%d.Shelf\n", 4);
  printf("%d.Quantity\n",5); 

}

void edit_goods(tree_t* tree){
  print(return_node_head(tree)); 
  int j;
  char editItem[100]; 
  printf("Edit Item: ");
  scanf("%s", editItem); 
  node_t*node_search = find_node(tree, editItem, comparevoid); 
  if(node_search == NULL)
    return;
  else {
    ware*item = returnNodeware(node_search);
    trace_action.copy = createNewWare(strdup(get_name(item)), strdup(get_des(item)),get_price(item),copyList(return_list(item)));
    edit_alternative(); 
    scanf("%d", &j);
    switch(j){
    case 1:
      printf("%s, the old name: \n", get_name(returnNodeware(node_search)));
      char *from = ask_question_string("The item to edit item: "); 
      remove_Node(tree, from, comparevoid);
      free(item -> name);
      char *to   = ask_question_string("New new name : ");
      item -> name = to;
      insertNode(tree, to, item, comparevoid);
      free(from); 
      break;
    case 2:
      printf("%d, the old price: ", get_price(returnNodeware(node_search)));
      set_price(item); 
      break; 
    case 3:
      printf("%s, the old description: ", get_des(returnNodeware(node_search)));
      set_des(item); 
      break;
    case 4:
      print_link_list(return_list(item));
      int index_shelf; 
      printf("Which index shelf you would like to edit\n");
      scanf("%d", &index_shelf);
      shelf *at_index_shelf = list_get_shelf(return_list(item), index_shelf);
      printf("%s, the oldshelf: ", get_shelf(at_index_shelf));
      strcpy(get_shelf(at_index_shelf), ask_question_shelf("Please insert shelf: ")); 
      break;

    case 5:
      print_link_list(return_list(item));
      int index_quantity; 
      printf("Which index shelf you would like to edit\n");
      scanf("%d", &index_quantity);
      shelf *shelf_at_index = list_get_shelf(return_list(item), index_quantity);
      printf("%d, the old quanity", get_quantity(shelf_at_index));
      set_quantity(shelf_at_index,  ask_question_int("New quantity:")); 
   			 
    default:
      break; 
    }
    trace_action.merch = item;
    trace_action.type = 3;
  }
	

		
}


void list_good(tree_t *tree){
  printTree(tree); 	
}




void display_goods(tree_t *tree){
  print(return_node_head(tree)); 
  char ware_name_array[100];  
  printf("Which item would you like to see?:  ");
  scanf("%s", ware_name_array); 
  node_t*node_search = find_node(tree, ware_name_array, comparevoid); 
  if(node_search !=NULL){
    printf("Name: %s:\n", get_name(returnNodeware(node_search)));
    printf("Description: %s\n", get_des(returnNodeware(node_search)));
    printf("Price: %d\n", get_price(returnNodeware(node_search)));
    printf("Shelf: %s\n", get_shelf(return_shelf(return_list((returnNodeware(node_search))))));
    printf("Quantity: %d\n", get_quantity(return_shelf(return_list((returnNodeware(node_search)))))); 
  }
}




void undo_action(tree_t*root){
  puts("0.Undo nothing to database");
  puts("1.Undo add information");
  puts("2.Undo delete action");
  puts("3.Undo edit");
  scanf("%d", &(trace_action.type));
  switch(trace_action.type){
  case 0:
    printf("There is nothing to do\n");
    break;
  case 1:
    remove_Node(root, get_name( trace_action.merch), comparevoid);
    lastupdate = 0; 
    printf("There is no more thing to undo\n");
    break;
  case 2:
    insertNode(root, get_name(trace_action.merch), trace_action.merch, comparevoid); 
    lastupdate = 0;
    printf("There is no more thing to undo\n");
    break;
  case 3:
    destroy_ware_exc(trace_action.merch); 
    remove_Node(root, get_name(trace_action.merch), comparevoid);
    free(trace_action.merch); 
    insertNode(root, get_name(trace_action.copy), trace_action.copy, comparevoid);
   

    lastupdate = 0;
    printf("There is no more thing to undo\n");
    break;
  default:
    printf("There is no action to be done\n");	
  }
}


bool quit_action()
{
  do
    {
      puts("Do you want to quit? [Y/N]");
      char input = getchar(); 

      if (input == 'Y') return true;
      if (input == 'N') return false;

      puts("Only Y or N are valid answers!");
    }while(true); 

  return false;
}




int main (int argc , char **argv){
 

	
  printf("Välkommen till lagerhantering 1.0\n"); 
  printf("=================================\n");
  tree_t *root = tree_new();
  char c;
  bool end_action = false;
  while(!end_action){
    puts("What are you going to do?\n");
    print_menu(); 
    scanf("%c",&c);
    ware*wareName = NULL; 
    if(c =='A'){
      wareName = insertInfo_at_ware(root); 
      add_goods(root, get_name(wareName), wareName);
    }
    if(c =='R'){
      remove_goods(root);
    }
    if(c =='D'){
      display_goods(root);
    }
    if(c =='E'){
      edit_goods(root);
    }
    if(c== 'U'){
      undo_action(root);
    }
    if(c=='L'){
      list_good(root);
    }
    if(c=='S'){
      blanced_tree(root);
    }
    if(c=='Q'){
      end_action = quit_action();
			
    }
  }
  free_tree(return_node_head(root));
  free(root);
  return 0; 
}   
