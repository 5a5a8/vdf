#ifndef DYNAMICLIST_H
#define DYNAMICLIST_H

#include <stddef.h>

typedef struct DYNAMICLIST_T
{
    void **values;
    size_t length;
    size_t item_size;
} dynamiclist_t;


dynamiclist_t *init_dynamic_list(size_t length);
void append_dynamic_list(dynamiclist_t *list, void *item_to_append);
void free_dynamic_list(dynamiclist_t *list);


#endif
