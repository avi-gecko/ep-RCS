#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "fileMenu.h"
#include <dirent.h>
#include <string.h>

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
    int count = 0;
    if ((dir = opendir("./DATA")) != NULL)
    {
        system("clear");
        while ((ent = readdir(dir)) != NULL)
        {
            if ((strcmp(ent->d_name, ".\0")) == 0 || (strcmp(ent->d_name, "..\0")) == 0)
                continue;
            else
                printf("%d. %s\n", ++count, ent->d_name);
        }
        closedir(dir);
        wait();
    }
    else
    {
        system("clear");
        printf("Не удалось открыть директорию.");
        wait();
    }
}
