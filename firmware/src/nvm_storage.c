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
#include "nvm_storage.h"
#include <stdlib.h>
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

char controlsLabels[12][8];
float ADCCoefs[4];
int ADCOffsets[4];
int ADCWarnings[4];
    
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

void nvmRead(){
    strcpy(controlsLabels[0], "Water 1\0");
    strcpy(controlsLabels[1], "Water 2\0");
    strcpy(controlsLabels[2], "Water 3\0");
    strcpy(controlsLabels[3], "Water 4\0");
    strcpy(controlsLabels[4], "Smoke 1\0");
    strcpy(controlsLabels[5], "Smoke 2\0");
    strcpy(controlsLabels[6], "Smoke 3\0");
    strcpy(controlsLabels[7], "Smoke 4\0");
    strcpy(controlsLabels[8], "Temp 1\0");
    strcpy(controlsLabels[9], "Temp 2\0");
    strcpy(controlsLabels[10], "Temp 3\0");
    strcpy(controlsLabels[11], "Temp 4\0");
    
    ADCCoefs[0] = 0.1;
    ADCCoefs[1] = 0.1;
    ADCCoefs[2] = 0.1;
    ADCCoefs[3] = 0.1;
    
    ADCOffsets[0] = 30;
    ADCOffsets[1] = 30;
    ADCOffsets[2] = 30;
    ADCOffsets[3] = 30;
    
    ADCWarnings[0] = 35;
    ADCWarnings[1] = 35;
    ADCWarnings[2] = 35;
    ADCWarnings[3] = 35;
}

/* *****************************************************************************
 End of File
 */
