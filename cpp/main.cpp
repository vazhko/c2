#include <iostream>
#include <vector>
#include <string>
#include "../test.h"
using namespace std;

int main(int argc, char **argv){
    cout << "Hello" << endl;

    char i;

    const char *path1 = "../LCD_1inch28_1.bmp";
    const char *path2 = "../LCD_1inch28_2.bmp";
    const char *path3 = "../LCD_1inch28_3.bmp";
    if( argc == 2 ) {
        loadBmp(argv[1]);
    } else {         
        //loadBmp(path);
    }
    while (1){
        if(getTouch()){
            switch (i){
                case 0:
                    loadBmp(path1);
                    break;
                case 1:
                    loadBmp(path2);
                    break;
                case 2:
                    loadBmp(path3);
                    break;   
                case 3:
                    clearLcd();
                    break;                  
            }
            i++;
            if(i > 3) i = 0;
        }
    }
    return 0;
}