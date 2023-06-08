#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

//-----------------------------------

//-------------------
// In general case this solution
// is non portable
//-------------------
uint32_t count_nonzero_bits (uint32_t num);

uint32_t parsing_stdin      (void);

void     output_to_screen   (uint32_t num);

//-----------------------------------

const int STDIN_ARGC = 1;
const int SCANF_RET  = 1;
const int NUM_BUF    = 16;
const int NUM_BASE   = 10;

//-----------------------------------

int main (int argc, char* argv[])
{
    if (argc != STDIN_ARGC)
    {
        fprintf (stderr, "ERROR! Execute: %s\n", argv[0]);
        exit    (EXIT_FAILURE);
    }

    uint32_t num = parsing_stdin ();

    num = count_nonzero_bits (num);
    
    output_to_screen (num);
 
    return 0;
}

//-----------------------------------

uint32_t count_nonzero_bits (uint32_t num)
{
    return __builtin_popcount (num);
}

//-----------------------------------

uint32_t parsing_stdin (void)
{
    char num_buf[NUM_BUF];
    memset (num_buf, 0, NUM_BUF * sizeof (char));

    if (scanf ("%s", num_buf) != SCANF_RET)
    {
        fprintf (stderr, "ERROR! scanf input\n");
        exit    (EXIT_FAILURE);
    }

    char* end_num_buf = NULL;
    uint64_t num = strtoul (num_buf, &end_num_buf, NUM_BASE);

    if (errno != 0)
    {
        perror ("strtoul\n");
        exit   (EXIT_FAILURE);
    }

    if (num_buf == end_num_buf)
    {
        fprintf (stderr, "No digits were found\n");
        exit    (EXIT_FAILURE);
    }

    if (*end_num_buf != '\0')
    {
        fprintf (stderr, "Not a number\n");
        exit    (EXIT_FAILURE);
    }

    return num;
}

//-----------------------------------

void output_to_screen (uint32_t num)
{
    printf ("%" PRIu32 "\n", num);
}

