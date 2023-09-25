#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

//------------------------------------------------------------

#include "parser_stdio.h"

//------------------------------------------------------------

typedef struct graph
{
    int num_of_vertices;

    int num_of_arcs;

    struct vertex* buf_vertices;

    char* alive_vertices;
} graph;

//-------

typedef struct vertex
{
    int num_of_out_arcs;

    int* out_arcs;

    int num_of_in_arcs;

    int* in_arcs;
} vertex;

//------------------------------------------------------------

graph* graph_construct          (parser_stdio* ps);

void   graph_destruct           (graph* grph);

void   graph_dump               (graph* grph);

void   graph_find_dead_vertices (graph* grph);

void   graph_free_dead_vertices (graph* grph);

void   graph_print              (graph* grph);

//------------------------------------------------------------

#endif // GRAPH_H_INCLUDED
