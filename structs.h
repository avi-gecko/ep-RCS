#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct DIR_ITEM
{
    char dirItemName[256];
    unsigned int id;
    struct DIR_ITEM *next;
} DIR_ITEM;

typedef struct DATA
{
    unsigned int id;
    char *codeItem;
    unsigned int idType;
    unsigned int idPlace;
    char *date;
    unsigned int cost;
    struct DATA *next;
} DATA;

typedef struct DICT
{
    unsigned int id;
    char *dictName;
    struct DICT *next;
} DICT;

typedef struct MAIN_DATA
{
    unsigned int id;
    char *codeItem;
    char *type;
    char *place;
    char *date;
    unsigned int cost;
    struct MAIN_DATA *next;
} MAIN_DATA;

#endif // STRUCTS_H
