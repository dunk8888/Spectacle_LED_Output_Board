/*******************************************************************************
* File Name: SystemTimer_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SystemTimer.h"

static SystemTimer_BACKUP_STRUCT SystemTimer_backup;


/*******************************************************************************
* Function Name: SystemTimer_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: SystemTimer_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_Sleep(void)
{
    if(0u != (SystemTimer_BLOCK_CONTROL_REG & SystemTimer_MASK))
    {
        SystemTimer_backup.enableState = 1u;
    }
    else
    {
        SystemTimer_backup.enableState = 0u;
    }

    SystemTimer_Stop();
    SystemTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: SystemTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: SystemTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_Wakeup(void)
{
    SystemTimer_RestoreConfig();

    if(0u != SystemTimer_backup.enableState)
    {
        SystemTimer_Enable();
    }
}


/* [] END OF FILE */
