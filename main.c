#include <pthread.h>
#include <semaphore.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "custom_types.h"
#include "list.h"

#define TRUE 1
#define FALSE 0

#define SIZE_LIST 10
#define AMOUNT_OF_THREADS 20

void *consumer(void *ptr);
void *producer(void *ptr);

sem_t empty_list;
sem_t full_list;
sem_t lock_sem;

int main(){

  long int inicio, fim;

  inicio = clock();

  sem_init(&empty_list, 0, SIZE_LIST);
  sem_init(&full_list, 0, 0);
  sem_init(&lock_sem, 0, 1);

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

  sem_destroy(&empty_list);
  sem_destroy(&full_list);
  sem_destroy(&lock_sem);
  
  printf("Final list: \n");
  print_list(*list);

  fim = clock();

  printf("Tempo de execução em %.2lf segundos\n", (double)(fim-inicio)/1000000);
  return 0;
}


void *producer( void *ptr ){
  sem_wait(&empty_list);
  sem_wait(&lock_sem);

  List *list = (List*) ptr;

  int number = rand() % 10;
  
  printf("adicionando o item: %d, á lista pelo producer...\n", number);
  
  add(list, number);
  
  print_list(*list);

  printf("O item: %d, foi adicionado á lista pelo producer...\n", number);
  printf("************************\n");

  sem_post(&lock_sem);
  sem_post(&full_list);
  sleep(random() % 3);
}

void *consumer( void *ptr ){
  sem_wait(&full_list);
  sem_wait(&lock_sem);

  List *list = (List*) ptr;

  int value_to_be_removed = list->last->value;

  printf("removendo o item: %d, da lista pelo consumer...\n", value_to_be_removed);
  
  remove_last(list);
  
  print_list(*list);    

  printf("O item: %d, foi removido da lista pelo Consumer...\n", value_to_be_removed);
  printf("************************\n");

  sem_post(&lock_sem);
  sem_post(&empty_list);
  sleep(random() % 3);
}
