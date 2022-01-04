#include <stdio.h>
#include <string.h>
#include "ConsoleGame.h"

int main(int argc){
    if(argc>1){
        printf("Error: No arguments!\n");
    }else{
        consoleGameRun();
    }
    return 0;
}