#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "dictMenu.h"
#include "documentView.h"
#include "structs.h"

char *selectedDict = NULL;

void showDictMenu()
{
    int ans;
    int i;
    const char menuItems[7][100] =
    {
        "1. Select a directory",
        "2. Close the directory",
        "3. Display the directory",
        "4. Edit a record in the directory",
        "5. Add a record in the directory",
        "6. Delete a record in the directory",
        "7. Back"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 7; i++)
            printf("%s\n", menuItems[i]);
        printf("\nEnter a menu item: ");
        scanf("%d", &ans);
        clearBuff();
        switch(ans)
        {
            case 1: selectDict(); break;
            case 2: closeDict(); break;
            case 3: showDict(); break;
            case 4: break;
            case 5: break;
            case 6: break;
            case 7: return;
            default: {
                        system("clear");
                        printf("There's no such menu item.\nPress ENTER to continue...");
                        wait();
                     }
         }
     }
}

void selectDict()
{
    if (!selectedDict)
    {
        int ans;
        system("clear");
        printf("1. type.db\n2. place.db\n");
        printf("\nEnter a number of directory: ");
        scanf("%d", &ans);
        clearBuff();
        switch(ans)
        {
        case 1: selectedDict = "type.db"; printf("Selected directory: %s", selectedDict); wait(); break;
        case 2: selectedDict = "place.db"; printf("Selected directory: %s", selectedDict); wait(); break;
        default: {
                    system("clear");
                    printf("There's no such menu item.\nPress ENTER to continue...");
                    wait();
                 }
        }
    }
    else
    {
        system("clear");
        printf("You already have selected file: %s\nPress ENTER to continue...", selectedDict);
        wait();
        return;
    }
}

void closeDict()
{
    selectedDict = NULL;
    if (headDict_t)
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
    }
    if (headDict_p)
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
    }
    system("clear");
    printf("File is successfully closed.\nPress ENTER to continue...");
    wait();
}

void showDict()
{
    if (!selectedDict)
    {
        system("clear");
        printf("Files isn't selected. It can't be opened.\nPress ENTER to continue...");
        wait();
        return;
    }
    if (selectedDict == "type.db" && !headDict_t)
        createDict_T();
    if (selectedDict == "place.db" && !headDict_t)
        createDict_P();
    if (selectedDict == "type.db")
    {
        DICT_T *nextItem;
        system("clear");
        printf("--------------------\n");
        printf("|%-3s|%-15s|\n", "ID", "Directory name");
        printf("--------------------\n");
        for (nextItem = headDict_t; nextItem != NULL; nextItem = nextItem->next)
            printf("|%-3d|%-15s|\n", nextItem->id, nextItem->dictName);
        printf("--------------------\n");
        printf("\nAmount of records: %d\nPress ENTER to continue...", numOfDict_T);
        wait();
    }
    if (selectedDict == "place.db")
    {
        DICT_P *nextItem;
        system("clear");
        printf("--------------------\n");
        printf("|%-3s|%-15s|\n", "ID", "Directory name");
        printf("--------------------\n");
        for (nextItem = headDict_p; nextItem != NULL; nextItem = nextItem->next)
            printf("|%-3d|%-15s|\n", nextItem->id, nextItem->dictName);
        printf("--------------------\n");
        printf("\nAmount of records: %d\nPress ENTER to continue...", numOfDict_P);
        wait();
    }

}
