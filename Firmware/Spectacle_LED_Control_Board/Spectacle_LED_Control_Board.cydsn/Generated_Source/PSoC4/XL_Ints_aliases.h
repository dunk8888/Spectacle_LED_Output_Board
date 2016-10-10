/*******************************************************************************
* File Name: XL_Ints.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_XL_Ints_ALIASES_H) /* Pins XL_Ints_ALIASES_H */
#define CY_PINS_XL_Ints_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define XL_Ints_0			(XL_Ints__0__PC)
#define XL_Ints_0_PS		(XL_Ints__0__PS)
#define XL_Ints_0_PC		(XL_Ints__0__PC)
#define XL_Ints_0_DR		(XL_Ints__0__DR)
#define XL_Ints_0_SHIFT	(XL_Ints__0__SHIFT)
#define XL_Ints_0_INTR	((uint16)((uint16)0x0003u << (XL_Ints__0__SHIFT*2u)))

#define XL_Ints_1			(XL_Ints__1__PC)
#define XL_Ints_1_PS		(XL_Ints__1__PS)
#define XL_Ints_1_PC		(XL_Ints__1__PC)
#define XL_Ints_1_DR		(XL_Ints__1__DR)
#define XL_Ints_1_SHIFT	(XL_Ints__1__SHIFT)
#define XL_Ints_1_INTR	((uint16)((uint16)0x0003u << (XL_Ints__1__SHIFT*2u)))

#define XL_Ints_INTR_ALL	 ((uint16)(XL_Ints_0_INTR| XL_Ints_1_INTR))
#define XL_Ints_int1			(XL_Ints__int1__PC)
#define XL_Ints_int1_PS		(XL_Ints__int1__PS)
#define XL_Ints_int1_PC		(XL_Ints__int1__PC)
#define XL_Ints_int1_DR		(XL_Ints__int1__DR)
#define XL_Ints_int1_SHIFT	(XL_Ints__int1__SHIFT)
#define XL_Ints_int1_INTR	((uint16)((uint16)0x0003u << (XL_Ints__0__SHIFT*2u)))

#define XL_Ints_int2			(XL_Ints__int2__PC)
#define XL_Ints_int2_PS		(XL_Ints__int2__PS)
#define XL_Ints_int2_PC		(XL_Ints__int2__PC)
#define XL_Ints_int2_DR		(XL_Ints__int2__DR)
#define XL_Ints_int2_SHIFT	(XL_Ints__int2__SHIFT)
#define XL_Ints_int2_INTR	((uint16)((uint16)0x0003u << (XL_Ints__1__SHIFT*2u)))


#endif /* End Pins XL_Ints_ALIASES_H */


/* [] END OF FILE */
