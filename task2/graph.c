#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>

#include "graph_settings.h"
#include "graph.h"
#include "queue.h"

//------------------------------------------------------------

static const int  START_VERTEX = 0;

static const int POISON_VERTEX = 0x00DEAD00;

//------------------------------------------------------------

enum CONDITIONS_VERTEX
{
    DEAD  = 0,
    ALIVE = 1,
};

//-----

enum DIRECTION_ARCS
{
    AGAINST = 0,
    IN      = 1,
};

//------------------------------------------------------------

static char*  graph_bfs              (graph* grph, int start_vertex, int order);

static void   graph_free_visited_buf (char* visited_buf);


static void fprintf_declaration_nodes (FILE* grph_file, graph* grph);

static void fprintf_special_node      (FILE* grph_file, graph* grph, const char* name_node, int* i_vertex);

static void fprintf_arcs              (FILE* grph_file, graph* grph);


static void selection_sort (int* array, int size);

static void swap           (int* a, int* b);

//------------------------------------------------------------

graph* graph_construct (parser_stdio* ps)
{
    if (ps == NULL)
    {
        perror ("ps == NULL\n");
        exit   (EXIT_FAILURE);
    }

    graph* grph = (graph*) calloc (1, sizeof(graph));
    if    (grph == NULL)
    {
        perror ("calloc grph\n");
        exit   (EXIT_FAILURE);
    }

    grph->num_of_vertices = ps->num_of_vertices;
    grph->num_of_arcs     = ps->num_of_arcs;

    grph->alive_vertices = (char*) calloc (grph->num_of_vertices, sizeof(char));
    if (grph->alive_vertices == NULL)
    {
        perror ("calloc grph->alive_vertices\n");
        exit   (EXIT_FAILURE);
    }

    for (int i = 0; i < grph->num_of_vertices; i++)
        grph->alive_vertices[i] = ALIVE;

    grph->buf_vertices = (vertex*) calloc (grph->num_of_vertices, sizeof(vertex));
    if (grph->buf_vertices == NULL)
    {
        perror("calloc grph->vertices\n");
        exit  (EXIT_FAILURE);
    }

    for (int i = 0; i < grph->num_of_arcs; i++)
    {
        grph->buf_vertices[ps->buf_vertices[i][0]].num_of_out_arcs++;
        grph->buf_vertices[ps->buf_vertices[i][1]].num_of_in_arcs++;
    }

    for (int i = 0; i < grph->num_of_vertices; i++)
    {
        grph->buf_vertices[i].out_arcs = (int*) calloc (grph->buf_vertices[i].num_of_out_arcs, sizeof(int));
        if (grph->buf_vertices[i].out_arcs == NULL)
        {
            perror ("calloc grph->buf_vertices[i].out_arcs\n");
            exit   (EXIT_FAILURE);
        }

        grph->buf_vertices[i].in_arcs = (int*) calloc (grph->buf_vertices[i].num_of_in_arcs, sizeof(int));
        if (grph->buf_vertices[i].in_arcs == NULL)
        {
            perror ("calloc grph->buf_vertices[i].in_arcs\n");
            exit   (EXIT_FAILURE);
        }
    }

    for (int i = 0; i < grph->num_of_vertices; i++)
    {
        grph->buf_vertices[i].num_of_out_arcs = 0;
        grph->buf_vertices[i].num_of_in_arcs  = 0;
    }

    for (int i = 0; i < grph->num_of_arcs; i++)
    {
        int i_out = ps->buf_vertices[i][0];
        int i_in  = ps->buf_vertices[i][1];

        grph->buf_vertices[i_out].out_arcs[grph->buf_vertices[i_out].num_of_out_arcs] = i_in;
        grph->buf_vertices[i_out].num_of_out_arcs++;

        grph->buf_vertices[i_in].in_arcs[grph->buf_vertices[i_in].num_of_in_arcs] = i_out;
        grph->buf_vertices[i_in].num_of_in_arcs++;

    }

    return grph;
}

//------------------------------------------------------------

void graph_destruct (graph* grph)
{
    if (grph == NULL)
    {
        perror ("grph NULL\n");
        exit   (EXIT_FAILURE);
    }

    for (int i = 0; i < grph->num_of_vertices; i++)
    {
        if (grph->alive_vertices[i])
        {
            free (grph->buf_vertices[i].out_arcs);
            free (grph->buf_vertices[i].in_arcs);
        }
    }

    free (grph->alive_vertices);
    free (grph->buf_vertices);
    free (grph);
}

