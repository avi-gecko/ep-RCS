#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "fileMenu.h"
#include "editMenu.h"
#include "dictMenu.h"
#include "structs.h"
#include "about.h"
#include "documentView.h"
#include "export.h"

int main()
{
    int ans;
    int i;
    const char menuItems[7][100] =
    {
        "1. File",
        "2. Edit the document",
        "3. Display the document",
        "4. Export the document to the txt file",
        "5. Directory",
        "6. About the program",
        "7. Exit"
    };

    while(1)
    {
        system("clear");
        for (i = 0; i < 7; i++)
            printf("%s\n", menuItems[i]);
        if (selectedFile)
            printf("\nSelected file: %s", selectedFile->dirItemName);
        if (selectedDict)
            printf("\nSelected directory: %s" , selectedDict);
        printf("\nEnter a menu item: ");
        scanf("%d", &ans);
        clearBuff();
        switch(ans)
        {
            case 1: showFileMenu(); break;
            case 2: showEditMenu(); break;
            case 3: showDoc(); break;
            case 4: exportToTxt(); break;
            case 5: showDictMenu(); break;
            case 6: showAbout(); break;
            case 7: exit(0);
            default: {
                        system("clear");
                        printf("There's no such menu item.\nPress ENTER to continue...");
                        wait();
                     }
        }
    }
    return 0;
}
