/*******************************************************************************
* File Name: INT2.h  
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

#if !defined(CY_PINS_INT2_ALIASES_H) /* Pins INT2_ALIASES_H */
#define CY_PINS_INT2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define INT2_0			(INT2__0__PC)
#define INT2_0_PS		(INT2__0__PS)
#define INT2_0_PC		(INT2__0__PC)
#define INT2_0_DR		(INT2__0__DR)
#define INT2_0_SHIFT	(INT2__0__SHIFT)
#define INT2_0_INTR	((uint16)((uint16)0x0003u << (INT2__0__SHIFT*2u)))

#define INT2_INTR_ALL	 ((uint16)(INT2_0_INTR))
#define INT2_int1			(INT2__int1__PC)
#define INT2_int1_PS		(INT2__int1__PS)
#define INT2_int1_PC		(INT2__int1__PC)
#define INT2_int1_DR		(INT2__int1__DR)
#define INT2_int1_SHIFT	(INT2__int1__SHIFT)
#define INT2_int1_INTR	((uint16)((uint16)0x0003u << (INT2__0__SHIFT*2u)))


#endif /* End Pins INT2_ALIASES_H */


/* [] END OF FILE */
