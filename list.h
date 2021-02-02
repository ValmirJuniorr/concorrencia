#ifndef LIST_H    /* This is an "include guard" */
#define LIST_H    /* prevents the file from being included twice. */

List *create_list(int max_length);

void add(List *list, int number);
void remove_last(List *list);
void print_list(List list);

#endif /* LIST_H */