/* Producer and Consumer problem using Semaphore */
/* You should complete the implementation provided here */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

/************************************************************
 *          YOU DO NOT HAVE TO MODIFY THIS PART             *
 ************************************************************/
/* we first define a FIFO circular queue data-structure */
#define MAX_FIFO_SIZE 8         /* the size of the queue */
typedef struct QUEUE {
  int data[MAX_FIFO_SIZE] ;
  int head, tail ;
  int full ;
} queue ;

/* This function inits the queue, should be called first */
void
init_queue(queue* q) {
  q->head = q->tail = 0 ;
  q->full = 0 ;
}

/* return "1" if queue is empty, "0" otherwise */
int
queue_empty(queue* q) {
  if(q->head == q->tail)
    return !(q->full) ;
  else
    return 0 ;
}

/* this function returns the queue size */
int
queue_size(queue* q) {
  if(!q->full) {
    if(q->tail >= q->head)
      return q->tail - q->head ;
    else
      return MAX_FIFO_SIZE - q->head + q->tail ;
  } else
    return MAX_FIFO_SIZE ;
}

/* this function appends an integer into the tail of the queue */
/* if the queue is full, then the integer is not added */
/* it returns "1" to indicate that an element is added, "0" if not */
int
enqueue(queue* q, int e) {
  if(!q->full) {
    q->data[q->tail] = e ;
    q->tail = (q->tail+1) % MAX_FIFO_SIZE ;
    if(q->head == q->tail)
      q->full = 1 ;
    /* this usleep is put here just to let */
    /* other threads get a chance to run */
    /* this forced context switch will make any thread */
    /* safety issues apparent sooner rather than later */
    usleep(10) ;
    return 1 ;
  } else
    return 0 ;
}

/* this function removes an integer from the head of the queue */
/* if the queue is empty, then nothing is done */
/* returns "1" to indicate an integer is removed, "0" if not */
/* removed integer is stored in the second argument "e" */
int
dequeue(queue* q, int* e) {
  if(queue_empty(q))
    return 0 ;
  *e = q->data[q->head] ;
  q->head = (q->head+1) % MAX_FIFO_SIZE ;
  if(q->full) q->full = 0 ;
  /* this usleep is just to let others to get a chance to run */
  usleep(10) ;
  return 1 ;
}

/*******************************************************************
 *               THIS IS THE PART YOU NEED TO WORK ON              *
 *******************************************************************/

/* Now that we can begin to define the producer and consumer functions */

/* first define a produce function that generates an integer */
/* based on the producer's id and an offset number */
int
produce(int id, int offset) {
  int item = id * 1000000 + offset ;
  printf("Producer #%d produces item: %d\n", id, item) ;
  return item ;
}

/* a consume function of an integer just prints out the value */
/* and the associated consumer id */
void
consume(int id, int item) {
  printf("Consumer #%d consumes item: %d\n", id, item) ;
}

/* we will need to define a common shared queue
   that everyone can access */
queue fifo_buffer ;

/* this defines a total number of items each producer is going to produce */
#define MAX_ITEM_TO_PRODUCE 10

/* the producer function  */
void*
producer(void* arg) {
  /* fill in the details here */
  /* you need to ensure that the function satisfies the
     requirements of the producer/consumer problem */
  int i;
  for(i=0;i<MAX_ITEM_TO_PRODUCE;++i) {
    /* each producer produces "MAX_ITEM_TO_PRODUCE" and then quit */
  }
  return 0 ;
}

/* the consumer function */
void*
consumer(void* arg) {
  /* fill in the details here */
  /* you need to ensure that the function satisfies the
     requirements of the producer/consumer problem */

  /* consumers never quit */
  while(1) {
    /* fill in the details here */
  }
  return 0 ;
}


/* Here we can finally define the main function to put everything together */
int
main(int argc, char* argv[]) {
  int num_producer, num_consumer ;
  int i ;

  if(argc != 3) {
    printf("Usage: %s <# producer> <# consumer>\n", argv[0]) ;
    return 1 ;
  }

  num_producer = atoi(argv[1]) ;
  num_consumer = atoi(argv[2]) ;

  /* we need to initialize the global queue buffer */
  init_queue(&fifo_buffer) ;

  /* you need to replace the following function calls
     with actual thread launching, you will also need to
     create, initialize, and destroy the sempahores properly,
     joining the threads properly. */

  /* we create num_consumer consumers first */
  printf("Creating %d consumers\n", num_consumer) ;
  for(i=0;i<num_consumer;++i) {
    consumer( (void*)i);
  }
  printf("Creating %d producers\n", num_producer) ;
  /* we create num_producer producers then */
  for(i=0;i<num_producer;++i) {
    producer( (void*)i);
  }

  /* since consumers never quit, we'll notify the user to */
  /* end the program by press "Ctrl-C" */
  printf("********************************************************\n") ;
  printf("* All Producers finished, please terminate the program *\n") ;
  printf("* by \"Ctrl-C\" when all consumers print their items     *\n") ;
  printf("********************************************************\n") ;

  return 0 ;
}

/* ... the end ... */

