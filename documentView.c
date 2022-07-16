#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "inputFunc.h"
#include "documentView.h"
#include "fileMenu.h"
#include "structs.h"

unsigned int numOfEnt = 0;
unsigned int numOfDict_T = 0;
unsigned int numOfDict_P = 0;
DATA *headData = NULL;
DICT_T *headDict_t = NULL;
DICT_P *headDict_p = NULL;
MAIN_DATA *headMain_data = NULL;
FILE *in = NULL, *fDict_T = NULL, *fDict_P = NULL;

void openFDict_P(char *mode)
{
    if ((fDict_P = fopen("./DICTIONARY/place.db", mode)) == NULL)
    {
        system("clear");
        printf("File can't be opened.\nPress ENTER to continue...");
        wait();
        return;
    }
}

void openFDict_T(char *mode)
{
    if ((fDict_T = fopen("./DICTIONARY/type.db", mode)) == NULL)
    {
        system("clear");
        printf("File can't be opened.\nPress ENTER to continue...");
        wait();
        return;
    }
}

void openIn(char *mode)
{
    char path[256] = "./DATA/";
    strcat(path, selectedFile->dirItemName);
    if ((in = fopen(path, mode)) == NULL)
    {
        system("clear");
        printf("File can't be opened.\nPress ENTER to continue...");
        wait();
        return;
    }
}

void createData()
{
    if (!in)
        openIn("r");
    if (!numOfEnt)
    {
        while (!feof(in))
            if (fgetc(in) == '\n')
                numOfEnt++;
        rewind(in);
    }
    char *temp = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int id;
    char *codeItem = NULL;
    unsigned int idType;
    unsigned int idPlace;
    char *date = NULL;
    unsigned int cost;
    while ((read = getline(&temp, &len, in)) != EOF)
    {
        id = atoi(strtok(temp, ";"));
        codeItem = strdup(strtok(NULL, ";"));
        idType = atoi(strtok(NULL, ";"));
        idPlace = atoi(strtok(NULL, ";"));
        date = strdup(strtok(NULL, ";"));
        cost = atoi(strtok(NULL, ";"));
        putData(id, codeItem, idType, idPlace, date, cost);
        free(temp);
        temp = NULL;
    }
    fclose(in);
    in = NULL;
}

void putData(unsigned int id, char *codeItem, unsigned int idType, unsigned int idPlace, char *date, unsigned int cost)
{
    DATA *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headData; nextItem != NULL && (id > nextItem->id); prevItem = nextItem, nextItem = nextItem->next);
    newItem = (DATA *) malloc(sizeof(DATA));
    newItem->id = id;
    newItem->codeItem = codeItem;
    newItem->idType = idType;
    newItem->idPlace = idPlace;
    newItem->date = date;
    newItem->cost = cost;
    if (nextItem)
        newItem->next = nextItem;
    else
        newItem->next = NULL;
    if (!prevItem)
        headData = newItem;
    else
        prevItem->next = newItem;
}

void createDict_T()
{
    if (!fDict_T)
        openFDict_T("r");
    if (!numOfDict_T)
    {
        while (!feof(fDict_T))
            if (fgetc(fDict_T) == '\n')
                numOfDict_T++;
        rewind(fDict_T);
    }
    unsigned int id;
    char *temp = NULL;
    size_t len = 0;
    ssize_t read;
    char *dictName = NULL;
    while ((read = getline(&temp, &len, fDict_T)) != EOF)
    {
        id = atoi(strtok(temp, ";"));
        dictName = strdup(strtok(NULL, ";"));
        putDict_T(id, dictName);
        free(temp);
        temp = NULL;
    }
    fclose(fDict_T);
    fDict_T = NULL;
}

void putDict_T(unsigned int id, char *dictName)
{
    DICT_T *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headDict_t; nextItem != NULL && (id > nextItem->id); prevItem = nextItem, nextItem = nextItem->next);
    newItem = (DICT_T *) malloc(sizeof(DICT_T));
    newItem->id = id;
    newItem->dictName = dictName;
    if (nextItem)
        newItem->next = nextItem;
    else
        newItem->next = NULL;
    if (!prevItem)
        headDict_t = newItem;
    else
        prevItem->next = newItem;
}

void createDict_P()
{
    if (!fDict_P)
        openFDict_P("r");
    if (!numOfDict_P)
    {
        while (!feof(fDict_P))
            if (fgetc(fDict_P) == '\n')
                numOfDict_P++;
        rewind(fDict_P);
    }
    char *temp = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int id;
    char *dictName = NULL;
    while ((read = getline(&temp, &len, fDict_P)) != EOF)
    {
        id = atoi(strtok(temp, ";"));
        dictName = strdup(strtok(NULL, ";"));
        putDict_P(id, dictName);
        free(temp);
        temp = NULL;
    }
    fclose(fDict_P);
    fDict_P = NULL;
}