//------------------------------------------------------------

void graph_find_dead_vertices (graph* grph)
{
    if (grph == NULL)
    {
        perror ("grph NULL\n");
        exit   (EXIT_FAILURE);
    }

    char*  first_traversal = graph_bfs (grph, START_VERTEX, IN);

    char* second_traversal = graph_bfs (grph, grph->num_of_vertices - 1, AGAINST);

    for (int i = 0; i < grph->num_of_vertices; i++)
        grph->alive_vertices[i] = first_traversal[i] && second_traversal[i];

    graph_free_visited_buf (second_traversal);

    graph_free_visited_buf (first_traversal);
}

//------------------------------------------------------------

static char* graph_bfs (graph* grph, int start_vertex, int order)
{
    if (grph == NULL)
    {
        perror ("grph NULL\n");
        exit   (EXIT_FAILURE);
    }

    char* visited_buf = (char*) calloc (grph->num_of_vertices, sizeof(char));
    if   (visited_buf == NULL)
    {
        perror ("calloc bfs_buf\n");
        exit   (EXIT_FAILURE);
    }

    visited_buf[0]                         = ALIVE;
    visited_buf[grph->num_of_vertices - 1] = ALIVE;

    queue* queu = queue_construct (grph->num_of_vertices);
    queue_push (queu, start_vertex);

    if (order == IN)
    {
        while (!queue_is_empty (queu))
        {
            int pop_vertex = queue_pop (queu);

            for (int i = 0; i < grph->buf_vertices[pop_vertex].num_of_out_arcs; i++)
            {
                if (visited_buf[grph->buf_vertices[pop_vertex].out_arcs[i]] == DEAD)
                {
                    visited_buf[grph->buf_vertices[pop_vertex].out_arcs[i]] = ALIVE;
                    queue_push (queu, grph->buf_vertices[pop_vertex].out_arcs[i]);
                }
            }
        }
    }
    else if (order == AGAINST)
    {
        while (!queue_is_empty (queu))
        {
            int pop_vertex = queue_pop (queu);

            for (int i = 0; i < grph->buf_vertices[pop_vertex].num_of_in_arcs; i++)
            {
                if (visited_buf[grph->buf_vertices[pop_vertex].in_arcs[i]] == DEAD)
                {
                    visited_buf[grph->buf_vertices[pop_vertex].in_arcs[i]] = ALIVE;
                    queue_push (queu, grph->buf_vertices[pop_vertex].in_arcs[i]);
                }
            }
        }
    }

    queue_dump (queu);

    queue_destruct (queu);

    return visited_buf;
}

//------------------------------------------------------------

static void graph_free_visited_buf (char* visited_buf)
{
    free (visited_buf);
}

//------------------------------------------------------------

void graph_free_dead_vertices (graph* grph)
{
    if (grph == NULL)
    {
        perror ("grph NULL\n");
        exit   (EXIT_FAILURE);
    }

    for (int i = 0; i < grph->num_of_vertices; i++)
    {
        if (!grph->alive_vertices[i])
        {
            free (grph->buf_vertices[i].out_arcs);
            free (grph->buf_vertices[i].in_arcs);
            continue;
        }

        for (int i_out = 0; i_out < grph->buf_vertices[i].num_of_out_arcs; i_out++)
            if (grph->alive_vertices[grph->buf_vertices[i].out_arcs[i_out]] == DEAD)
                grph->buf_vertices[i].out_arcs[i_out] = POISON_VERTEX;


        for (int i_in = 0; i_in < grph->buf_vertices[i].num_of_in_arcs; i_in++)
            if (grph->alive_vertices[grph->buf_vertices[i].in_arcs[i_in]] == DEAD)
                grph->buf_vertices[i].in_arcs[i_in] = POISON_VERTEX;           
    }
}

//------------------------------------------------------------

