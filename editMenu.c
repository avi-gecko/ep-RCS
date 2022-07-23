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
            case 1: addRecord(); break;
            case 2: delRecord(); break;
            case 3: editRecord(); break;
            case 4: return;
            default: {
                        system("clear");
                        printf("There's no such menu item.\nPress ENTER to continue...");
                        wait();
                     }
         }
     }
}

void addRecord()
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

    DATA *newItem, *prevItem = NULL, *nextItem;
    for (nextItem = headData; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
    {
        if (headData->id != 1)
            break;
        if (prevItem && nextItem)
            if(nextItem->id - prevItem->id != 1)
                break;
    }
    newItem = (DATA *) malloc(sizeof(DATA));
    system("clear");
    printf("Enter a code of RCS: ");
    read = getline(&codeItem, &len, stdin);
    if (read > 7)
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
    DICT *nextItemT;
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
    DICT *nextItemP;
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
    clearBuff();
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
    system("clear");
    printf("Additing is successful.\nPress ENTER to continue...");
    wait();
}

void delRecord()
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

    unsigned int id;
    int isMatched = 0;

    system("clear");
    printf("Enter an id of item to delete: ");
    scanf("%d", &id);
    clearBuff();
    DATA *nextItem, *prevItem = NULL;
    for (nextItem = headData; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
        if (id == nextItem->id)
        {
            isMatched = 1;
            if (!prevItem)
            {
                headData = nextItem->next;
                free(nextItem->codeItem);
                free(nextItem->date);
                free(nextItem);
            }
            else
            {
                prevItem->next = nextItem->next;
                free(nextItem->codeItem);
                free(nextItem->date);
                free(nextItem);
            }
            break;
        }
    if (!isMatched)
    {
        system("clear");
        printf("The ID %d doesn't exist.\nPress ENTER to continue...", id);
        wait();
        return;
    }
    MAIN_DATA *nextItemM, *prevItemM = NULL;
    for (nextItemM = headMain_data; nextItemM != NULL; prevItemM = nextItemM, nextItemM = nextItemM->next)
        if (id == nextItemM->id)
        {
            if (!prevItemM)
            {
                headMain_data = nextItemM->next;
                free(nextItemM);
            }
            else
            {
                prevItemM->next = nextItemM->next;
                free(nextItemM);
            }
            break;
        }
    numOfEnt--;
    system("clear");
    printf("Deleting is successful.\nPress ENTER to continue...");
    wait();
}

void editRecord()
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

    unsigned int id;
    char *codeItem = NULL;
    unsigned int idType; char *type = NULL;
    unsigned int idPlace; char *place = NULL;
    char *date;
    unsigned int cost;
    int isMatched = 0;
    int isMatchedG = 0;
    size_t len = 0;
    ssize_t read = 0;

    system("clear");
    printf("Enter an id of item to edit: ");
    scanf("%d", &id);
    clearBuff();
    DATA *nextItem;
    for (nextItem = headData; nextItem != NULL; nextItem = nextItem->next)
        if (id == nextItem->id)
        {
            isMatchedG = 1;
            printf("\nEnter a code of RCS: ");
            read = getline(&codeItem, &len, stdin);
            if (read > 7)
            {
                system("clear");
                printf("Entered number of symbols is more than 6.\nPress ENTER to continue...");
                free(codeItem);
                wait();
                return;
            }
            codeItem[strcspn(codeItem, "\n")] = '\0';
            read = 0;
            len = 0;
            free(nextItem->codeItem);
            nextItem->codeItem = codeItem;
            printf("\nEnter a ID of type of RCS: ");
            scanf("%d", &idType);
            clearBuff();
            DICT *nextItemT;
            for (nextItemT = headDict_t; nextItemT != NULL; nextItemT = nextItemT->next)
                if (idType == nextItemT->id)
                    isMatched = 1;
            if (!isMatched)
            {
                system("clear");
                printf("The ID %d doesn't exist.\nPress ENTER to continue...", idType);
                free(codeItem);
                wait();
                return;
            }
            isMatched = 0;
            printf("\nEnter a ID of of place in the warehouse of RCS: ");
            scanf("%d", &idPlace);
            clearBuff();
            DICT *nextItemP;
            for (nextItemP = headDict_p; nextItemP != NULL; nextItemP = nextItemP->next)
            if (idPlace == nextItemP->id)
                isMatched = 1;
            if (!isMatched)
            {
                system("clear");
                printf("The ID %d doesn't exist.\nPress ENTER to continue...", idPlace);
                free(codeItem);
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
                wait();
                return;
            }
            date[strcspn(date, "\n")] = '\0';
            free(nextItem->date);
            nextItem->date = date;
            printf("\nEnter a cost of RCS: ");
            scanf("%d", &cost);
            clearBuff();
            nextItem->cost = cost;
            break;
        }
    if (!isMatchedG)
    {
        system("clear");
        printf("The ID %d doesn't exist.\nPress ENTER to continue...", id);
        wait();
        return;
    }
    MAIN_DATA *nextItemM;
    for (nextItemM = headMain_data; nextItemM != NULL; nextItemM = nextItemM->next)
        if (id == nextItemM->id)
        {
            nextItemM->codeItem = codeItem;
            nextItemM->date = date;
            matchItem(idType, idPlace, &type, &place);
            nextItemM->type = type;
            nextItemM->place = place;
            nextItemM->cost = cost;
            break;
        }
    system("clear");
    printf("Editing is successful.\nPress ENTER to continue...");
    wait();
}
