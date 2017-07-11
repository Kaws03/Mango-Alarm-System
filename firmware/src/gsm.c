/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */
#include "gsm.h"
#include "driver/usart/drv_usart.h"
#include "event_log.h"
#include "power_control.h"
#include "driver/tmr/drv_tmr.h"

/* TODO:  Include other files here if needed. */


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks
 */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.
    
    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }
 */



/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */

char rxBytes[150];
int rxPtr;
int rxDone;
int txAttempts = 0;
int gsmFault = 0;

int callDd = -1;

int serviceState = 0;

uint32_t timeOutVal = 1250000;

void timerStart(){
    PLIB_TMR_Stop(TMR_ID_2);
    PLIB_TMR_Counter32BitClear(TMR_ID_2);
    PLIB_TMR_Start(TMR_ID_2);
}



int timeOut(){
    if(PLIB_TMR_Counter32BitGet(TMR_ID_2) >= timeOutVal){
        PLIB_TMR_Stop(TMR_ID_2);
        return 1;
    }
    return 0;
}

void clearRx()
{
    int i;
    for(i=0; i<50; i++){
        rxBytes[i] = '\0';
    }
}

bool getString()
{
    int i;
    if(PLIB_USART_ReceiverDataIsAvailable(USART_ID_2) != 0){
        while(PLIB_USART_ReceiverDataIsAvailable(USART_ID_2) != 0){
            if(rxPtr == 0){
                clearRx();
            }
            rxBytes[rxPtr] = PLIB_USART_ReceiverByteReceive(USART_ID_2);
            
            if(rxBytes[rxPtr] == '\n'){
                rxPtr = 0;
                rxDone = 1;
            }
            else{
                rxPtr++;
            }  
        }
    }
}

void initGSM()
{   
    __XC_UART = 2;
    DRV_USART0_Initialize();
    
    PLIB_TMR_Stop(TMR_ID_2);
    PLIB_TMR_ClockSourceSelect(TMR_ID_2, TMR_CLOCK_SOURCE_PERIPHERAL_CLOCK);
    PLIB_TMR_PrescaleSelect(TMR_ID_2, TMR_PRESCALE_VALUE_256);
    PLIB_TMR_Mode32BitEnable(TMR_ID_2);
    PLIB_TMR_Counter32BitClear(TMR_ID_2);
    PLIB_TMR_Period32BitSet(TMR_ID_1, 0xFFFFFFFF);
    PLIB_TMR_Stop(TMR_ID_2);
}
void sendMessage()
{
    if(getAlarm() == 0 || serviceState != 0){
        return;
    }
    serviceState = 1;
    txAttempts = 0;
}
void call()
{

}

void txRetry(){
    serviceState = 1;
    txAttempts ++;
    clearRx();
}

void txFaultLog(){
    gsmFault = 1;
}

void gsmService(){
    getString();
    switch(serviceState){
        case 0:
            return;
        case 1:
            if(txAttempts >= 5){
                serviceState = 0;
                txFaultLog();
                return;
            }
            printf("AT\r\n");
            timerStart();
            serviceState++;
            return;
        case 2:
            if(timeOut() == 1){
                txRetry();
            }
            else{
               if(rxBytes[0] == 'O' && rxBytes[1] == 'K'){
                   serviceState++;
               } 
            }
            return;
        case 3:
            printf("AT+CMGS=\"80979298777\"\n");
            timerStart();
            serviceState++;
        case 4:
            if(timeOut() == 1){
                txRetry();
            }
            else{
               if(rxBytes[0] == '>' || rxBytes[1] == '>'){
                   serviceState++;
               } 
            }
            return;
        case 5:
            printf(logStrings[0]);
            printf("\032\n");
            timerStart();
            serviceState++;
        case 6:
            if(timeOut() == 1){
                txRetry();
            }
            else{
               if(rxBytes[0] == 'O' && rxBytes[1] == 'K'){
                   serviceState = 0;
                   clearRx();
               } 
            }
            return;
    }   
}



/* *****************************************************************************
 End of File
 */
