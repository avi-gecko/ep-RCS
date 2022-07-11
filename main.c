#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "fileMenu.h"
#include "editMenu.h"
#include "dictMenu.h"
#include "structs.h"
#include "about.h"
#include "documentView.h"

int main()
{
    int ans;
    int i;
    const char menuItems[7][100] =
    {
        "1. Файл",
        "2. Редактировать документ",
        "3. Вывести на экран документ",
        "4. Экспорт документа в файл txt",
        "5. Справочник",
        "6. О программе",
        "7. Выход"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 7; i++)
            printf("%s\n", menuItems[i]);
        if (choosedFile)
            printf("\nВыбранный файл %s", choosedFile->dirItemName);
        printf("\nВведите пункт меню: ");
        scanf("%d", &ans);
        clearBuff();
        switch(ans)
        {
            case 1: showFileMenu(); break;
            case 2: showEditMenu(); break;
            case 3: showDoc(); break;
            case 4: break;
            case 5: showDictMenu(); break;
            case 6: showAbout(); break;
            case 7: exit(0);
            default: {
                        system("clear");
                        printf("Такого пункта меню нет, нажмите клавишу ENTER для продолжения.");
                        wait();
                     }
        }
    }
    return 0;
}
