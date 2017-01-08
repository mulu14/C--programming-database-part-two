#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<stdint.h>

int compare(void *p1, void*p2){
	int val;
	if((val = strcmp((char*)p1, (char*)p2)) < 0){
		return -1; 
	}
	else if ((val = strcmp((char*)p1, (char*)p2)) > 0){
		return 1; 
	}
	else{
		return 0; 
	}
	return val; 
	}
 
int comparevoid(void *p1, void*p2){
	
  return strcmp((char*)p1, (char*)p2);
      
 
}

