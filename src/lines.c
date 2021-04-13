#include "globals.h"
#include "lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void
strip_newline(char **s)
{
    size_t line_len = strlen(*s);
    if ((*s)[line_len - 2] == '\r' && (*s)[line_len - 1] == '\n')
    {
        (*s)[line_len - 2] = '\0';
    }
    else if ((*s)[line_len - 1] == '\n')
    {
        (*s)[line_len - 1] = '\0';
    }
}


size_t
get_max_output_line_len(dynamiclist_t *field_lengths)
{
    size_t i;
    size_t req_line_len = 0;

    if (wFlag)
    {
        fprintf(stderr, "-w flag is not yet supported\n");
        exit(1); //TODO
    }
    else
    {
        for (i=0; i<field_lengths->length; ++i)
        {
            req_line_len += (size_t) field_lengths->values[i] + GAP_WIDTH;
        }
    }

    return req_line_len + 1;
}


void
format_line(char *noformat, char **formatted, dynamiclist_t *field_lengths)
{
    size_t i, j;
    char *token;
    for (i=0; (token = strsep(&noformat, delim)) != NULL; ++i)
    {
        size_t f_len = (size_t) field_lengths->values[i];
        strncat(*formatted, token, f_len);
        for (j = strlen(token); j < f_len + GAP_WIDTH; ++j)
        {
            strcat(*formatted, " ");
        }
    }
}
