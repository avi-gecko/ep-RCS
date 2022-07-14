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
        "1. Select directory",
        "2. Display directory",
        "3. Edit a record in a directory",
        "4. Add a record in a directory",
        "5. Delete a record",
        "6. Back"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 6; i++)
            printf("%s\n", menuItems[i]);
        printf("\nEnter a menu item: ");
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
                        printf("There's no such menu item.\nPress ENTER to continue...");
                        wait();
                     }
         }
     }
}
