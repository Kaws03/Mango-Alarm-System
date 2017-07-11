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

#include <proc/p32mx795f512l.h>
#include "board_io.h"

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
int global_data;


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



void initIO()
{
    //Switches
    TRISGbits.TRISG12 = 1;
    TRISDbits.TRISD7 = 1;
    TRISDbits.TRISD6 = 1;
    TRISDbits.TRISD5 = 1;
    TRISDbits.TRISD4 = 1;
    TRISDbits.TRISD3 = 1;
    TRISDbits.TRISD1 = 1;
    TRISDbits.TRISD2 = 1;
    
    //LEDs
    TRISBbits.TRISB0 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB4 = 0;
    TRISGbits.TRISG13 = 0;
    TRISGbits.TRISG14 = 0;
    TRISDbits.TRISD12 = 0;
}

void setLed(int ledNum, int state)
{
    switch(ledNum)
    {
        case 0:
            LATBbits.LATB0 = state;
            break;
        case 1:
            LATBbits.LATB1 = state;
            break;
        case 2:
            LATBbits.LATB2 = state;
            break;
        case 3:
            LATBbits.LATB3 = state;
            break;
        case 4:
            LATBbits.LATB4 = state;
            break;
        case 5:
            LATGbits.LATG13 = state;
            break;
        case 6:
            LATGbits.LATG14 = state;
            break;
        case 7:
            LATDbits.LATD12 = state;
            break;
    }
           
}

int getLed(int ledNum)
{
    switch(ledNum)
    {
        case 0:
            return LATBbits.LATB0;
        case 1:
            return LATBbits.LATB1;
        case 2:
            return LATBbits.LATB2;
        case 3:
            return LATBbits.LATB3;
        case 4:
            return LATBbits.LATB4;
        case 5:
            return LATGbits.LATG13;
        case 6:
            return LATGbits.LATG14;
        case 7:
            return LATDbits.LATD12;
    }
           
}

int getBtn(int btnNum)
{
    switch(btnNum)
    {
        case 0:
            return PORTGbits.RG12;
        case 1:
            return PORTDbits.RD7;
        case 2:
            return PORTDbits.RD6;
        case 3:
            return PORTDbits.RD5;
        case 4:
            return PORTDbits.RD4;
        case 5:
            return PORTDbits.RD3;
        case 6:
            return PORTDbits.RD1;
        case 7:
            return PORTDbits.RD2;
    }
}


/* *****************************************************************************
 End of File
 */
