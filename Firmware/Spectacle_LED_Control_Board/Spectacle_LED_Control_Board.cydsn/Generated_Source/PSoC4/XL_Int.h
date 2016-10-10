/*******************************************************************************
* File Name: XL_Int.h
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
#if !defined(CY_ISR_XL_Int_H)
#define CY_ISR_XL_Int_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void XL_Int_Start(void);
void XL_Int_StartEx(cyisraddress address);
void XL_Int_Stop(void);

CY_ISR_PROTO(XL_Int_Interrupt);

void XL_Int_SetVector(cyisraddress address);
cyisraddress XL_Int_GetVector(void);

void XL_Int_SetPriority(uint8 priority);
uint8 XL_Int_GetPriority(void);

void XL_Int_Enable(void);
uint8 XL_Int_GetState(void);
void XL_Int_Disable(void);

void XL_Int_SetPending(void);
void XL_Int_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the XL_Int ISR. */
#define XL_Int_INTC_VECTOR            ((reg32 *) XL_Int__INTC_VECT)

/* Address of the XL_Int ISR priority. */
#define XL_Int_INTC_PRIOR             ((reg32 *) XL_Int__INTC_PRIOR_REG)

/* Priority of the XL_Int interrupt. */
#define XL_Int_INTC_PRIOR_NUMBER      XL_Int__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable XL_Int interrupt. */
#define XL_Int_INTC_SET_EN            ((reg32 *) XL_Int__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the XL_Int interrupt. */
#define XL_Int_INTC_CLR_EN            ((reg32 *) XL_Int__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the XL_Int interrupt state to pending. */
#define XL_Int_INTC_SET_PD            ((reg32 *) XL_Int__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the XL_Int interrupt. */
#define XL_Int_INTC_CLR_PD            ((reg32 *) XL_Int__INTC_CLR_PD_REG)



#endif /* CY_ISR_XL_Int_H */


/* [] END OF FILE */
