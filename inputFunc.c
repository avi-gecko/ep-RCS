#include <stdio.h>
#include <stdlib.h>
#include "inputFunc.h"
#include <string.h>
#include "documentView.h"
#include "fileMenu.h"

void clearBuff()
{
    while (getchar() != '\n');
}

void wait()
{
    char keyPressed = 0;
    while (scanf("%c", &keyPressed) == 1 && keyPressed != '\n');
}
