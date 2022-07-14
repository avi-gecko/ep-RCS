#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFunc.h"
#include "editMenu.h"
#include "structs.h"
#include "documentView.h"
#include "fileMenu.h"

void showEditMenu()
{
    int ans;
    int i;
    const char menuItems[4][100] =
    {
        "1. Add a record",
        "2. Delete a record",
        "3. Edit an existing record",
        "4. Back"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 4; i++)
            printf("%s\n", menuItems[i]);
        printf("\nEnter a menu item: ");
        scanf("%d", &ans);
        clearBuff();
        switch(ans)
        {
            case 1: addItem(); break;
            case 2: break;
            case 3: break;
            case 4: return;
            default: {
                        system("clear");
                        printf("There's no such menu item.\nPress ENTER to continue...");
                        wait();
                     }
         }
     }
}

void addItem()
{
    DICT_P *nextItemP;
    DICT_T *nextItemT;
    DATA *newItem, *prevItem = NULL, *nextItem;
    char *codeItem = NULL;
    unsigned int idType;
    unsigned int idPlace;
    char *date = NULL;
    unsigned int cost;
    char *type = NULL;
    char *place = NULL;
    size_t len = 0;
    ssize_t read = 0;
    int isMatched = 0;
    if (choosedFile && (!headData && !headDict_t && !headDict_p && !headMain_data))
    {
        createData();
        createDict_T();
        createDict_P();
        createMain_Data();
    }
    else
    if (!choosedFile)
    {
        system("clear");
        printf("Files isn't choosed. It can't be opened.\nPress ENTER to continue...");
        wait();
        return;
    }
    for (nextItem = headData; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
    {
        if (prevItem && nextItem)
            if(nextItem->id - prevItem->id != 1)
                break;
    }
    newItem = (DATA *) malloc(sizeof(DATA));
    system("clear");
    printf("Enter a code of RCS: ");
    read = getline(&codeItem, &len, stdin);
    if (read > 8)
    {
        system("clear");
        printf("Entered number of symbols is more than 6.\nPress ENTER to continue...");
        free(codeItem);
        free(newItem);
        wait();
        return;
    }
    codeItem[strcspn(codeItem, "\n")] = '\0';
    read = 0;
    len = 0;
    printf("\nEnter a ID of type of RCS: ");
    scanf("%d", &idType);
    clearBuff();
    for (nextItemT = headDict_t; nextItemT != NULL; nextItemT = nextItemT->next)
        if (idType == nextItemT->id)
            isMatched = 1;
    if (!isMatched)
    {
        system("clear");
        printf("The ID %d doesn't exist.\nPress ENTER to continue...", idType);
        free(codeItem);
        free(newItem);
        wait();
        return;
    }
    isMatched = 0;
    printf("\nEnter a ID of of place in the warehouse of RCS: ");
    scanf("%d", &idPlace);
    clearBuff();
    for (nextItemP = headDict_p; nextItemP != NULL; nextItemP = nextItemP->next)
    if (idPlace == nextItemP->id)
        isMatched = 1;
    if (!isMatched)
    {
        system("clear");
        printf("The ID %d doesn't exist.\nPress ENTER to continue...", idPlace);
        free(codeItem);
        free(newItem);
        wait();
        return;
    }
    printf("\nEnter a date of production of RCS: ");
    read = getline(&date, &len, stdin);
    if (read > 9)
    {
        system("clear");
        printf("Entered number of symbols is more than 8.\nPress ENTER to continue...");
        free(codeItem);
        free(date);
        free(newItem);
        wait();
        return;
    }
    date[strcspn(date, "\n")] = '\0';
    printf("\nEnter a cost of RCS: ");
    scanf("%d", &cost);
    newItem->codeItem = codeItem;
    newItem->idType = idType;
    newItem->idPlace = idPlace;
    newItem->date = date;
    newItem->cost = cost;
    if (nextItem)
        newItem->next = nextItem;
    else
        newItem->next = NULL;
    numOfEnt++;
    if (!prevItem)
    {
        headData = newItem;
        newItem->id = 1;
    }
    else
    {
        prevItem->next = newItem;
        newItem->id = prevItem->id + 1;
    }
    matchItem(idType, idPlace, &type, &place);
    putMain_Data(newItem->id, codeItem, type, place, date, newItem->cost);
}
