#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>

#include "parser_stdio.h"

//------------------------------------------------------------

static const char* PS_DUMP_PATH = "./parser_stdio_dump.txt";

static const int MIN_NUM_OF_ARCS = 0;
static const int MAX_NUM_OF_ARCS = 10000000;

static const int MIN_NUM_OF_VERTICES = 2;
static const int MAX_NUM_OF_VERTICES = 1000000;

//-----

#define SIZE_NUM 8

//------------------------------------------------------------

static int  get_one_num_in_line (void);

static int  get_num             (char** buf_num, char last_symb);

static void get_arc             (int* buf_vertices);

//------------------------------------------------------------

parser_stdio* parser_stdio_construct (void)
{
    parser_stdio* ps = (parser_stdio*) calloc (1, sizeof(parser_stdio));
    if (ps == NULL)
    {
        perror ("calloc ps\n");
        exit   (EXIT_FAILURE);
    }

    ps->num_of_vertices = get_one_num_in_line ();
    if (ps->num_of_vertices < MIN_NUM_OF_VERTICES || ps->num_of_vertices > MAX_NUM_OF_VERTICES)
    {
        fprintf (stderr, "ERROR! Please, input correct num_of_vertices: 1 < N < 1000000\n");
        exit    (EXIT_FAILURE);
    }

    ps->num_of_arcs = get_one_num_in_line ();
    if (ps->num_of_arcs < MIN_NUM_OF_ARCS || ps->num_of_arcs > MAX_NUM_OF_ARCS)
    {
        fprintf (stderr, "ERROR! Please, input correct num_of_arcs: 2 < M < 10000000\n");
        exit    (EXIT_FAILURE);
    }

    ps->buf_vertices = (int (*)[2]) calloc (ps->num_of_arcs, sizeof(int[2]));
    if (ps->buf_vertices == NULL)
    {
        perror ("calloc (*buf_vertices)[2]\n");
        exit   (EXIT_FAILURE);
    }

    for (int i = 0; i < ps->num_of_arcs; i++)
    {
        get_arc (ps->buf_vertices[i]);

        if (ps->buf_vertices[i][0] < 0 || ps->buf_vertices[i][0] > ps->num_of_vertices - 1)
        {
            fprintf (stderr, "ERROR! Please, input correct arc: 1 < N < num_of_vertices\n");
            exit    (EXIT_FAILURE);
        }

        if (ps->buf_vertices[i][1] < 0 || ps->buf_vertices[i][1] > ps->num_of_vertices - 1)
        {
            fprintf (stderr, "ERROR! Please, input correct arc: 1 < N < num_of_vertices\n");
            exit    (EXIT_FAILURE);
        }
    }

    return ps;
}

//------------------------------------------------------------

void parser_stdio_destruct (parser_stdio* ps)
{
    if (ps == NULL)
    {
        perror ("ps == NULL\n");
        exit   (EXIT_FAILURE);
    }

    free (ps->buf_vertices);
    free (ps);
}

//------------------------------------------------------------

static int get_one_num_in_line (void)
{
    char* buf_num = (char*) calloc (SIZE_NUM + 1, sizeof(char));
    if (buf_num == NULL)
    {
        perror ("calloc buf_num\n");
        exit   (EXIT_FAILURE);
    }

    char* save_buf_num = buf_num;

    char* ret_fgets = fgets (buf_num, SIZE_NUM, stdin);
    if   (ret_fgets == NULL)
    {
        perror ("fgets\n");
        exit   (EXIT_FAILURE);
    }

    int num = get_num (&buf_num, '\n');

    free (save_buf_num);

    return num;
}

//------------------------------------------------------------

static int get_num (char** buf_num, char last_symb)
{
    assert (buf_num);

    if (!(isdigit (**buf_num) || **buf_num == '-' || **buf_num == '+'))
    {
        fprintf (stderr, "ERROR! isdigit(): start char is not a number...\n");
        exit    (EXIT_FAILURE);
    }

    int   num_base    = 10;
    char* end_num_str = NULL;
    
    int num = strtol (*buf_num, &end_num_str, num_base);

    if (errno != 0)
    {
        perror ("ERROR! strtol(): smth went wrong...");
        exit   (EXIT_FAILURE);
    }
 
    if (*end_num_str != last_symb)
    {
        fprintf (stderr, "ERROR! wrong in end of num...\n");
        exit    (EXIT_FAILURE);
    }

    if (*buf_num == end_num_str)
    {
        fprintf (stderr, "ERROR! strtol(): no digits were found...\n");
        exit    (EXIT_FAILURE);
    }

    *buf_num = end_num_str;

    return num;
}

//------------------------------------------------------------

static void get_arc (int* buf_vertices)
{
    // ['N','U','M',' ','N','U','M','\n']
    int size = 2 * SIZE_NUM + 2;

    char* buf_num = (char*) calloc (size, sizeof(char));
    if   (buf_num == NULL)
    {
        perror ("calloc buf_num\n");
        exit   (EXIT_FAILURE);
    }

    char* save_buf_num = buf_num;

    char* ret_fgets = fgets (buf_num, size, stdin);
    if   (ret_fgets == NULL)
    {
        perror ("fgets\n");
        exit   (EXIT_FAILURE);
    }

    buf_vertices[0] = get_num (&buf_num, ' ')  - 1;

    buf_num++;

    buf_vertices[1] = get_num (&buf_num, '\n') - 1;

    free (save_buf_num);
}

//------------------------------------------------------------

void parser_stdio_dump (parser_stdio* ps)
{
    if (ps == NULL)
    {
        fprintf (stderr, "ERROR! pd == NULL\n");
        exit    (EXIT_FAILURE);
    }

    FILE* dump = fopen (PS_DUMP_PATH, "wb");
    if (dump == NULL)
    {
        perror ("fopen pd_dump\n");
        exit   (EXIT_FAILURE);
    }

    fprintf (dump,     "|-------------------------------------|\n"
                       "|           DUMP PARSER STDIO         |\n"
                       "|-------------------------------------|\n"
                       "{\n"
                       "    num_of_vertices = [%d];\n"
                       "    num_of_arcs     = [%d];\n"
                       "    buf_vertices    = [%p];\n"
                       "\n"
                       "    Buffer Vertices:\n",
                            ps->num_of_vertices,
                            ps->num_of_arcs,
                            ps->buf_vertices
    );

    for (int i = 0; i < ps->num_of_arcs; i++)
    {
        fprintf (dump, "    (%3d) [{%3d} -> {%3d}]\n", 
                 i + 1, 
                 ps->buf_vertices[i][0], 
                 ps->buf_vertices[i][1]
        );
    }

    fprintf (dump,     "}\n"
                       "|-------------------------------------|\n"
                       "|        END DUMP PARSER STDIO        |\n"
                       "|-------------------------------------|\n"
                       );


    fclose (dump);
}

//------------------------------------------------------------
