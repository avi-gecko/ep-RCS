#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "fileMenu.h"
#include <dirent.h>
#include <string.h>
#include "structs.h"
#include <malloc.h>
#include "documentView.h"
#include "dictMenu.h"

DIR_ITEM *headDirItems = NULL;
DIR_ITEM *selectedFile = NULL;

void showFileMenu()
{
    int ans;
    int i;
    const char menuItems[4][100] =
    {
        "1. Open",
        "2. Save",
        "3. Close",
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
            case 1: selectFile(); break;
            case 2: break;
            case 3: close(); break;
            case 4: return;
            default: {
                        system("clear");
                        printf("There's no such menu item.\nPress ENTER to continue...");
                        wait();
                     }
         }
     }
}

void selectFile()
{
    DIR *dir = NULL;
    struct dirent *ent = NULL;
    DIR_ITEM *nextItem;
    int count = 0;
    unsigned int ans;

    if (!headDirItems)
    {
        if ((dir = opendir("./DATA")) != NULL)
        {
            while ((ent = readdir(dir)) != NULL)
            {
                if ((strcmp(ent->d_name, ".\0")) == 0 || (strcmp(ent->d_name, "..\0")) == 0)
                    continue;
                else
                    putItem(ent->d_name, ++count);
            }
            closedir(dir);
            count = 0;
        }
        else
        {
            system("clear");
            printf("Directory can't be opened.\nPress ENTER to continue...");
            wait();
            return;
        }
    }

    if (!selectedFile)
    {
        system("clear");
        for (nextItem = headDirItems; nextItem != NULL; nextItem = nextItem->next)
            printf("%d. %-s\n", nextItem->id, nextItem->dirItemName);
        printf("\nEnter a file number: ");
        scanf("%d", &ans);
        clearBuff();
        for (nextItem = headDirItems; nextItem != NULL; nextItem = nextItem->next)
            if (ans == nextItem->id)
            {
                selectedFile = nextItem;
                printf("\nSelected file: %s\nPress ENTER to continue...", selectedFile->dirItemName);
                break;
            }
        wait();
        return;
    }
    else
    {
        system("clear");
        printf("You already have selected file: %s\nPress ENTER to continue...", selectedFile->dirItemName);
        wait();
        return;
    }
}

void putItem(char *itemName, int id)
{
    DIR_ITEM *newItem, *nextItem, *prevItem = NULL;
    for (nextItem = headDirItems; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next);
    newItem = (DIR_ITEM *) malloc(sizeof(DIR_ITEM));
    newItem->id = id;
    newItem->next = NULL;
    strcpy(newItem->dirItemName, itemName);
    if (!prevItem) headDirItems = newItem;
    else prevItem->next = newItem;
}

void close()
{
    if (selectedFile)
        selectedFile = NULL;
    if (headData)
    {
        DATA *nextItem, *prevItem = headData;
        for (nextItem = prevItem->next; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
        {
            free(prevItem->date);
            free(prevItem->codeItem);
            free(prevItem);
        }
        free(prevItem->date);
        free(prevItem->codeItem);
        free(prevItem);
        headData = NULL;
    }
    if (headDict_t && !selectedDict)
    {
        DICT_T *nextItem, *prevItem = headDict_t;
        for (nextItem = prevItem->next; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
        {
            free(prevItem->dictName);
            free(prevItem);
        }
        free(prevItem->dictName);
        free(prevItem);
        headDict_t = NULL;
        numOfDict_T = 0;
    }
    if (headDict_p && !selectedDict)
    {
        DICT_P *nextItem, *prevItem = headDict_p;
        for (nextItem = prevItem->next; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
        {
            free(prevItem->dictName);
            free(prevItem);
        }
        free(prevItem->dictName);
        free(prevItem);
        headDict_p = NULL;
        numOfDict_P = 0;
    }
    if (headMain_data)
    {
        MAIN_DATA *nextItem, *prevItem = headMain_data;
        for (nextItem = prevItem->next; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
        {
            free(prevItem->place);
            free(prevItem->type);
            free(prevItem);
        }
        free(prevItem->place);
        free(prevItem->type);
        free(prevItem);
        headMain_data = NULL;
    }
    numOfEnt = 0;
    system("clear");
    printf("File is successfully closed.\nPress ENTER to continue...");
    wait();
}
