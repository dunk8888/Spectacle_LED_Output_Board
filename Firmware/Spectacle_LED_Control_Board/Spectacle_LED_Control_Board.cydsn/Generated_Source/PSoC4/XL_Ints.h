/*******************************************************************************
* File Name: XL_Ints.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_XL_Ints_H) /* Pins XL_Ints_H */
#define CY_PINS_XL_Ints_H

#include "cytypes.h"
#include "cyfitter.h"
#include "XL_Ints_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} XL_Ints_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   XL_Ints_Read(void);
void    XL_Ints_Write(uint8 value);
uint8   XL_Ints_ReadDataReg(void);
#if defined(XL_Ints__PC) || (CY_PSOC4_4200L) 
    void    XL_Ints_SetDriveMode(uint8 mode);
#endif
void    XL_Ints_SetInterruptMode(uint16 position, uint16 mode);
uint8   XL_Ints_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void XL_Ints_Sleep(void); 
void XL_Ints_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(XL_Ints__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define XL_Ints_DRIVE_MODE_BITS        (3)
    #define XL_Ints_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - XL_Ints_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the XL_Ints_SetDriveMode() function.
         *  @{
         */
        #define XL_Ints_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define XL_Ints_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define XL_Ints_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define XL_Ints_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define XL_Ints_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define XL_Ints_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define XL_Ints_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define XL_Ints_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define XL_Ints_MASK               XL_Ints__MASK
#define XL_Ints_SHIFT              XL_Ints__SHIFT
#define XL_Ints_WIDTH              2u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in XL_Ints_SetInterruptMode() function.
     *  @{
     */
        #define XL_Ints_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define XL_Ints_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define XL_Ints_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define XL_Ints_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(XL_Ints__SIO)
    #define XL_Ints_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(XL_Ints__PC) && (CY_PSOC4_4200L)
    #define XL_Ints_USBIO_ENABLE               ((uint32)0x80000000u)
    #define XL_Ints_USBIO_DISABLE              ((uint32)(~XL_Ints_USBIO_ENABLE))
    #define XL_Ints_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define XL_Ints_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define XL_Ints_USBIO_ENTER_SLEEP          ((uint32)((1u << XL_Ints_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << XL_Ints_USBIO_SUSPEND_DEL_SHIFT)))
    #define XL_Ints_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << XL_Ints_USBIO_SUSPEND_SHIFT)))
    #define XL_Ints_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << XL_Ints_USBIO_SUSPEND_DEL_SHIFT)))
    #define XL_Ints_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(XL_Ints__PC)
    /* Port Configuration */
    #define XL_Ints_PC                 (* (reg32 *) XL_Ints__PC)
#endif
/* Pin State */
#define XL_Ints_PS                     (* (reg32 *) XL_Ints__PS)
/* Data Register */
#define XL_Ints_DR                     (* (reg32 *) XL_Ints__DR)
/* Input Buffer Disable Override */
#define XL_Ints_INP_DIS                (* (reg32 *) XL_Ints__PC2)

/* Interrupt configuration Registers */
#define XL_Ints_INTCFG                 (* (reg32 *) XL_Ints__INTCFG)
#define XL_Ints_INTSTAT                (* (reg32 *) XL_Ints__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define XL_Ints_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(XL_Ints__SIO)
    #define XL_Ints_SIO_REG            (* (reg32 *) XL_Ints__SIO)
#endif /* (XL_Ints__SIO_CFG) */

/* USBIO registers */
#if !defined(XL_Ints__PC) && (CY_PSOC4_4200L)
    #define XL_Ints_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define XL_Ints_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define XL_Ints_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define XL_Ints_DRIVE_MODE_SHIFT       (0x00u)
#define XL_Ints_DRIVE_MODE_MASK        (0x07u << XL_Ints_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins XL_Ints_H */


/* [] END OF FILE */
