#ifndef PARSER_STDIO_H_INCLUDED
#define PARSER_STDIO_H_INCLUDED

//------------------------------------------------------------

typedef struct parser_stdio
{
    int num_of_vertices;

    int num_of_arcs;

    int (*buf_vertices)[2];
} parser_stdio;

//------------------------------------------------------------

parser_stdio* parser_stdio_construct (void);

void          parser_stdio_destruct  (parser_stdio* ps);

void          parser_stdio_dump      (parser_stdio* ps);

//------------------------------------------------------------

#endif // PARSER_STDIO_H_INCLUDED
