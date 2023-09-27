#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "queue_settings.h"
#include "queue.h"

//------------------------------------------------------------

static const int POISON_VERTEX = 0x00DEAD00; //< poison value for vertex

//------------------------------------------------------------

/*! Resize a queue
    @param [in] int capacity capacity to init struct
    @return pointer on alloc struct queue
    @version 1.0
    @authors StaVan28

    Increase capacity and copy elements in correct order. 
*/
static void queue_resize (queue* queu);

//------------------------------------------------------------

queue* queue_construct (int capacity)
{
    if (capacity <= 0)
    {
        perror ("capacity queue_construct\n");
        exit   (EXIT_FAILURE);
    }

    queue* queu = (queue*) calloc (1, sizeof(queue));
    if (queu == NULL)
    {
        perror ("calloc queue\n");
        exit   (EXIT_FAILURE);
    }

    queu->capacity = capacity;

    queu->buf_vertices = (int*) calloc (queu->capacity, sizeof(int));
    if (queu->buf_vertices == NULL)
    {
        perror ("calloc queu->buf_vertices\n");
        exit   (EXIT_FAILURE);
    }

    for (int i_vertex = 0; i_vertex < queu->capacity; i_vertex++)
        queu->buf_vertices[i_vertex] = POISON_VERTEX;

    return queu;
}

//------------------------------------------------------------

void queue_destruct (queue* queu)
{
    if (queu == NULL)
    {
        perror ("queu == NULL");
        exit   (EXIT_FAILURE);
    }

    free (queu->buf_vertices);
    free (queu);
}

//------------------------------------------------------------

static void queue_resize (queue* queu)
{
    assert (queu);

    int* new_buf_vertices = (int*) calloc (2 * queu->capacity, sizeof(int));
    if (new_buf_vertices == NULL)
    {
        perror ("calloc queu->buf_vertices\n");
        exit   (EXIT_FAILURE);
    }

    for (int i_vertex = 0; i_vertex < queu->cur_size; i_vertex++)
        new_buf_vertices[i_vertex] = queu->buf_vertices[(queu->head + i_vertex) % queu->capacity];

    for (int i_vertex = queu->cur_size; i_vertex < 2 * queu->capacity; i_vertex++)
        new_buf_vertices[i_vertex] = POISON_VERTEX;

    free (queu->buf_vertices);
    queu->buf_vertices = new_buf_vertices;

    queu->capacity *= 2;

    queu->head = 0;
    queu->tail = queu->cur_size;
}

//------------------------------------------------------------

void queue_push (queue* queu, int vertex)
{
    if (queu == NULL)
    {
        fprintf (stderr, "ERROR! queu == NULL\n");
        exit    (EXIT_FAILURE);
    }

    if (queu->cur_size == queu->capacity)
        queue_resize(queu);

    queu->buf_vertices[queu->tail] = vertex;

    queu->tail = (queu->tail + 1) % queu->capacity;
    queu->cur_size++;
}

//------------------------------------------------------------

int queue_pop (queue* queu)
{
    if (queu == NULL)
    {
        fprintf (stderr, "ERROR! queu == NULL\n");
        exit    (EXIT_FAILURE);
    }

    if (queue_is_empty (queu))
    {
        fprintf (stderr, "ERROR! pop in empty queue\n");
        exit    (EXIT_FAILURE);
    }

    int vertex = queu->buf_vertices[queu->head];
    queu->buf_vertices[queu->head] = POISON_VERTEX;

    queu->head = (queu->head + 1) % queu->capacity;
    queu->cur_size--;

    return vertex;
}

//------------------------------------------------------------

void queue_dump (queue* queu)
{
    if (queu == NULL)
    {
        fprintf (stderr, "ERROR! queu == NULL\n");
        exit    (EXIT_FAILURE);
    }

    FILE* dump = fopen (QUEUE_DUMP_PATH, "wb");
    if (dump == NULL)
    {
        perror ("fopen queue_dump\n");
        exit   (EXIT_FAILURE);
    }

    fprintf (dump,     "|-------------------------------------|\n"
                       "|           DUMP QUEUE                |\n"
                       "|-------------------------------------|\n"
                       "{\n"
                       "    capacity     = [%d];\n"
                       "    cur_size     = [%d];\n"
                       "    head         = [%d];\n"
                       "    tail         = [%d];\n"
                       "    buf_vertices = [%p];\n"
                       "\n"
                       "    Buffer Vertices:\n",
                            queu->capacity,
                            queu->cur_size,
                            queu->head,
                            queu->tail,
                            queu->buf_vertices
    );

    for (int i_vertex = 0; i_vertex < queu->capacity; i_vertex++)
    {
        fprintf (dump, "    (%3d)", i_vertex + 1);

        if (queu->buf_vertices[i_vertex] == POISON_VERTEX)
            fprintf (dump, " [xxx]");
        else
            fprintf (dump, " [%3d]", queu->buf_vertices[i_vertex]);

        if (i_vertex == queu->head)
            fprintf (dump, " <--- {head}");

        if (i_vertex == queu->tail)
            fprintf (dump, " <--- {tail}");

        fprintf (dump, "\n");
    }

    fprintf (dump,     "}\n"
                       "|-------------------------------------|\n"
                       "|           END DUMP QUEUE            |\n"
                       "|-------------------------------------|\n"
                       );


    fclose (dump);
}

//------------------------------------------------------------

char queue_is_empty (queue* queu)
{
    if (queu == NULL)
    {
        fprintf (stderr, "ERROR! queu == NULL\n");
        exit    (EXIT_FAILURE);
    }

    return queu->cur_size == 0;
}

//------------------------------------------------------------

int queue_size (queue* queu)
{
    if (queu == NULL)
    {
        fprintf (stderr, "ERROR! queu == NULL\n");
        exit    (EXIT_FAILURE);
    }

    return queu->cur_size;
}

//------------------------------------------------------------
