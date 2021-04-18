#include "error.h"
#include "globals.h"
#include "lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void wrap_text(char *noformat,
			   char **formatted,
			   dynamiclist_t *field_lengths);

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
		size_t wrap_width = (size_t) strtoll(args[wFlagindex], NULL, 10);
		check_strtoll_error(wrap_width);
		for (i=0; i<field_lengths->length; ++i)
		{
			size_t newlines_to_insert = 1 + 
								(size_t) field_lengths->values[i] / wrap_width;

			size_t spaces_to_insert = 1 + 
								(size_t) field_lengths->values[i] % wrap_width;

			req_line_len += (size_t ) field_lengths->values[i]
						  + newlines_to_insert
						  + spaces_to_insert
						  + GAP_WIDTH;
		}
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
	if (wFlag)
	{
		wrap_text(noformat, formatted, field_lengths);
		return;
	}
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


void
wrap_text(char *noformat,
		  char **formatted,
		  dynamiclist_t *field_lengths)
{
//	size_t wrap_width = strtoll(args[wFlagindex], NULL, 10);

//	size_t i;
//	char **fields = malloc(field_lengths->length * sizeof(char *));
//	for (i=0; i<field_lengths->length; ++i)
//	{
//		fields[i] = malloc((size_t) field_lengths->values[i]);
//	}
//
//	char *token;
//	for (i=0; (token = strsep(&noformat, delim)) != NULL; ++i)
//	{
//		strcpy(fields[i], token);
//	}
//
//	for (i=0; i<field_lengths->length; ++i)
//	{
//		for (j=0; i<strlen(fields[i]); ++j)
//		{
//			for (k=0; k<wrap_width; ++k)
//			{
//				(*formatted)[k] = noformat[k];
//			}
//			(*formatted)[k] = '\n';
//		}
//	}
}




















