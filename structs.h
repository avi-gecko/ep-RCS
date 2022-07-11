#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct DIR_ITEM
{
    char dirItemName[256];
    int id;
    struct DIR_ITEM *next;
} DIR_ITEM;

typedef struct DATA
{
    int id;
    char *codeItem;
    int idType;
    int idPlace;
    char *date;
    int cost;
} DATA;

#endif // STRUCTS_H
