#include "DEV_Config.h"
#include "LCD_1in28.h"
#include "Touch_1in28.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "test.h"
#include "image.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()
#include <wiringPi.h>



UBYTE flag = 0,flgh = 0;
UWORD *BlackImage,x,y,l;


static UBYTE isInit = 0;

void Touch_INT_callback(void) {
    flag = TOUCH_IRQ;
}

char init(){
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1IN28_LCD);    
    
	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        //exit(0);
        return 1;
    }

    LCD_1IN28_Init(HORIZONTAL);
	LCD_1IN28_Clear(BLACK);
	LCD_SetBacklight(1023);  

    wiringPiISR(TP_INT, INT_EDGE_FALLING, &Touch_INT_callback);

    return 0;
}

char getTouch(){
    if(isInit == 0){
        //char res = 
        init();
        //if(res) return res;
        isInit = 1;
    }
    if (flag == TOUCH_IRQ){
        printf("Touch_INT_callback\r\n");
        flag = 0;
        DEV_Delay_ms(1);
        return 1;
    }
    return 0;
}


char loadBmp(const char *path){
    if(isInit == 0){
        char res = init();
        if(res) return res;
        isInit = 1;
    }

    //LCD_1IN28_Init(HORIZONTAL);
	LCD_1IN28_Clear(BLACK);
	//LCD_SetBacklight(1023);

    UDOUBLE Imagesize = LCD_1IN28_HEIGHT*LCD_1IN28_WIDTH*2;
    printf("Imagesize = %d\r\n", Imagesize);
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
       return 2;
    }
    
    Paint_NewImage(BlackImage, LCD_1IN28_WIDTH, LCD_1IN28_HEIGHT, 0, BLACK, 16);
    Paint_Clear(WHITE);
	Paint_SetRotate(ROTATE_0); 

    printf("Show %s\r\n", path);
    Paint_SelectImage(BlackImage);
    //if (0 == GUI_ReadBmp(path)) return 3;
    GUI_ReadBmp(path);

    LCD_1IN28_Display((UWORD *)BlackImage);
    DEV_Delay_ms(1);

    free(BlackImage);
    BlackImage = NULL;

    return 0;
}

void clearLcd(){
	LCD_1IN28_Clear(BLACK);        
}




