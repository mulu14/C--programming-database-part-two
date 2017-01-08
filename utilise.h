#ifndef _ASK2_H_
#define _ASK2_H_
#include<stdbool.h>

typedef union answer answer_t;
typedef bool(*check_func)(char*);
typedef answer_t(*convert_func)(char*);
typedef  int (*cmp)(void *p1, void*p2);
bool is_number(char*str);
bool string_validation(char *string);
bool right_form(char *str);
char* ask_question_shelf(char*str);
char*ask_question_string(char*question); 
bool read_string_bool();
int ask_question_int(char*question);
#endif
