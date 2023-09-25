#include <stdio.h>
#include <stdlib.h>

#include "parser_stdio.h"
#include "graph.h"

//------------------------------------------------------------

static const int LAUNCH_ARGC = 1;

//------------------------------------------------------------

int main (const int argc, const char* argv[])
{
    if (argc != LAUNCH_ARGC)
    {
        fprintf (stderr, "ERROR! Execute: %s\n", argv[0]);
        exit    (EXIT_FAILURE);
    }

    parser_stdio_dump (ps);

    graph* grph = graph_construct (ps);

    parser_stdio_dump (ps);

    parser_stdio_destruct (ps);

    graph_find_dead_vertices (grph);

    graph_free_dead_vertices (grph);

    graph_dump (grph);

    graph_print (grph);

    graph_destruct (grph);

    return 0;
}
