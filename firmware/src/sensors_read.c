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
#include "system_config.h"
#include "sensors_read.h"
#include "adc_read.h"
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
int tempFlags[4];
int ACFlag;

int readTemp(int sensor)
{
    int ADCVal = readAdcChannel(sensor + 3);
    float tempFl = (float)ADCVal;
    tempFl *= nvmData.ADCCoefs[sensor];
    tempFl += (float)nvmData.ADCOffsets[sensor];
    return (int)tempFl;
}

int getTempWarning(int sensor)
{
    int temp = readTemp(sensor);
    
    if(tempFlags[sensor] == 1){
        if((float)temp < (float)nvmData.ADCWarnings[sensor] * 0.9){
            tempFlags[sensor] = 0;
            return 0;
        }
        return 2;
    }
    
    if(temp > nvmData.ADCWarnings[sensor])
    {
        
        tempFlags[sensor] = 1;
        return 1;
    }
    else
    {
        return 0;
    }
        
}

int getSmoke(int sensor)
{
    return getBtn(sensor);
}

int getWater(int sensor)
{
    return getBtn(sensor + 4);
}


int getAC(){
    int ACVal = readAdcChannel(7);
    
    if(ACFlag == 1){
        if((float)ACVal > 140){
            ACFlag = 0;
            return 0;
        }
        return 2;
    }
    
    if(ACVal <= 124){
        ACFlag = 1;
        return 1;
    }
    
    else{
        return 0;
    }
}

int getAlert(){
    int alert = 0;
    int i;
    
    for(i=0; i<4; i++){
        alert = getTempWarning(i);
        if(alert == 1)
            return 1;
    }
    
    for(i=0; i<4; i++)
    {    
        alert = getWater(i);
        if(alert == 1)
            return 1;
    }
    
    for(i=0; i<4; i++){
        alert = getSmoke(i);
        if(alert == 1)
            return 1;
    }
    
    if(getAC() != 0){
        return 1;
    }
    
    return 0;
}

/* *****************************************************************************
 End of File
 */
