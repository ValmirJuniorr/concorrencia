#ifndef CUSTOM_TYPES_H    /* This is an "include guard" */
#define CUSTOM_TYPES_H    /* prevents the file from being included twice. */

typedef struct Item
{
  int value;
  struct Item *prev, *next;
} Item;

typedef struct List
{
  struct Item *items, *first, *last;
  int length,  max_length;
} List;

#endif /* CUSTOM_TYPES_H */