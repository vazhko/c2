#ifndef _TRST_H_
#define _TRST_H_

#ifdef __cplusplus
    extern "C"  void Touch_INT_callback(void);
    extern "C"  char loadBmp(const char *path);
    extern "C"  char getTouch();
    extern "C"  void clearLcd();
#else
    void Touch_INT_callback(void);
    char loadBmp(const char *path);
    char getTouch();
    void clearLcd();

#endif
#endif