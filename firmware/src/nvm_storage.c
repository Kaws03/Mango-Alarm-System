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
#include "tcpip/tcpip.h"
#include "tcpip/tcpip_manager.h"
#include "tcpip/src/tcpip_manager_control.h"
#include "system_config.h"
#include "driver/nvm/drv_nvm.h"
#include <stdlib.h>
#include <stdint.h>

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

int networkInitDone;

DRV_HANDLE nvmHandle;
DRV_NVM_COMMAND_HANDLE nvmCommandHandle[8];

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

void checkNVM(){
    if(nvmData.nvmEmpty != 534){
        setDefaults();
    }
    
    nvmData.nvmEmpty = 534;
}

int factoryReset(){
    if(PORTAbits.RA5 == 0){
        setDefaults();
        return 1;
    }
    
    return 0;
}


void writeNVM(){
    uint8_t nvmWriteBuffer [DRV_NVM_PAGE_SIZE * 3];
    
    memcpy(nvmWriteBuffer, &nvmData, sizeof(nvmData));
            
    DRV_NVM_EraseWrite(nvmHandle, &nvmCommandHandle[1], nvmWriteBuffer, 256, 12);            
}

void nvmRead(){
    nvmHandle = DRV_NVM_Open(0, DRV_IO_INTENT_READWRITE);
    
    uint8_t nvmReadBuffer [DRV_NVM_PAGE_SIZE * 3] __attribute__((aligned(16)));
    
    if(factoryReset()){
        return;
    }
    
    DRV_NVM_Read(nvmHandle, &nvmCommandHandle[0], nvmReadBuffer, (256*512), 6144);
    memcpy(&nvmData, nvmReadBuffer, sizeof(nvmData));
    
    checkNVM();
}

void setDefaults(){
    int i;
    
    strcpy(nvmData.controlsLabels[0], "Water 1\0");
    strcpy(nvmData.controlsLabels[1], "Water 2\0");
    strcpy(nvmData.controlsLabels[2], "Water 3\0");
    strcpy(nvmData.controlsLabels[3], "Water 4\0");
    strcpy(nvmData.controlsLabels[4], "Smoke 1\0");
    strcpy(nvmData.controlsLabels[5], "Smoke 2\0");
    strcpy(nvmData.controlsLabels[6], "Smoke 3\0");
    strcpy(nvmData.controlsLabels[7], "Smoke 4\0");
    strcpy(nvmData.controlsLabels[8], "Temp 1\0");
    strcpy(nvmData.controlsLabels[9], "Temp 2\0");
    strcpy(nvmData.controlsLabels[10], "Temp 3\0");
    strcpy(nvmData.controlsLabels[11], "Temp 4\0");
    
    nvmData.ADCCoefs[0] = 0.1;
    nvmData.ADCCoefs[1] = 0.1;
    nvmData.ADCCoefs[2] = 0.1;
    nvmData.ADCCoefs[3] = 0.1;
    
    nvmData.ADCOffsets[0] = 30;
    nvmData.ADCOffsets[1] = 30;
    nvmData.ADCOffsets[2] = 30;
    nvmData.ADCOffsets[3] = 30;
    
    nvmData.ADCWarnings[0] = 35;
    nvmData.ADCWarnings[1] = 35;
    nvmData.ADCWarnings[2] = 35;
    nvmData.ADCWarnings[3] = 35;
    
    nvmData.outs[0] = 1;
    nvmData.outs[1] = 1;
    nvmData.outs[2] = 1;
    
    strcpy(nvmData.login, "admin\0");
    strcpy(nvmData.password, "mpimsp\0");
    
    strcpy(nvmData.smsNumbers[0], "\0");
    strcpy(nvmData.smsNumbers[1], "\0");
    strcpy(nvmData.smsNumbers[2], "\0");
    
    nvmData.gmtOffset = 3;
    
    char ipStrings[5][20];
    
    strcpy(ipStrings[0], "192.168.1.224");
    strcpy(ipStrings[2], "255.255.255.0");
    strcpy(ipStrings[1], "192.168.1.1");
    strcpy(ipStrings[3], "192.168.1.1");
    strcpy(ipStrings[4], "0.0.0.0");
    nvmData.DHCP = 0;
    
    for(i=0; i<5; i++){
        TCPIP_Helper_StringToIPAddress(ipStrings[i], &nvmData.IPs[i]);  
    }
}

void setNetwork(){
    TCPIP_NET_HANDLE netH = TCPIP_STACK_IndexToNet(0);
    
    if(networkInitDone == 1 || nvmData.DHCP){
        networkInitDone = 1;
        return;
    }
    
    if(!TCPIP_STACK_NetIsReady(netH)){
        return;
    }

    TCPIP_STACK_NetAddressSet(netH, &nvmData.IPs[0], &nvmData.IPs[2], true);
    TCPIP_STACK_NetAddressGatewaySet(netH, &nvmData.IPs[1]);
    TCPIP_STACK_NetAddressDnsPrimarySet(netH, &nvmData.IPs[3]);
    TCPIP_STACK_NetAddressDnsSecondSet(netH, &nvmData.IPs[4]);
    
    networkInitDone = 1;
}

/* *****************************************************************************
 End of File
 */
