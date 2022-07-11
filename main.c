#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"

int main()
{
    int ans;
    int i;
    char menuItems[7][100] =
    {
        "Файл",
        "Редактировать документ",
        "Вывести на экран документ",
        "Экспорт документа в файл txt",
        "Справочник",
        "О программе",
        "Выход"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 7; i++)
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
            case 6: break;
            case 7: break;
            default: {
                        system("clear");
                        printf("Такого пункта меню нет, нажмите клавишу для продолжения.");
                        wait();
                     }
        }
    }
    return 0;
}