void putDict_P(unsigned int id, char *dictName)
{
    DICT_P *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headDict_p; nextItem != NULL && (id > nextItem->id); prevItem = nextItem, nextItem = nextItem->next);
    newItem = (DICT_P *) malloc(sizeof(DICT_P));
    newItem->id = id;
    newItem->dictName = dictName;
    if (nextItem)
        newItem->next = nextItem;
    else
        newItem->next = NULL;
    if (!prevItem)
        headDict_p = newItem;
    else
        prevItem->next = newItem;
}

void createMain_Data()
{
    DICT_P *nextItemP;
    DICT_T *nextItemT;
    DATA *nextItemD;
    unsigned int id;
    char *codeItem = NULL;
    char *type = NULL; unsigned int idType;
    char *place = NULL; unsigned int idPlace;
    char *date = NULL;
    unsigned int cost;
    for (nextItemD = headData; nextItemD != NULL; nextItemD = nextItemD->next)
    {
        int isMatched = 0;
        id = nextItemD->id;
        codeItem = nextItemD->codeItem;
        date = nextItemD->date;
        cost = nextItemD->cost;
        idType = nextItemD->idType;
        idPlace = nextItemD->idPlace;

        for (nextItemT = headDict_t; nextItemT != NULL; nextItemT = nextItemT->next)
            if (idType == nextItemT->id)
            {
                isMatched = 1;
                type = strdup(nextItemT->dictName);
                break;
            }
        if (!isMatched)
        {
            system("clear");
            printf("There's no ID %d in the type.db directory.\nPress ENTER to continue...", idType);
            wait();
            return;
        }
        isMatched = 0;
        for (nextItemP = headDict_p; nextItemP != NULL; nextItemP = nextItemP->next)
            if (idPlace == nextItemP->id)
            {
                isMatched = 1;
                place = strdup(nextItemP->dictName);
                break;
            }
        if (!isMatched)
        {
            free(type);
            system("clear");
            printf("There's no ID %d in the place.db directory.\nPress ENTER to continue...", idPlace);
            wait();
            return;
        }
        putMain_Data(id, codeItem, type, place, date, cost);
    }
}

void matchItem(unsigned int idType, unsigned int idPlace, char **type, char **place)
{
    DICT_P *nextItemP;
    DICT_T *nextItemT;
    for (nextItemT = headDict_t; nextItemT != NULL; nextItemT = nextItemT->next)
        if (idType == nextItemT->id)
        {
            *type = strdup(nextItemT->dictName);
            break;
        }
    for (nextItemP = headDict_p; nextItemP != NULL; nextItemP = nextItemP->next)
        if (idPlace == nextItemP->id)
        {
            *place = strdup(nextItemP->dictName);
            break;
        }
}

void putMain_Data(unsigned int id, char *codeItem, char *type, char *place, char *date, unsigned int cost)
{
    MAIN_DATA *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headMain_data; nextItem != NULL && (id > nextItem->id); prevItem = nextItem, nextItem = nextItem->next);
    newItem = (MAIN_DATA *) malloc(sizeof(MAIN_DATA));
    newItem->id = id;
    newItem->codeItem = codeItem;
    newItem->type = type;
    newItem->place = place;
    newItem->date = date;
    newItem->cost = cost;
    if (nextItem)
        newItem->next = nextItem;
    else
        newItem->next = NULL;
    if (!prevItem)
        headMain_data = newItem;
    else
        prevItem->next = newItem;
}

void showDoc()
{
    if (!selectedFile)
    {
        system("clear");
        printf("Files isn't selected. It can't be opened.\nPress ENTER to continue...");
        wait();
        return;
    }
    if (!headDict_t)
        createDict_T();
    if (!headDict_p)
        createDict_P();
    if (!headData)
        createData();
    if (!headMain_data)
        createMain_Data();
    system("clear");
    MAIN_DATA *nextItem;
    printf(".------------------------------------------------------------------------.\n");
    printf("|%-6s|%-9s|%-21s|%-15s|%-8s|%8s|\n", "ID", "Item code", "Type", "Place", "Date", "Cost");
    printf("|------------------------------------------------------------------------|\n");
    for (nextItem = headMain_data; nextItem != NULL; nextItem = nextItem->next)
        printf("|%-6d|%-9s|%-21s|%-15s|%-8s|%8d|\n", nextItem->id, nextItem->codeItem, nextItem->type, nextItem->place, nextItem->date, nextItem->cost);
    printf("'------------------------------------------------------------------------'\n");
    printf("\nAmount of records: %d\nPress ENTER to continue...", numOfEnt);
    wait();
}
