#include <stdio.h>
#include "inputFunc.h"

void clearBuff()
{
    while (getchar() != '\n');
}

void wait()
{
    char keyPressed = 0;
    while (scanf("%c", &keyPressed) == 1 && keyPressed != '\n');
}
