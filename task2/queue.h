#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

//------------------------------------------------------------

typedef struct queue
{
    int  capacity;

    int  cur_size;

    int  head;

    int  tail;

    int* buf_vertices;
} queue;

//------------------------------------------------------------

queue* queue_construct (int capacity);

void   queue_destruct  (queue* queu);

void   queue_push      (queue* queu, int vertex);

int    queue_pop       (queue* queu);

void   queue_dump      (queue* queu);

char   queue_is_empty  (queue* queu);

int    queue_size      (queue* queu);

//------------------------------------------------------------

#endif // QUEUE_H_INCLUDED
