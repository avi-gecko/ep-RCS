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
static FILE *in = NULL, *fDict_T = NULL, *fDict_P = NULL;

void openDoc()
{
    char path[256] = "./DATA/";
    strcat(path, choosedFile->dirItemName);
    if ((in = fopen(path, "r")) == NULL)
    {
        system("clear");
        printf("Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
    if ((fDict_T = fopen("./DICTIONARY/type.db", "r")) == NULL)
    {
        system("clear");
        printf("Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
    if ((fDict_P = fopen("./DICTIONARY/place.db", "r")) == NULL)
    {
        system("clear");
        printf("Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
}

void createData()
{
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
        codeItem = strtok(NULL, ";");
        idType = atoi(strtok(NULL, ";"));
        idPlace = atoi(strtok(NULL, ";"));
        date = strtok(NULL, ";");
        cost = atoi(strtok(NULL, ";"));
        putData(id, codeItem, idType, idPlace, date, cost);
        temp = NULL;
    }
    fclose(in);
}

void putData(unsigned int id, char *codeItem, unsigned int idType, unsigned int idPlace, char *date, unsigned int cost)
{
    DATA *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headData; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next);
    newItem = (DATA *) malloc(sizeof(DATA));
    newItem->id = id;
    newItem->codeItem = codeItem;
    newItem->idType = idType;
    newItem->idPlace = idPlace;
    newItem->date = date;
    newItem->cost = cost;
    newItem->next = nextItem;
    if (!prevItem) headData = newItem;
    else prevItem->next = newItem;
}

void createDict_T()
{
    char *temp = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int id;
    char *dictName = NULL;
    while ((read = getline(&temp, &len, fDict_T)) != EOF)
    {
        id = atoi(strtok(temp, ";"));
        dictName = strtok(NULL, ";");
        putDict_T(id, dictName);
        temp = NULL;
    }
    /*if (!numOfDict_T)
    {
        DICT_T *nextItem, *prevItem = NULL;
        for (nextItem = headDict_t; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next);
        numOfDict_T = prevItem->id;
    }*/
    fclose(fDict_T);
}

void putDict_T(unsigned int id, char *dictName)
{
    DICT_T *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headDict_t; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next);
    newItem = (DICT_T *) malloc(sizeof(DICT_T));
    newItem->id = id;
    newItem->dictName = dictName;
    newItem->next = nextItem;
    if (!prevItem) headDict_t = newItem;
    else prevItem->next = newItem;
}

void createDict_P()
{
    char *temp = NULL;
    size_t len = 0;
    ssize_t read;
    unsigned int id;
    char *dictName = NULL;
    while ((read = getline(&temp, &len, fDict_P)) != EOF)
    {
        id = atoi(strtok(temp, ";"));
        dictName = strtok(NULL, ";");
        putDict_P(id, dictName);
        temp = NULL;
    }
  /*  if (!numOfDict_P)
    {
        DICT_P *nextItem, *prevItem = NULL;
        for (nextItem = headDict_p; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next);
        numOfDict_P = prevItem->id;
    }*/
    fclose(fDict_P);
}

void putDict_P(unsigned int id, char *dictName)
{
    DICT_P *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headDict_p; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next);
    newItem = (DICT_P *) malloc(sizeof(DICT_P));
    newItem->id = id;
    newItem->dictName = dictName;
    newItem->next = nextItem;
    if (!prevItem) headDict_p = newItem;
    else prevItem->next = newItem;
}

void creatMain_Data()
{
    DICT_P *nextItemP;
    DICT_T *nextItemT;
    DATA *nextItemD, *prevItemD = NULL;
    if (!numOfEnt)
    {
        for (nextItemD = headData; nextItemD != NULL; prevItemD = nextItemD, nextItemD = nextItemD->next);
        numOfEnt = prevItemD->id;
    }
    unsigned int i;
    unsigned int id;
    char *codeItem = NULL;
    char *type = NULL; unsigned int idType;
    char *place = NULL; unsigned int idPlace;
    char *date = NULL;
    unsigned int cost;
    for (i = 1; i <= numOfEnt; i++)
    {
        for (nextItemD = headData; nextItemD != NULL; nextItemD = nextItemD->next)
            if (i == nextItemD->id)
            {
                id = nextItemD->id;
                codeItem = nextItemD->codeItem;
                date = nextItemD->date;
                cost = nextItemD->cost;
                idType = nextItemD->idType;
                idPlace = nextItemD->idPlace;
                break;
            }
        for (nextItemT = headDict_t; nextItemT != NULL; nextItemT = nextItemT->next)
            if (idType == nextItemT->id)
            {
                type = nextItemT->dictName;
                break;
            }
        for (nextItemP = headDict_p; nextItemP != NULL; nextItemP = nextItemP->next)
            if (idPlace == nextItemP->id)
            {
                place = nextItemP->dictName;
                break;
            }
        putMain_Data(id, codeItem, type, place, date, cost);
    }
}

void putMain_Data(unsigned int id, char *codeItem, char *type, char *place, char *date, unsigned int cost)
{
    MAIN_DATA *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headMain_data; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next);
    newItem = (MAIN_DATA *) malloc(sizeof(MAIN_DATA));
    newItem->id = id;
    newItem->codeItem = codeItem;
    newItem->type = type;
    newItem->place = place;
    newItem->date = date;
    newItem->cost = cost;
    newItem->next = nextItem;
    if (!prevItem) headMain_data = newItem;
    else prevItem->next = newItem;
}

void showDoc()
{
    if (choosedFile)
        openDoc();
    else
    {
        system("clear");
        printf("файл не выбран. Неудалось открыть файл.\nНажмите клавишу ENTER, чтобы продолжить...");
        wait();
        return;
    }
    if (!headData)
        createData();
    if (!headDict_t)
        createDict_T();
    if (!headDict_p)
        createDict_P();
    if (!headMain_data)
        creatMain_Data();
    system("clear");
    MAIN_DATA *nextItem;
    for (nextItem = headMain_data; nextItem != NULL; nextItem = nextItem->next)
        printf("| %-5d | %6s |\t %-25s \t| %-12s \t| %8s | %8d |\n", nextItem->id, nextItem->codeItem, nextItem->type, nextItem->place, nextItem->date, nextItem->cost);
    wait();
}
