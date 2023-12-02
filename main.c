#include "test.h"
#include <math.h>
#include <stdlib.h>     //exit()
#include <stdio.h>

int main(int argc, char **argv){
    //LCD_1IN28_test();

    //const char *path = "./LCD_1inch28_1.bmp";
    if( argc == 2 ) {
        loadBmp(argv[1]);
    } else {         
        //loadBmp(path);
    }
    while (1){
        getTouch();
    }
    return 0;
}
