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
char* logStrings[20];
char* timeString;
int prevState[12];
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
    int curState[12];
    int alert = -1;
    int i;
    
    for(i=0; i<4; i++){
        curState[i] = getTempWarning(i);
    }
    
    for(i=0; i<4; i++)
    {    
        curState[i+4] = getWater(i);
    }
    
    for(i=0; i<4; i++){
        curState[i+8] = getSmoke(i);
    }
    
    for(i=0; i<12; i++){
        if(curState[i] != 0 && curState[i] != prevState[i])
            alert = i;
    }
    
    for(i=0; i<12; i++){
        prevState[i] = curState[i];
    }
    
    if(gsmFault == 1){
        gsmFault = 0;
        alert = 12;
    }
    
    return alert;
}

void getTimeString(){
    time_t rawTime = TCPIP_SNTP_UTCSecondsGet() + 10800;
    struct tm * timeInfo;

    timeInfo = localtime (&rawTime);
    
    timeString = asctime(timeInfo);;
}

void initLog(){
    int i;
    
    stateChanged();
    for(i=0; i<20; i++){
        logStrings[i] = malloc(1);
        strcpy(logStrings[i], " ");
    }
}

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void getLog(){
    char* eventString;
    char eventChars[50];
    int i;
    getTimeString();
    
    switch(stateChanged())
    {
        case -1:
            return;
        case 0:
            eventString = concat(timeString, " Temperature Sensor 1 Alert\0");
            sendMessage();
            break;
        case 1:
            eventString = concat(timeString, " Temperature Sensor 2 Alert\0");
            sendMessage();
            break;
        case 2:
            eventString = concat(timeString, " Temperature Sensor 3 Alert\0");
            sendMessage();
            break;
        case 3:
            eventString = concat(timeString, " Temperature Sensor 4 Alert\0");
            sendMessage();
            break;
        case 4:
            eventString = concat(timeString, " Water Leak Sensor 1 Alert\0");
            sendMessage();
            break;
        case 5:
            eventString = concat(timeString, " Water Leak Sensor 2 Alert\0");
            sendMessage();
            break;
        case 6:
            eventString = concat(timeString, " Water Leak Sensor 3 Alert\0");
            sendMessage();
            break;
        case 7:
            eventString = concat(timeString, " Water Leak Sensor 4 Alert\0");
            sendMessage();
            break;
        case 8:
            eventString = concat(timeString, " Smoke Sensor 1 Alert\0");
            sendMessage();
            break;
        case 9:
            eventString = concat(timeString, " Smoke Sensor 2 Alert\0");
            sendMessage();
            break;
        case 10:
            eventString = concat(timeString, " Smoke Sensor 3 Alert\0");
            sendMessage();
            break;
        case 11:
            eventString = concat(timeString, " Smoke Sensor 4 Alert\0");
            sendMessage();
            break;
        case 12:
            eventString = concat(timeString, " GSM Module error\0");
            break;
    }
    
    free(logStrings[19]);
      
    for(i = 19; i>0; i--){
        logStrings[i] = logStrings[i-1];
    }
    
    logStrings[0] = eventString;

}


/* *****************************************************************************
 End of File
 */
