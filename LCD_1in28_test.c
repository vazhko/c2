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



UBYTE flag = 0,flgh = 0;
UWORD *BlackImage,x,y,l;
PI_THREAD (myThread)
{
    while(1)
    {
        l++;
        if(l>30)
            l=25;
        DEV_Delay_ms(1);
    }
    
    return NULL;
}

void LCD_1IN28_test(void){

    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1IN28_LCD);


    if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }

    printf("1.28inch LCD demo...\r\n");
    LCD_1IN28_Init(HORIZONTAL);
    LCD_1IN28_Clear(BLACK);
    LCD_SetBacklight(1023);

    UDOUBLE Imagesize = LCD_1IN28_HEIGHT*LCD_1IN28_WIDTH*2;
    printf("Imagesize = %d\r\n", Imagesize);
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }

    Paint_NewImage(BlackImage, LCD_1IN28_WIDTH, LCD_1IN28_HEIGHT, 0, BLACK, 16);
    Paint_Clear(WHITE);
    Paint_SetRotate(ROTATE_0);

    // Touch_Gesture();


    printf("show window BMP-----------------\r\n");
    Paint_SelectImage(BlackImage);
    const char *path = "./LCD_1inch28_1.bmp";
    GUI_ReadBmp(path);

    //Touch_HandWriting();
    LCD_1IN28_Display((UWORD *)BlackImage);

    DEV_Delay_ms(20000);
    // Module Exit
    free(BlackImage);
    BlackImage = NULL;
    DEV_ModuleExit();

}

/*
void Touch_HandWriting(){

    XY.mode = 1;
    XY.color = BLACK;
    flgh = TOUCH_INIT; //Initializes the flag bit   
    flag = TOUCH_INIT;

    Touch_1IN28_init(XY.mode);

    piThreadCreate(myThread);

    DEV_Delay_ms(10);
    Paint_Clear(WHITE);

    Paint_DrawRectangle(0, 0, 35, 208,RED,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawRectangle(0, 0, 208, 35,GREEN,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawRectangle(206, 0, 240, 240,BLUE,DOT_PIXEL_1X1,DRAW_FILL_FULL);
    Paint_DrawRectangle(0, 206, 240, 240,GRAY,DOT_PIXEL_1X1,DRAW_FILL_FULL); 
    LCD_1IN28_Display(BlackImage);

    while(1)
    {
        if(flgh == TOUCH_INIT && XY.x_point != TOUCH_INIT)
        {
                flgh = true; 
                //Get the coordinates of the first point    
                x = XY.x_point;
                y = XY.y_point;
        }   
        
        if (flag == TOUCH_IRQ)
        {
            XY = Touch_1IN28_Get_Point();
            if ((XY.x_point > 35 && XY.x_point < 205) && (XY.y_point > 35 && XY.y_point < 208))
            {
                flgh = TOUCH_DRAW;//Permit painting     
            }
            else
            {
                if ((XY.x_point > 0 && XY.x_point < 33) && (XY.y_point > 0 && XY.y_point < 208))
                    {
                        XY.color = RED;
                    }
                if ((XY.x_point > 0 && XY.x_point < 208) && (XY.y_point > 0 && XY.y_point < 33))
                    {
                        XY.color = GREEN;
                    }
                if ((XY.x_point > 208 && XY.x_point < 240) && (XY.y_point > 0 && XY.y_point < 240))
                    {
                        XY.color = BLUE;
                    }
                if ((XY.x_point > 0 && XY.x_point < 240) && (XY.y_point > 208 && XY.y_point < 240))
                    {
                        Paint_ClearWindow(35,35,205,208,WHITE);
                        Paint_DrawRectangle(0, 206, 240, 240,GRAY,DOT_PIXEL_1X1,DRAW_FILL_FULL); 
                        LCD_1IN28_DisplayWindows(35,35,205,208,BlackImage);
                    }
                flgh = TOUCH_NO_DRAW; //No painting     
                flag = TOUCH_DRAW;
            }
            

            if (flgh == TOUCH_DRAW)
            {
                XY.x_point = (XY.x_point > 37)? XY.x_point : 37;
                XY.y_point = (XY.y_point > 37)? XY.y_point : 37;

                XY.x_point = (XY.x_point < 205)? XY.x_point : 205;
                XY.y_point = (XY.y_point < 203)? XY.y_point : 203;    
                
                if (l<16) //Continuous drawing  
                {
                    flag = TOUCH_DRAW;
                    flgh = TOUCH_NO_DRAW;
                    Paint_DrawLine(x,y,XY.x_point, XY.y_point, XY.color, DOT_PIXEL_2X2, LINE_STYLE_SOLID);
                    LCD_1IN28_DisplayWindows(x,y,XY.x_point, XY.y_point,BlackImage);
                    l = 0;
                }
                else//POINT     
                {
                    flag = TOUCH_DRAW; 
                    flgh = TOUCH_NO_DRAW;
                    Paint_DrawPoint(XY.x_point, XY.y_point, XY.color, DOT_PIXEL_2X2, DOT_FILL_AROUND);
                    LCD_1IN28_DisplayWindows(x,y,XY.x_point, XY.y_point,BlackImage);
                    l = 0;
                }
                x = XY.x_point;
                y = XY.y_point;
            }
        }
    }
}
*/
/*
void Touch_Gesture(){
    XY.mode = 0;

    if(Touch_1IN28_init(XY.mode) == true)
        printf("Success:Detected CST816T.\r\n");
    else
        printf("Error: Not Detected CST816T.\r\n");
    wiringPiISR(TP_INT,INT_EDGE_FALLING,&Touch_INT_callback);
    Paint_Clear(WHITE);
    Paint_DrawString_EN(35, 90, "Gesture test", &Font20, BLACK, WHITE);
    Paint_DrawString_EN(10, 120, "Complete as prompted", &Font16, BLACK, WHITE);
    LCD_1IN28_Display(BlackImage);
    Paint_Clear(WHITE);
    DEV_Delay_ms(1500);
    Paint_DrawImage(gImage_up, 45, 30, 150, 150);
    LCD_1IN28_Display(BlackImage);
    while(XY.Gesture != UP)
    {
        Paint_DrawString_EN(105, 190, "Up", &Font24, 0X647C, WHITE);
        LCD_1IN28_DisplayWindows(105,190,145,215,BlackImage);
        DEV_Delay_ms(500);
        Paint_ClearWindow(105,190,145,215,WHITE);
        LCD_1IN28_DisplayWindows(105,190,145,215,BlackImage);
        DEV_Delay_ms(500);
    }
    Paint_DrawImage(gImage_down, 45, 30, 150, 150);
    LCD_1IN28_Display(BlackImage);
    while(XY.Gesture != Down)
    {
        Paint_DrawString_EN(85, 190, "Down", &Font24, 0X647C, WHITE);
        LCD_1IN28_DisplayWindows(85,190,155,215,BlackImage);
        DEV_Delay_ms(500);
        Paint_ClearWindow(85,190,155,215,WHITE);
        LCD_1IN28_DisplayWindows(85,190,155,215,BlackImage);
        DEV_Delay_ms(500);
    }
    Paint_DrawImage(gImage_left, 45, 30, 150, 150);
    LCD_1IN28_Display(BlackImage);
    while(XY.Gesture != LEFT)
    {
        Paint_DrawString_EN(85, 190, "Left", &Font24, 0X647C, WHITE);
        LCD_1IN28_DisplayWindows(85,190,155,215,BlackImage);
        DEV_Delay_ms(500);
        Paint_ClearWindow(85,190,155,215,WHITE);
        LCD_1IN28_DisplayWindows(85,190,155,215,BlackImage);
        DEV_Delay_ms(500);
    } 
    Paint_DrawImage(gImage_right, 45, 30, 150, 150);
    LCD_1IN28_Display(BlackImage);
    while(XY.Gesture != RIGHT)
    {
        Paint_DrawString_EN(80, 190, "Right", &Font24, 0X647C, WHITE);
        LCD_1IN28_DisplayWindows(80,190,160,215,BlackImage);
        DEV_Delay_ms(500);
        Paint_ClearWindow(80,190,170,215,WHITE);
        LCD_1IN28_DisplayWindows(80,190,170,215,BlackImage);
        DEV_Delay_ms(500);
    }
    Paint_DrawImage(gImage_long_press, 45, 30, 150, 150);
    LCD_1IN28_Display(BlackImage);
    while(XY.Gesture != LONG_PRESS)
    {
        Paint_DrawString_EN(47, 190, "Long Press", &Font20, 0X647C, WHITE);
        LCD_1IN28_DisplayWindows(47,190,180,215,BlackImage);
        DEV_Delay_ms(500);
        Paint_ClearWindow(47,190,200,215,WHITE);
        LCD_1IN28_DisplayWindows(47,190,200,215,BlackImage);
        DEV_Delay_ms(500);
    }
    Paint_DrawImage(gImage_double_click, 45, 30, 150, 150);
    LCD_1IN28_Display(BlackImage);
    while(XY.Gesture != DOUBLE_CLICK)
    {
        Paint_DrawString_EN(35, 185, "Double Click", &Font20, 0X647C, WHITE);
        LCD_1IN28_DisplayWindows(35,185,210,215,BlackImage);
        DEV_Delay_ms(500);
        Paint_ClearWindow(35,185,210,215,WHITE);
        LCD_1IN28_DisplayWindows(35,185,210,215,BlackImage);
        DEV_Delay_ms(500);
    }

    flag = TOUCH_OUT_GESTURE; //Exit gesture mode 
}
*/

