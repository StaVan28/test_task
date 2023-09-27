#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

//------------------------------------------------------------

#include "parser_stdio.h"

//------------------------------------------------------------

/*! @brief   Struct for graph
    @version 1.0
    @authors StaVan28
    @date    26.07.2023
*/
typedef struct graph
{
    int num_of_vertices;         //< number of vertices

    int num_of_arcs;             //< number of arcs

    struct vertex* buf_vertices; //< array of vertices

    char* alive_vertices;        //< array of alive vertices 
} graph;

//-------

/*! @brief   Struct for vertex of graph
    @version 1.0
    @authors StaVan28
    @date    26.07.2023
*/
typedef struct vertex
{
    int num_of_out_arcs; //< number of outgoing arcs of a current vertex

    int* out_arcs;       //< array of outgoing arcs

    int num_of_in_arcs;  //< number of incoming arcs of a current vertex

    int* in_arcs;        //< array of incoming arcs
} vertex;

//------------------------------------------------------------

/*! Constructor a graph
    @param [in] parser_stdio* ps pointer on parser_stdio
    @return pointer on alloc struct graph
    @version 1.0
    @authors StaVan28

    Copy fields of parser_stdio and fill a graph struct.
*/
graph* graph_construct          (parser_stdio* ps);
              
//--------

/*! Destruct a graph
    @param [in] graph* grph pointer on alloc struct graph
    @return None
    @version 1.0
    @authors StaVan28

    Free memory buf_vertices, out and in arcs bufs and the structure itself graph.
*/
void   graph_destruct           (graph* grph);
              
//--------

/*! Dump a graph
    @param[in] graph* grph pointer on alloc struct graph
    @return None
    @version 1.0
    @authors StaVan28

    Print a template for graphviz. Path defined in GRAPH_DUMP_PATH.
*/
void   graph_dump               (graph* grph);
              
//--------

/*! Find dead vertices in graph
    @param[in] graph* grph pointer on alloc struct graph
    @return None
    @version 1.0
    @authors StaVan28

    Find dead vertices by using 2 bfs in forward and reverse order, 
    starting from the start and stop verticies respectively. Update alive_vertices.
*/
void   graph_find_dead_vertices (graph* grph);
              
//--------

/*! Free dead vertices in graph
    @param[in] graph* grph pointer on alloc struct graph
    @return None
    @version 1.0
    @authors StaVan28

    Free dead verticies in graph. Mark pointers to dead vertices in live vertices.
*/
void   graph_free_dead_vertices (graph* grph);
              
//--------

/*! Print graph in stdio
    @param[in] graph* grph pointer on alloc struct graph
    @return None
    @version 1.0
    @authors StaVan28

    Print graph in format required in the condition of task. Print only alive parts of graph!
*/
void   graph_print              (graph* grph);

//------------------------------------------------------------

#endif // GRAPH_H_INCLUDED
