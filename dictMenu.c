#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "dictMenu.h"

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
            case 3: break;
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
    system("clear");
    printf("File is successfully closed.\nPress ENTER to continue...");
    wait();
}
