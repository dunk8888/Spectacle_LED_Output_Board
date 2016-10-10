/*******************************************************************************
* File Name: tickInt.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_tickInt_H)
#define CY_ISR_tickInt_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void tickInt_Start(void);
void tickInt_StartEx(cyisraddress address);
void tickInt_Stop(void);

CY_ISR_PROTO(tickInt_Interrupt);

void tickInt_SetVector(cyisraddress address);
cyisraddress tickInt_GetVector(void);

void tickInt_SetPriority(uint8 priority);
uint8 tickInt_GetPriority(void);

void tickInt_Enable(void);
uint8 tickInt_GetState(void);
void tickInt_Disable(void);

void tickInt_SetPending(void);
void tickInt_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the tickInt ISR. */
#define tickInt_INTC_VECTOR            ((reg32 *) tickInt__INTC_VECT)

/* Address of the tickInt ISR priority. */
#define tickInt_INTC_PRIOR             ((reg32 *) tickInt__INTC_PRIOR_REG)

/* Priority of the tickInt interrupt. */
#define tickInt_INTC_PRIOR_NUMBER      tickInt__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable tickInt interrupt. */
#define tickInt_INTC_SET_EN            ((reg32 *) tickInt__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the tickInt interrupt. */
#define tickInt_INTC_CLR_EN            ((reg32 *) tickInt__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the tickInt interrupt state to pending. */
#define tickInt_INTC_SET_PD            ((reg32 *) tickInt__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the tickInt interrupt. */
#define tickInt_INTC_CLR_PD            ((reg32 *) tickInt__INTC_CLR_PD_REG)



#endif /* CY_ISR_tickInt_H */


/* [] END OF FILE */
