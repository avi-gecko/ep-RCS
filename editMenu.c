#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "editMenu.h"

void showEditMenu()
{
    int ans;
    int i;
    const char menuItems[4][100] =
    {
        "1. Добавить запись",
        "2. Удалить запись",
        "3. Редактировать существующую запись",
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
            case 1: break;
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
