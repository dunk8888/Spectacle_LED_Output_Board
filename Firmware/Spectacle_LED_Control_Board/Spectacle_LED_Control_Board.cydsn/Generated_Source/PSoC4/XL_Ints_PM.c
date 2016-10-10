/*******************************************************************************
* File Name: XL_Ints.c  
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
#include "XL_Ints.h"

static XL_Ints_BACKUP_STRUCT  XL_Ints_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: XL_Ints_Sleep
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
*  \snippet XL_Ints_SUT.c usage_XL_Ints_Sleep_Wakeup
*******************************************************************************/
void XL_Ints_Sleep(void)
{
    #if defined(XL_Ints__PC)
        XL_Ints_backup.pcState = XL_Ints_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            XL_Ints_backup.usbState = XL_Ints_CR1_REG;
            XL_Ints_USB_POWER_REG |= XL_Ints_USBIO_ENTER_SLEEP;
            XL_Ints_CR1_REG &= XL_Ints_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(XL_Ints__SIO)
        XL_Ints_backup.sioState = XL_Ints_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        XL_Ints_SIO_REG &= (uint32)(~XL_Ints_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: XL_Ints_Wakeup
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
*  Refer to XL_Ints_Sleep() for an example usage.
*******************************************************************************/
void XL_Ints_Wakeup(void)
{
    #if defined(XL_Ints__PC)
        XL_Ints_PC = XL_Ints_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            XL_Ints_USB_POWER_REG &= XL_Ints_USBIO_EXIT_SLEEP_PH1;
            XL_Ints_CR1_REG = XL_Ints_backup.usbState;
            XL_Ints_USB_POWER_REG &= XL_Ints_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(XL_Ints__SIO)
        XL_Ints_SIO_REG = XL_Ints_backup.sioState;
    #endif
}


/* [] END OF FILE */
