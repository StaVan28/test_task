#ifndef PARSER_STDIO_H_INCLUDED
#define PARSER_STDIO_H_INCLUDED

//------------------------------------------------------------

/*! @brief   Struct for parsing stdio
    @version 1.0
    @authors StaVan28
    @date    26.07.2023
*/
typedef struct parser_stdio
{
    int num_of_vertices;

    int num_of_arcs;

    int (*buf_vertices)[2];
} parser_stdio;

//------------------------------------------------------------

/*! Construct a parser_stdio
    @param [in] None
    @return pointer on alloc struct parser_stdio
    @version 1.0
    @authors StaVan28

    <pre>
     Parsing occurs according to the principle
     The following data is provided on stdio >
     1| 7           -- added in num_of_vertices
     2| 7           -- added in num_of_arcs
     3| 1 2         \ 
     4| 1 3         |
     5| 1 4         |
     6| 4 5         |> added in buf_vertices
     7| 5 4         |
     8| 3 7         |
     9| 6 7         /
    10|
    </pre>
*/
parser_stdio* parser_stdio_construct (void);
              
//--------

/*! Destruct a parser_stdio
    @param[in] parser_stdio* ps pointer on alloc struct parser_stdio
    @return None
    @version 1.0
    @authors StaVan28

    Free memory buf_vertices and the structure itself parser_stdio
*/
void          parser_stdio_destruct (parser_stdio* ps);

//--------

/*! Dump a parser_stdio
    @param[in] parser_stdio* ps pointer on alloc struct parser_stdio
    @return None
    @version 1.0
    @authors StaVan28

    Prints a printout with all parameters output in a beautiful form to a file,
    defined in PS_DUMP_PATH
*/
void          parser_stdio_dump (parser_stdio* ps);

//------------------------------------------------------------

#endif // PARSER_STDIO_H_INCLUDED
