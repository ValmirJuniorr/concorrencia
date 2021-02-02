#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "custom_types.h"
#include "list.h"

#define SIZE_LIST 10

void *consumer(void *ptr);
void *producer(void *ptr);

int main(){  
  List *list = create_list(SIZE_LIST);

  pthread_t thread1, thread2;

  pthread_create(&thread1, NULL, producer, (void*) list);
  pthread_create(&thread2, NULL, consumer, (void*) list);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL); 
  
  printf("Final list: \n");
  print_list(*list);
  
  return 0;
}


void *producer( void *ptr ){  
  List *list = (List*) ptr;

  int number = rand() % 10;
  
  printf("adicionando o item: %d, á lista pelo producer...\n", number);
  
  add(list, number);
  
  print_list(*list);

  printf("O item: %d, foi adicionado á lista pelo producer...\n", number);
  printf("************************\n");
}

void *consumer( void *ptr ){
  List *list = (List*) ptr;

  if( list->length > 0 ) {
    int value_to_be_removed = list->last->value;

    printf("removendo o item: %d, da lista pelo consumer...\n", value_to_be_removed);
    
    remove_last(list);
    
    print_list(*list);    

    printf("O item: %d, foi removido da lista pelo Consumer...\n", value_to_be_removed);
    printf("************************\n");
  } else {
    printf("Empty list :(\n");
  }
}
