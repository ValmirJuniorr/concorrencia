#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "custom_types.h"
#include "list.h"

#define SIZE_LIST 10
#define AMOUNT_OF_THREADS 20

void *consumer(void *ptr);
void *producer(void *ptr);

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int main(){  
  List *list = create_list(SIZE_LIST);

  pthread_t thread_id[AMOUNT_OF_THREADS * 2];  

  int number, i, j;

  for(i=0; i < AMOUNT_OF_THREADS; i++)
  {    
    pthread_create( &thread_id[i], NULL, producer, (void*) list);
    pthread_create( &thread_id[i + AMOUNT_OF_THREADS], NULL, consumer, (void*) list);
  }

  for(j=0; j < AMOUNT_OF_THREADS * 2; j++)
  {
    pthread_join( thread_id[j], NULL); 
  }
  
  printf("Final list: \n");
  print_list(*list);
  
  return 0;
}


void *producer( void *ptr ){  
  pthread_mutex_lock( &mutex1 );

  List *list = (List*) ptr;

  int number = rand() % 10;
  
  printf("adicionando o item: %d, á lista pelo producer...\n", number);
  
  add(list, number);
  
  print_list(*list);

  printf("O item: %d, foi adicionado á lista pelo producer...\n", number);
  printf("************************\n");

  pthread_mutex_unlock( &mutex1 );
}

void *consumer( void *ptr ){
  pthread_mutex_lock( &mutex1 );
  
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

  pthread_mutex_unlock( &mutex1 );
}
