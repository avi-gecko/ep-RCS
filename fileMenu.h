#ifndef FILEMENU_H
#define FILEMENU_H
#include "structs.h"

void showFileMenu();
void selectFile();
void putItem(char *, int);
void close();

extern  DIR_ITEM *headDirItems;
extern  DIR_ITEM *selectedFile;


#endif // FILEMENU_H
