#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFunc.h"
#include "dictMenu.h"
#include "documentView.h"
#include "structs.h"

char *selectedDict = NULL;

void showDictMenu()
{
    int ans;
    int i;
    const char menuItems[8][100] =
    {
        "1. Select a directory",
        "2. Save the directory",
        "3. Close the directory",
        "4. Display the directory",
        "5. Edit a record in the directory",
        "6. Add a record in the directory",
        "7. Delete a record in the directory",
        "8. Back"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 8; i++)
            printf("%s\n", menuItems[i]);
        printf("\nEnter a menu item: ");
        scanf("%d", &ans);
        clearBuff();
        switch(ans)
        {
            case 1: selectDict(); break;
            case 2: saveDict(); break;
            case 3: closeDict(); break;
            case 4: showDict(); break;
            case 5: editRecordDict();break;
            case 6: addRecordDict(); break;
            case 7: delRecordDict(); break;
            case 8: return;
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
        numOfDict_T = 0;
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
        numOfDict_P = 0;
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
    if (selectedDict == "place.db" && !headDict_p)
        createDict_P();
    if (selectedDict == "type.db")
    {
        DICT_T *nextItem;
        system("clear");
        printf(".-------------------.\n");
        printf("|%-3s|%-15s|\n", "ID", "Directory name");
        printf("|-------------------|\n");
        for (nextItem = headDict_t; nextItem != NULL; nextItem = nextItem->next)
            printf("|%-3d|%-15s|\n", nextItem->id, nextItem->dictName);
        printf("'-------------------'\n");
        printf("\nAmount of records: %d\nPress ENTER to continue...", numOfDict_T);
        wait();
    }
    if (selectedDict == "place.db")
    {
        DICT_P *nextItem;
        system("clear");
        printf(".-------------------.\n");
        printf("|%-3s|%-15s|\n", "ID", "Directory name");
        printf("|-------------------|\n");
        for (nextItem = headDict_p; nextItem != NULL; nextItem = nextItem->next)
            printf("|%-3d|%-15s|\n", nextItem->id, nextItem->dictName);
        printf("'-------------------'\n");
        printf("\nAmount of records: %d\nPress ENTER to continue...", numOfDict_P);
        wait();
    }

}

void addRecordDict()
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
    if (selectedDict == "place.db" && !headDict_p)
        createDict_P();
    if (selectedDict == "type.db")
    {
        char *dictName = NULL;
        size_t len = 0;
        DICT_T *nextItem, *prevItem = NULL, *newItem;
        for (nextItem = headDict_t; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
        {
            if (headDict_t->id != 1)
                break;
            if (prevItem && nextItem)
                if(nextItem->id - prevItem->id != 1)
                    break;
        }
        newItem = (DICT_T *) malloc(sizeof(DICT_T));
        system("clear");
        printf("Enter a new type: ");
        getline(&dictName, &len, stdin);
        dictName[strcspn(dictName, "\n")] = '\0';
        newItem->dictName = dictName;
        if (nextItem)
            newItem->next = nextItem;
        else
            newItem->next = NULL;
        numOfDict_T++;
        if (!prevItem)
        {
            headDict_t = newItem;
            newItem->id = 1;
        }
        else
        {
            prevItem->next = newItem;
            newItem->id = prevItem->id + 1;
        }
        system("clear");
        printf("Additing is successful.\nPress ENTER to continue...");
        wait();
        return;
    }
    if (selectedDict == "place.db")
    {
        char *dictName = NULL;
        size_t len = 0;
        DICT_P *nextItem, *prevItem = NULL, *newItem;
        for (nextItem = headDict_p; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
        {
            if (headDict_p->id != 1)
                break;
            if (prevItem && nextItem)
                if(nextItem->id - prevItem->id != 1)
                    break;
        }
        newItem = (DICT_P *) malloc(sizeof(DICT_P));
        system("clear");
        printf("Enter a new type: ");
        getline(&dictName, &len, stdin);
        dictName[strcspn(dictName, "\n")] = '\0';
        newItem->dictName = dictName;
        if (nextItem)
            newItem->next = nextItem;
        else
            newItem->next = NULL;
        numOfDict_P++;
        if (!prevItem)
        {
            headDict_p = newItem;
            newItem->id = 1;
        }
        else
        {
            prevItem->next = newItem;
            newItem->id = prevItem->id + 1;
        }
        system("clear");
        printf("Additing is successful.\nPress ENTER to continue...");
        wait();
        return;
    }
}

void delRecordDict()
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
    if (selectedDict == "place.db" && !headDict_p)
        createDict_P();
    if (selectedDict == "type.db")
    {
        int isMatched = 0;
        unsigned int id;
        system("clear");
        printf("Enter an id of item to delete: ");
        scanf("%d", &id);
        clearBuff();
        DICT_T *nextItem, *prevItem = NULL;
        for (nextItem = headDict_t; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
            if (id == nextItem->id)
            {
                isMatched = 1;
                if (!prevItem)
                {
                    headDict_t = nextItem->next;
                    free(nextItem->dictName);
                    free(nextItem);
                }
                else
                {
                    prevItem->next = nextItem->next;
                    free(nextItem->dictName);
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
        numOfDict_T--;
        system("clear");
        printf("Deleting is successful.\nPress ENTER to continue...");
        wait();
        return;
    }
    if (selectedDict == "place.db")
    {
        int isMatched = 0;
        unsigned int id;
        system("clear");
        printf("Enter an id of item to delete: ");
        scanf("%d", &id);
        clearBuff();
        DICT_P *nextItem, *prevItem = NULL;
        for (nextItem = headDict_p; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
            if (id == nextItem->id)
            {
                isMatched = 1;
                if (!prevItem)
                {
                    headDict_p = nextItem->next;
                    free(nextItem->dictName);
                    free(nextItem);
                }
                else
                {
                    prevItem->next = nextItem->next;
                    free(nextItem->dictName);
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
        numOfDict_P--;
        system("clear");
        printf("Deleting is successful.\nPress ENTER to continue...");
        wait();
        return;
    }
}

void editRecordDict()
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
    if (selectedDict == "place.db" && !headDict_p)
        createDict_P();
    if (selectedDict == "type.db")
    {
        int isMatched = 0;
        unsigned int id;
        char *dictName = NULL;
        size_t len = 0;
        system("clear");
        printf("Enter an ID of item to edit: ");
        scanf("%d", &id);
        clearBuff();
        DICT_T *nextItem, *prevItem = NULL;
        for (nextItem = headDict_t; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
            if (id == nextItem->id)
            {
                isMatched = 1;
                printf("\nEnter a new type: ");
                getline(&dictName, &len, stdin);
                dictName[strcspn(dictName, "\n")] = '\0';
                free(nextItem->dictName);
                nextItem->dictName = dictName;
                break;
            }
        if (!isMatched)
        {
            system("clear");
            printf("The ID %d doesn't exist.\nPress ENTER to continue...", id);
            wait();
            return;
        }
        system("clear");
        printf("Editing is successful.\nPress ENTER to continue...");
        wait();
        return;
    }
    if (selectedDict == "place.db")
    {
        int isMatched = 0;
        unsigned int id;
        char *dictName = NULL;
        size_t len = 0;
        system("clear");
        printf("Enter an ID of item to edit: ");
        scanf("%d", &id);
        clearBuff();
        DICT_P *nextItem, *prevItem = NULL;
        for (nextItem = headDict_p; nextItem != NULL; prevItem = nextItem, nextItem = nextItem->next)
            if (id == nextItem->id)
            {
                isMatched = 1;
                printf("\nEnter a new place: ");
                getline(&dictName, &len, stdin);
                dictName[strcspn(dictName, "\n")] = '\0';
                free(nextItem->dictName);
                nextItem->dictName = dictName;
                break;
            }
        if (!isMatched)
        {
            system("clear");
            printf("The ID %d doesn't exist.\nPress ENTER to continue...", id);
            wait();
            return;
        }
        system("clear");
        printf("Editing is successful.\nPress ENTER to continue...");
        wait();
        return;
    }
}

void saveDict()
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
    if (selectedDict == "place.db" && !headDict_p)
        createDict_P();
    if (selectedDict == "type.db")
    {
        openFDict_T("w");
        DICT_T *nextItem;
        for (nextItem = headDict_t; nextItem != NULL; nextItem = nextItem->next)
            fprintf(fDict_T, "%d;%s;\n", nextItem->id, nextItem->dictName);
        fclose(fDict_T);
        fDict_T = NULL;
        system("clear");
        printf("Saving is successful.\nPress ENTER to continue...");
        wait();
        return;
    }
    if (selectedDict == "place.db")
    {
        openFDict_P("w");
        DICT_P *nextItem;
        for (nextItem = headDict_p; nextItem != NULL; nextItem = nextItem->next)
            fprintf(fDict_P, "%d;%s;\n", nextItem->id, nextItem->dictName);
        fclose(fDict_P);
        fDict_P = NULL;
        system("clear");
        printf("Saving is successful.\nPress ENTER to continue...");
        wait();
        return;
    }
}
