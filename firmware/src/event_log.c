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
#include "event_log.h"
#include "inttypes.h"
#include "tcpip/sntp.h"
#include "time.h"
#include "sensors_read.h"
#include "gsm.h"
#include "nvm_storage.h"

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
char timeString[26];
int prevState[13];
static const char default_format[] = "%a %b %d %Y";

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
int stateChanged()
{
    int curState[13];
    int alert = -1;
    int i;
    
    for(i=0; i<4; i++){
        curState[i] = getWater(i);
    }
    
    for(i=0; i<4; i++)
    {    
        curState[i+4] = getSmoke(i);
    }
    
    for(i=0; i<4; i++){
        curState[i+8] = getTempWarning(i);
    }
    
    curState[12] = getAC();   //AC
    
    for(i=0; i<13; i++){
        if(curState[i] != 0 && curState[i] != 2 && curState[i] != prevState[i])
            alert = i;
    }
    
    for(i=0; i<13; i++){
        prevState[i] = curState[i];
    }
    
    if(gsmFault == 1){
        gsmFault = 0;
        alert = 13;
    }
    
    
    return alert;
}

void getTimeString(){
    time_t rawTime = TCPIP_SNTP_UTCSecondsGet() + (nvmData.gmtOffset * 3600);
    struct tm * timeInfo;
    char* bufString = malloc(26);
    int i;

    timeInfo = localtime (&rawTime);
    
    strcpy(bufString, asctime(timeInfo));
    
    for(i=0; i<25; i++){
        timeString[i] = bufString[i];
        if(timeString[i] == '\0')
            break;
    }
    
    timeString[24] = ' ';
    timeString[25] = '\0';
    
    free(bufString);
}

void initLog(){
    int i;
    
    stateChanged();
    for(i=0; i<20; i++){
        if(nvmData.logStrings[i][0] == '\0'){
            strcpy(nvmData.logStrings[i], " "); 
        }
    }
}

void clearLog(){
    int i;
    for(i=0; i<20; i++){
        strcpy(nvmData.logStrings[i], " ");
    }
}

void getLog(){
    char eventString[40];
    int i, j;
    getTimeString();
    
    int event = stateChanged();
    
    if(event == -1){
        return;
    }
    
    for(j = 19; j>0; j--){
        for(i=0; i<40; i++){
            nvmData.logStrings[j][i] = nvmData.logStrings[j-1][i];
        }
    }
    
    strcpy(eventString, timeString);
    
    if(event == 12){
        strcpy(eventString+25, "AC loss\0");
        
    }
    
    else if(event == 13){
        strcpy(eventString+25, "GSM error\0");
    }
    
    else {
    
        strcpy((char *)eventString+25, nvmData.controlsLabels[event]);
        for(i=25; i<32; i++){
            if(eventString[i] == '\0')
                break;
        }
        strcpy((char *)eventString+i, " Alert\0");
    }
    
    for(i=0; i<40; i++){
        nvmData.logStrings[0][i] = eventString[i];
    }
    
    if(event!= 13) {
        sendMessage();
    }

    writeNVM();
}


/* *****************************************************************************
 End of File
 */
