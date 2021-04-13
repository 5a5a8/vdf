#include "dynamiclist.h"
#include <stdlib.h>


dynamiclist_t *
init_dynamic_list(size_t item_size)
{
    dynamiclist_t *list = calloc(1, sizeof(struct DYNAMICLIST_T));
    list->item_size = item_size;
    list->length = 0;
    list->values = NULL;

    return list;
}


void
append_dynamic_list(dynamiclist_t *list, void *item_to_append)
{
    ++(list->length);

    list->values = list->values == NULL ? 
    calloc(list->length, list->item_size) : 
    realloc(list->values, list->length * list->item_size);

    list->values[list->length - 1] = item_to_append;
}


void
free_dynamic_list(dynamiclist_t *list)
{
    free(list->values);
    free(list);
}
