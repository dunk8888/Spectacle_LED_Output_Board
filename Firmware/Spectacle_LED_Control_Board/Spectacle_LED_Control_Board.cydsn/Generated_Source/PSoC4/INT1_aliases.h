/*******************************************************************************
* File Name: INT1.h  
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

#if !defined(CY_PINS_INT1_ALIASES_H) /* Pins INT1_ALIASES_H */
#define CY_PINS_INT1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define INT1_0			(INT1__0__PC)
#define INT1_0_PS		(INT1__0__PS)
#define INT1_0_PC		(INT1__0__PC)
#define INT1_0_DR		(INT1__0__DR)
#define INT1_0_SHIFT	(INT1__0__SHIFT)
#define INT1_0_INTR	((uint16)((uint16)0x0003u << (INT1__0__SHIFT*2u)))

#define INT1_INTR_ALL	 ((uint16)(INT1_0_INTR))
#define INT1_int1			(INT1__int1__PC)
#define INT1_int1_PS		(INT1__int1__PS)
#define INT1_int1_PC		(INT1__int1__PC)
#define INT1_int1_DR		(INT1__int1__DR)
#define INT1_int1_SHIFT	(INT1__int1__SHIFT)
#define INT1_int1_INTR	((uint16)((uint16)0x0003u << (INT1__0__SHIFT*2u)))


#endif /* End Pins INT1_ALIASES_H */


/* [] END OF FILE */
