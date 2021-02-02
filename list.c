#include <stdio.h>
#include <stdlib.h>
#include "custom_types.h"
#include "list.h"

List *create_list(int max_length) {
  List *list = malloc(sizeof(List));
  
  list->length = 0;
  list->max_length = max_length;

  return list;
}

void add(List *list, int number) {
  int new_length = list->length + 1;
  
  if(new_length <= list->max_length) {
    list->length = new_length;

    Item *item = (Item *) malloc(sizeof(Item));
    item->value = number;
    item->prev = NULL;
    item->next = NULL;

    if(new_length == 1) {
      list->items = item;      
      list->first = item;
      list->last  = item;
    } else {
      item->prev = list->last;
      list->last->next = item;
      list->last = item;
    }
  }
  
}

void remove_last(List *list){
  int new_length = list->length - 1;
  
  if(new_length >=0) {
    list->length = new_length;

    Item *old_last = list->last;;

    if(new_length == 0) {
      list->items = NULL;      
      list->first = NULL;
      list->last  = NULL;
    } else {
      list->last = list->last->prev;
      list->last->next = NULL;
    }
    
    free(old_last);
  }
}

void print_list(List list) {
  printf("=======================\n");
  printf("max: %d\n", list.max_length);
  printf("length: %d\n", list.length);
  
  if(list.length > 0) {
    printf("first: %d\n", list.first->value);
    printf("last: %d\n", list.last->value);

    Item *iterator = list.first;

    printf("items: ");
    while(iterator != NULL){
      printf("%d, ", iterator->value);

      iterator = iterator->next;
    }
    printf("\n");
  } else {
    printf("empty list :(\n");
  }
}