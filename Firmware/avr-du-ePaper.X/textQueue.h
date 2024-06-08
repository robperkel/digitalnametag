#ifndef TEXTQUEUE_H
#define	TEXTQUEUE_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define TX_QUEUE_SIZE 32
    
    //Initialize Text
    void TextQueue_Initialize(void);
    
    //Load Text
    void TextQueue_LoadText(const char* str);
    
    //Load data into the USB report
    void TextQueue_LoadUSB(void);

#ifdef	__cplusplus
}
#endif

#endif	/* TEXTQUEUE_H */

