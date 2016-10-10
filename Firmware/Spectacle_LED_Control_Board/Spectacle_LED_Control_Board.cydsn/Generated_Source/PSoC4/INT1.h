/*******************************************************************************
* File Name: INT1.h  
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

#if !defined(CY_PINS_INT1_H) /* Pins INT1_H */
#define CY_PINS_INT1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "INT1_aliases.h"


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
} INT1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   INT1_Read(void);
void    INT1_Write(uint8 value);
uint8   INT1_ReadDataReg(void);
#if defined(INT1__PC) || (CY_PSOC4_4200L) 
    void    INT1_SetDriveMode(uint8 mode);
#endif
void    INT1_SetInterruptMode(uint16 position, uint16 mode);
uint8   INT1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void INT1_Sleep(void); 
void INT1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(INT1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define INT1_DRIVE_MODE_BITS        (3)
    #define INT1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - INT1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the INT1_SetDriveMode() function.
         *  @{
         */
        #define INT1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define INT1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define INT1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define INT1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define INT1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define INT1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define INT1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define INT1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define INT1_MASK               INT1__MASK
#define INT1_SHIFT              INT1__SHIFT
#define INT1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in INT1_SetInterruptMode() function.
     *  @{
     */
        #define INT1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define INT1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define INT1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define INT1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(INT1__SIO)
    #define INT1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(INT1__PC) && (CY_PSOC4_4200L)
    #define INT1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define INT1_USBIO_DISABLE              ((uint32)(~INT1_USBIO_ENABLE))
    #define INT1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define INT1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define INT1_USBIO_ENTER_SLEEP          ((uint32)((1u << INT1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << INT1_USBIO_SUSPEND_DEL_SHIFT)))
    #define INT1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << INT1_USBIO_SUSPEND_SHIFT)))
    #define INT1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << INT1_USBIO_SUSPEND_DEL_SHIFT)))
    #define INT1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(INT1__PC)
    /* Port Configuration */
    #define INT1_PC                 (* (reg32 *) INT1__PC)
#endif
/* Pin State */
#define INT1_PS                     (* (reg32 *) INT1__PS)
/* Data Register */
#define INT1_DR                     (* (reg32 *) INT1__DR)
/* Input Buffer Disable Override */
#define INT1_INP_DIS                (* (reg32 *) INT1__PC2)

/* Interrupt configuration Registers */
#define INT1_INTCFG                 (* (reg32 *) INT1__INTCFG)
#define INT1_INTSTAT                (* (reg32 *) INT1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define INT1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(INT1__SIO)
    #define INT1_SIO_REG            (* (reg32 *) INT1__SIO)
#endif /* (INT1__SIO_CFG) */

/* USBIO registers */
#if !defined(INT1__PC) && (CY_PSOC4_4200L)
    #define INT1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define INT1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define INT1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define INT1_DRIVE_MODE_SHIFT       (0x00u)
#define INT1_DRIVE_MODE_MASK        (0x07u << INT1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins INT1_H */


/* [] END OF FILE */
