typedef struct parameter_type_list
{
  int datatype;
  struct parameter_type_list *next;
}PARAMETER_TYPE_LIST;


PARAMETER_TYPE_LIST *create_list(int datatype);
PARAMETER_TYPE_LIST *revert_list(PARAMETER_TYPE_LIST *list);
PARAMETER_TYPE_LIST *append_end(PARAMETER_TYPE_LIST *to, PARAMETER_TYPE_LIST *from);
void free_list(PARAMETER_TYPE_LIST *list);
void print_list(PARAMETER_TYPE_LIST *list);
