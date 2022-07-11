#ifndef FILEMENU_H
#define FILEMENU_H
#include "structs.h"

void showFileMenu();
void open();
void putItem(char *, int);
extern  DIR_ITEM *headDirItems;
extern  DIR_ITEM *choosedFile;


#endif // FILEMENU_H