void graph_dump (graph* grph)
{
    if (grph == NULL)
    {
        perror ("grph NULL\n");
        exit   (EXIT_FAILURE);
    }

    FILE* grph_file = fopen (GRAPH_DUMP_PATH, "wb");
    if   (grph_file == NULL)
    {
        perror ("fopen graph_dump\n");
        exit   (EXIT_FAILURE);
    }

    fprintf (grph_file,
             "digraph graph_task {\n"
             "    fontname=\"Helvetica,Arial,sans-serif\"\n"
             "    node [fontname=\"Helvetica,Arial,sans-serif\", style=filled, fillcolor=red]\n"
             "    edge [fontname=\"Helvetica,Arial,sans-serif\"]\n"
             "\n"
    );

    fprintf_declaration_nodes (grph_file, grph);

    fprintf_arcs (grph_file, grph);

    fprintf (grph_file, 
        "}\n"
    );

    fclose (grph_file);
}

//------------------------------------------------------------

static void fprintf_arcs (FILE* grph_file, graph* grph)
{
    assert (grph_file);
    assert (grph); 

    for (int i = 0; i < grph->num_of_vertices; i++)
    {
        if (grph->alive_vertices[i])
            for (int i_out = 0; i_out < grph->buf_vertices[i].num_of_out_arcs; i_out++)
                if (grph->buf_vertices[i].out_arcs[i_out] != POISON_VERTEX)
                    fprintf (grph_file, "    %d -> %d\n", i + 1, grph->buf_vertices[i].out_arcs[i_out] + 1);
    }
    
    fprintf (grph_file, "\n");  
}

//------------------------------------------------------------

static void fprintf_declaration_nodes (FILE* grph_file, graph* grph)
{
    assert (grph_file);
    assert (grph); 

    int i_vertex = START_VERTEX;

    fprintf_special_node (grph_file, grph, "start", &i_vertex);

    for (; i_vertex < grph->num_of_vertices - 1; ++i_vertex)
    {
        if (grph->alive_vertices[i_vertex])
            fprintf (grph_file, "    %d [fillcolor=%s]\n", 
                     i_vertex + 1, 
                     grph->alive_vertices[i_vertex] ? "green" : "red");
    }
    
    fprintf (grph_file, "\n");

    fprintf_special_node (grph_file, grph, "stop", &i_vertex);    
}

//------------------------------------------------------------

static void fprintf_special_node (FILE* grph_file, graph* grph, const char* name_node, int* i_vertex)
{
    assert (grph_file);
    assert (grph);
    assert (name_node);

    fprintf (grph_file,
             "    %d [fillcolor=%s\n"
             "        shape=record\n"
             "        label=\"{%s | %d}\"\n"
             "    ];\n"
             "\n",
             (*i_vertex) + 1,
             grph->alive_vertices[(*i_vertex)] ? "green" : "red",
             name_node,
             (*i_vertex) + 1
    );

    (*i_vertex)++;
}

//------------------------------------------------------------

void graph_print (graph* grph)
{
    if (grph == NULL)
    {
        perror ("grph NULL\n");
        exit   (EXIT_FAILURE);
    }

    int new_num_of_vertices = 0;
    for (int i = 0; i < grph->num_of_vertices; i++)
        new_num_of_vertices += grph->alive_vertices[i];

    printf ("%d\n", new_num_of_vertices);

    int new_num_of_arcs = 0;
    for (int i = 0; i < grph->num_of_vertices; i++)
        if (grph->alive_vertices[i])
            for (int i_out = 0; i_out < grph->buf_vertices[i].num_of_out_arcs; i_out++)
                if (grph->buf_vertices[i].out_arcs[i_out] != POISON_VERTEX)
                    new_num_of_arcs++;

    printf ("%d\n", new_num_of_arcs);

    for (int i = 0; i < grph->num_of_vertices; i++)
    {
        if (grph->alive_vertices[i])
        {
            selection_sort (grph->buf_vertices[i].out_arcs, grph->buf_vertices[i].num_of_out_arcs);

            for (int i_out = 0; i_out < grph->buf_vertices[i].num_of_out_arcs; i_out++)
                if (grph->buf_vertices[i].out_arcs[i_out] != POISON_VERTEX)
                    printf ("%d %d\n", i + 1, grph->buf_vertices[i].out_arcs[i_out] + 1);
        }
    }

}

//------------------------------------------------------------

static void selection_sort (int* array, int size)
{
    int i       = 0;
    int j       = 0;
    int min_idx = 0;

    for (i = 0; i < size - 1; i++)
    {
        min_idx = i;
        for (j =  i + 1; j < size; j++)
            if (array[j] < array[min_idx])
                min_idx = j;

        swap (&array[min_idx], &array[i]);
    }
}

//------------------------------------------------------------

static void swap (int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

