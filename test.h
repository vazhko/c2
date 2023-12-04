#ifndef _TRST_H_
#define _TRST_H_

#ifdef __cplusplus    
    extern "C"  char loadBmp(const char *path);
    extern "C"  char getTouch();
    extern "C"  void clearLcd();
#else    
    char loadBmp(const char *path);
    char getTouch();
    void clearLcd();
#endif
#endif