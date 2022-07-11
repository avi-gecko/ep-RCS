#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "dictMenu.h"

void showDictMenu()
{
    int ans;
    int i;
    const char menuItems[6][100] =
    {
        "1. Выбрать справочник",
        "2. Вывести на экран",
        "3. Редактировать запись в справочнике",
        "4. Добавить запись в справочник",
        "5. Удалить запись",
        "6. Назад"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 6; i++)
            printf("%s\n", menuItems[i]);
        printf("\nВведите пункт меню: ");
        scanf("%d", &ans);
        clearBuff();
        switch(ans)
        {
            case 1: break;
            case 2: break;
            case 3: break;
            case 4: break;
            case 5: break;
            case 6: return;
            default: {
                        system("clear");
                        printf("Такого пункта меню нет, нажмите клавишу ENTER для продолжения.");
                        wait();
                     }
         }
     }
}
