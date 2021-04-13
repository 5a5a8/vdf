#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "dynamiclist.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


void get_line_nums_to_print(dynamiclist_t **to_print, int64_t lines_in_file);
void get_line_positions(FILE *fp,
                   dynamiclist_t **line_position_list,
                   size_t max_line_to_read);

void get_max_field_lens(FILE *fp, 
                        dynamiclist_t *line_positions,
                        dynamiclist_t *lines_to_print,
                        dynamiclist_t **field_lengths);



#endif