void Touch_INT_callback(void) {
    flag = TOUCH_IRQ;
    //if (XY.mode == 0)
    //    XY.Gesture = I2C_Read_Byte(0x01);
    //printf("Touch_INT_callback");
}

char getTouch(){
    if (flag == TOUCH_IRQ){
        printf("Touch_INT_callback\r\n");
        flag = 0;
        DEV_Delay_ms(500);
        return 1;
    }
    return 0;
}

static UBYTE isInit = 0;


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

    UDOUBLE Imagesize = LCD_1IN28_HEIGHT*LCD_1IN28_WIDTH*2;
    printf("Imagesize = %d\r\n", Imagesize);
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
       return 2;
    }
    
    Paint_NewImage(BlackImage, LCD_1IN28_WIDTH, LCD_1IN28_HEIGHT, 0, BLACK, 16);
    Paint_Clear(WHITE);
	Paint_SetRotate(ROTATE_0); 

    wiringPiISR(TP_INT,INT_EDGE_FALLING,&Touch_INT_callback);
    piThreadCreate(myThread);

    return 0;
}



char loadBmp(const char *path){
    if(isInit == 0){
        char res = init();
        if(res) return res;
        isInit = 1;
    }

    printf("show BMP %s\r\n", path);
    Paint_SelectImage(BlackImage);
    printf("Paint_SelectImage(BlackImage)\r\n");
    //path = "./pic/LCD_1inch28_1.bmp";
    printf("GUI_ReadBmp(path)\r\n");
    //if (0 == GUI_ReadBmp(path)) return 3;
    GUI_ReadBmp(path);
    printf("LCD_1IN28_Display((UWORD *)BlackImage)\r\n");
    LCD_1IN28_Display((UWORD *)BlackImage);
    DEV_Delay_ms(20);

    return 0;
}




