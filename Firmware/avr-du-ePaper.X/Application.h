#ifndef APPLICATION_H
#define	APPLICATION_H

#ifdef	__cplusplus
extern "C" {
#endif
    
#define RX_BUFFER_SIZE 32
    
    //Init the Application
    void Application_Initialize(void);
    
    //Add data to the queue
    void Application_AcceptData(char c);
    
    //Handle any received input data
    void Application_HandleUSBInput(void);

#ifdef	__cplusplus
}
#endif

#endif	/* APPLICATION_H */

