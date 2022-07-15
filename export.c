#include "export.h"
#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include "structs.h"
#include "documentView.h"
#include "fileMenu.h"

void exportToTxt()
{
    if (choosedFile && (!headData && !headDict_t && !headDict_p && !headMain_data))
    {
        createData();
        createDict_T();
        createDict_P();
        createMain_Data();
    }
    else
    if (!choosedFile)
    {
        system("clear");
        printf("Files isn't choosed. It can't be opened.\nPress ENTER to continue...");
        wait();
        return;
    }
    FILE *out;
    if ((out = fopen("./out.txt", "w")) == NULL)
    {
        system("clear");
        printf("File can't be opened.\nPress ENTER to continue...");
        wait();
        return;
    }
    MAIN_DATA *nextItem;
    fprintf(out, "--------------------------------------------------------------------------\n");
    fprintf(out, "|%-6s|%-9s|%-21s|%-15s|%-8s|%8s|\n", "ID", "Item code", "Type", "Place", "Date", "Cost");
    fprintf(out, "--------------------------------------------------------------------------\n");
    for (nextItem = headMain_data; nextItem != NULL; nextItem = nextItem->next)
        fprintf(out, "|%-6d|%-9s|%-21s|%-15s|%-8s|%8d|\n", nextItem->id, nextItem->codeItem, nextItem->type, nextItem->place, nextItem->date, nextItem->cost);
    fprintf(out, "--------------------------------------------------------------------------\n");
    fclose(out);
    system("clear");
    printf("File is successfuly exported to txt.\nPress ENTER to continue...");
    wait();
}