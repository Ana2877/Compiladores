#include <stdlib.h>
#include <stdio.h>
#include "parameter_type_list.h"

PARAMETER_TYPE_LIST *create_list(int datatype)
{
    PARAMETER_TYPE_LIST *parameter_type_list = (PARAMETER_TYPE_LIST *)malloc(sizeof(PARAMETER_TYPE_LIST));
    parameter_type_list->next = NULL;
    parameter_type_list->datatype = datatype;

    return parameter_type_list;
}

PARAMETER_TYPE_LIST *revert_list(PARAMETER_TYPE_LIST *list)
{
    PARAMETER_TYPE_LIST *next = NULL, *before = NULL, *curr = list;
    while (curr)
    {
        next = curr->next;
        curr->next = before;

        before = curr;
        curr = next;
    }

    return before;
}

PARAMETER_TYPE_LIST *append_end(PARAMETER_TYPE_LIST *to, PARAMETER_TYPE_LIST *from)
{
    if (!to)
        return from;

    PARAMETER_TYPE_LIST *curr = to;
    while (curr->next)
        curr = curr->next;
    curr->next = from;

    return to;
}

void free_list(PARAMETER_TYPE_LIST *list)
{
    PARAMETER_TYPE_LIST *next = NULL;
    while (list)
    {
        next = list->next;
        free(list);

        list = next;
    }
}

void print_list(PARAMETER_TYPE_LIST *list)
{
    printf("[");
    while (list)
    {
        printf("datatype %d", list->datatype);
        if (list->next)
            printf(", ");

        list = list->next;
    }
    printf("]\n");
}
