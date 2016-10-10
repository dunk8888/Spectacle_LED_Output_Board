/*******************************************************************************
* File Name: INT1.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "INT1.h"

static INT1_BACKUP_STRUCT  INT1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: INT1_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function must be called for SIO and USBIO
*  pins. It is not essential if using GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet INT1_SUT.c usage_INT1_Sleep_Wakeup
*******************************************************************************/
void INT1_Sleep(void)
{
    #if defined(INT1__PC)
        INT1_backup.pcState = INT1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            INT1_backup.usbState = INT1_CR1_REG;
            INT1_USB_POWER_REG |= INT1_USBIO_ENTER_SLEEP;
            INT1_CR1_REG &= INT1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(INT1__SIO)
        INT1_backup.sioState = INT1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        INT1_SIO_REG &= (uint32)(~INT1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: INT1_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep().
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to INT1_Sleep() for an example usage.
*******************************************************************************/
void INT1_Wakeup(void)
{
    #if defined(INT1__PC)
        INT1_PC = INT1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            INT1_USB_POWER_REG &= INT1_USBIO_EXIT_SLEEP_PH1;
            INT1_CR1_REG = INT1_backup.usbState;
            INT1_USB_POWER_REG &= INT1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(INT1__SIO)
        INT1_SIO_REG = INT1_backup.sioState;
    #endif
}


/* [] END OF FILE */
