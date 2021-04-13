#include "fileparser.h"
#include "globals.h"
#include "lines.h"
#include <stdlib.h>
#include <string.h>


void
get_line_nums_to_print(dynamiclist_t **to_print, int64_t lines_in_file)
{
    if (!xFlag)
    {
        append_dynamic_list(*to_print, (void *) 0);
    }

    int64_t i;
    for (i = lFlaglow; i != lFlaghigh + 1 && i <= lines_in_file; ++i)
    {
        append_dynamic_list(*to_print, (void *) i);
    }
}


void
get_line_positions(FILE *fp,
                   dynamiclist_t **line_position_list,
                   size_t max_line_to_read)
{
    rewind(fp);

    size_t buffer_size = 128;
    char *line_buffer = malloc(buffer_size);

    do
    {
        fpos_t cur_line_position;
        fgetpos(fp, &cur_line_position);
        append_dynamic_list(*line_position_list, (void *) cur_line_position);
    }
    while ((*line_position_list)->length != max_line_to_read + 1
            && getline(&line_buffer, &buffer_size, fp) != -1);

    free(line_buffer);
}


void
get_max_field_lens(FILE *fp, 
                   dynamiclist_t *line_positions,
                   dynamiclist_t *lines_to_print,
                   dynamiclist_t **field_lengths)
{
    extern char* delim;
    size_t buffer_size = 64;
    char *input_buffer = malloc(buffer_size);

    size_t i;
    for (i=0; i<lines_to_print->length; ++i)
    {
        size_t next_line = (size_t) lines_to_print->values[i];
        fpos_t next_line_position = (fpos_t) line_positions->values[next_line];
        fsetpos(fp, &next_line_position);
        getline(&input_buffer, &buffer_size, fp);

        strip_newline(&input_buffer);

        char *token;
        size_t n_fields;
        for (n_fields = 1;
            (token = strsep(&input_buffer, delim)) != NULL;
            ++n_fields)
        {
            if (n_fields > (*field_lengths)->length)
            {
                append_dynamic_list(*field_lengths, (void *) 0);
            }

            size_t len;
            if ((len = strlen(token)) > 
                (size_t) (*field_lengths)->values[n_fields - 1])
            {
                (*field_lengths)->values[n_fields - 1] = (void *) len;
            }
        }
    }

    free(input_buffer);
}


