#ifndef LINES_H
#define LINES_H

#include "dynamiclist.h"
#include <stddef.h>

#define GAP_WIDTH 4

size_t get_max_output_line_len(dynamiclist_t *field_lengths);
void strip_newline(char **s);

void format_line(char *noformat,
                 char **formatted,
                 dynamiclist_t *field_lengths);

#endif
