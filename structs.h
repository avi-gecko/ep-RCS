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
} DATA;

typedef struct DICT_T
{
    unsigned int id;
    char *dictName;
} DICT_T;

typedef struct DICT_P
{
    unsigned int id;
    char *dictName;
} DICT_P;

typedef struct MAIN_DATA
{
    unsigned int id;
    char *codeItem;
    char *type;
    char *place;
    char *date;
    unsigned int cost;
} MAIN_DATA;

#endif // STRUCTS_H
