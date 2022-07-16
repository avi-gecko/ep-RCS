#ifndef FILEMENU_H
#define FILEMENU_H
#include "structs.h"

extern  DIR_ITEM *headDirItems;
extern  DIR_ITEM *selectedFile;

void showFileMenu();
void selectFile();
void putItem(char *, int);
void close();
void save();

#endif // FILEMENU_H
