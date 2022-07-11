#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct DIR_ITEM
{
    char dirItemName[256];
    int id;
    struct DIR_ITEM *next;
} DIR_ITEM;

#endif // STRUCTS_H
