/*
 * VDF - View Delimited File
 * FILE main.c
 */

#include "argparser.h"
#include <assert.h>
#include "dynamiclist.h"
#include "fileparser.h"
#include "globals.h"
#include "lines.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int
main (int argc, char **argv)
{
    argi = argc;
    args = argv;

    argparser_main();

    extern int optind;
    FILE *fp = fopen(args[optind], "r");
    assert(fp != NULL);

    dynamiclist_t *line_positions = init_dynamic_list(sizeof(fpos_t));
    dynamiclist_t *line_nums_to_print = init_dynamic_list(sizeof(size_t));
    dynamiclist_t *field_lengths = init_dynamic_list(sizeof(size_t));

    get_line_positions(fp, &line_positions, lFlaghigh);
    get_line_nums_to_print(&line_nums_to_print,
                          (int64_t) line_positions->length - 1);

    get_max_field_lens(fp,
                       line_positions,
                       line_nums_to_print,
                       &field_lengths);

    size_t max_output_line_len = get_max_output_line_len(field_lengths);
    char *formatted_line = malloc(max_output_line_len);

    size_t input_line_len = 64;
    char *input_line = malloc(input_line_len);

    size_t i;
    for (i = 0; i < line_nums_to_print->length; ++i)
    {
        size_t next_line = (size_t) line_nums_to_print->values[i];
        fpos_t next_line_pos = (fpos_t) line_positions->values[next_line];
        fsetpos(fp, &next_line_pos);

        getline(&input_line, &input_line_len, fp);
        strip_newline(&input_line);

        if (max_output_line_len > 0) formatted_line[0] = '\0';

        format_line(input_line, &formatted_line, field_lengths);
        printf("%s\n", formatted_line);
    }

    free_dynamic_list(line_positions);
    free_dynamic_list(line_nums_to_print);
    free_dynamic_list(field_lengths);
    fclose(fp);

    return 0;
}
