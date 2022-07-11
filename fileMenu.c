#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "fileMenu.h"
#include <dirent.h>
#include <string.h>
#include "structs.h"
#include <malloc.h>

DIR_ITEM *headDirItems = NULL;
DIR_ITEM *choosedFile = NULL;

void showFileMenu()
{
    int ans;
    int i;
    const char menuItems[4][100] =
    {
        "1. Открыть",
        "2. Сохранить",
        "3. Закрыть",
        "4. Назад"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 4; i++)
            printf("%s\n", menuItems[i]);
        printf("\nВведите пункт меню: ");
        scanf("%d", &ans);
        clearBuff();
        switch(ans)
        {
            case 1: open(); break;
            case 2: break;
            case 3: break;
            case 4: return;
            default: {
                        system("clear");
                        printf("Такого пункта меню нет, нажмите клавишу ENTER для продолжения.");
                        wait();
                     }
         }
     }
}

void open()
{
    DIR *dir = NULL;
    struct dirent *ent = NULL;
    DIR_ITEM *nextItem;
    int count = 0;
    int ans;

    if (!headDirItems)
    {
        if ((dir = opendir("./DATA")) != NULL)
        {
            system("clear");
            while ((ent = readdir(dir)) != NULL)
            {
                if ((strcmp(ent->d_name, ".\0")) == 0 || (strcmp(ent->d_name, "..\0")) == 0)
                    continue;
                else
                {

                    printf("%d. %s\n", ++count, ent->d_name);
                    putItem(ent->d_name, count);
                }
            }
            closedir(dir);
            printf("\nВведите номер файла: ");
            scanf("%d", &ans);
            clearBuff();
            for (nextItem = headDirItems; nextItem != NULL; nextItem = nextItem->next)
                if (ans == nextItem->id)
                {
                    choosedFile = nextItem;
                    printf("\nВыбранный файл: %s\nНажмите клавишу ENTER, чтобы продолжить", choosedFile->dirItemName);
                    break;
                }
            wait();
            return;
        }
        else
        {
            system("clear");
            printf("Не удалось открыть директорию.\nНажмите клавишу ENTER, чтобы продолжить");
            wait();
        }
    }
    else
    {
        system("clear");
        printf("Вы уже выбрали файл %s\nНажмите клавишу ENTER, чтобы продолжить", choosedFile->dirItemName);
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
    newItem->next = nextItem;
    strcpy(newItem->dirItemName, itemName);
    if (!prevItem) headDirItems = newItem;
    else prevItem->next = newItem;
}
