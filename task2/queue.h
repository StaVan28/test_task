#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

//------------------------------------------------------------

/*! @brief   Struct for queue
    @version 1.0
    @authors StaVan28
    @date    26.07.2023

    Classic realization of cyclic queue
*/
typedef struct queue
{
    int  capacity;

    int  cur_size;

    int  head;

    int  tail;

    int* buf_vertices;
} queue;

//------------------------------------------------------------

/*! Constructor a queue
    @param [in] int capacity capacity to init struct
    @return pointer on alloc struct queue
    @version 1.0
    @authors StaVan28

    Fill all fields struct.
*/
queue* queue_construct (int capacity);

//--------

/*! Destructor a queue
    @param [in] queue* queu pointer on alloc struct queue
    @return None
    @version 1.0
    @authors StaVan28

    Free memory buf_vertices and the structure itself queu.
*/
void   queue_destruct  (queue* queu);

//--------

/*! Add a vertex
    @param [in] queue* queu pointer on alloc struct queue
    @param [in] int vertex  value of vertex
    @return None
    @version 1.0
    @authors StaVan28

    Add a new vertex in queue, update all fields, if 
    cur_size == capacity resize() a queue.
*/
void   queue_push      (queue* queu, int vertex);

//--------

/*! Remove a vertex
    @param [in] queue* queu pointer on alloc struct queue
    @return int vertex  value of vertex
    @version 1.0
    @authors StaVan28

    Remove a vertex from queue and update all fields.
*/
int    queue_pop       (queue* queu);

//--------

/*! Print a queue
    @param [in] queue* queu pointer on alloc struct queue
    @return None
    @version 1.0
    @authors StaVan28

    Prints a printout with all parameters output in a beautiful form to a file,
    defined in QUEUE_DUMP_PATH.
*/
void   queue_dump      (queue* queu);

//--------

/*! Check is queue empty?
    @param [in] queue* queu pointer on alloc struct queue
    @return None
    @version 1.0
    @authors StaVan28

    Check and return 1 if empty, 0 else.
*/
char   queue_is_empty  (queue* queu);

//--------

/*! Return a size
    @param [in] queue* queu pointer on alloc struct queue
    @return int cur_size
    @version 1.0
    @authors StaVan28

    Return current size.
*/
int    queue_size      (queue* queu);

//------------------------------------------------------------

#endif // QUEUE_H_INCLUDED
