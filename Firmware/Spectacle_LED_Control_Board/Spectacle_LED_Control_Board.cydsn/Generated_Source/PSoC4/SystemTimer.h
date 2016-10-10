/*******************************************************************************
* File Name: SystemTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the SystemTimer
*  component.
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

#if !defined(CY_TCPWM_SystemTimer_H)
#define CY_TCPWM_SystemTimer_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} SystemTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  SystemTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define SystemTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define SystemTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define SystemTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define SystemTimer_QUAD_ENCODING_MODES            (0lu)
#define SystemTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define SystemTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define SystemTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define SystemTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define SystemTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define SystemTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define SystemTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define SystemTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define SystemTimer_TC_RUN_MODE                    (0lu)
#define SystemTimer_TC_COUNTER_MODE                (0lu)
#define SystemTimer_TC_COMP_CAP_MODE               (0lu)
#define SystemTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define SystemTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define SystemTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define SystemTimer_TC_START_SIGNAL_MODE           (0lu)
#define SystemTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define SystemTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define SystemTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define SystemTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define SystemTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define SystemTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define SystemTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SystemTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define SystemTimer_PWM_KILL_EVENT                 (0lu)
#define SystemTimer_PWM_STOP_EVENT                 (0lu)
#define SystemTimer_PWM_MODE                       (4lu)
#define SystemTimer_PWM_OUT_N_INVERT               (0lu)
#define SystemTimer_PWM_OUT_INVERT                 (0lu)
#define SystemTimer_PWM_ALIGN                      (0lu)
#define SystemTimer_PWM_RUN_MODE                   (0lu)
#define SystemTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define SystemTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define SystemTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define SystemTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define SystemTimer_PWM_START_SIGNAL_MODE          (0lu)
#define SystemTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define SystemTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define SystemTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define SystemTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define SystemTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define SystemTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define SystemTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define SystemTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define SystemTimer_TC_PERIOD_VALUE                (10lu)
#define SystemTimer_TC_COMPARE_VALUE               (1lu)
#define SystemTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define SystemTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define SystemTimer_PWM_PERIOD_VALUE               (65535lu)
#define SystemTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define SystemTimer_PWM_PERIOD_SWAP                (0lu)
#define SystemTimer_PWM_COMPARE_VALUE              (65535lu)
#define SystemTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define SystemTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define SystemTimer__LEFT 0
#define SystemTimer__RIGHT 1
#define SystemTimer__CENTER 2
#define SystemTimer__ASYMMETRIC 3

#define SystemTimer__X1 0
#define SystemTimer__X2 1
#define SystemTimer__X4 2

#define SystemTimer__PWM 4
#define SystemTimer__PWM_DT 5
#define SystemTimer__PWM_PR 6

#define SystemTimer__INVERSE 1
#define SystemTimer__DIRECT 0

#define SystemTimer__CAPTURE 2
#define SystemTimer__COMPARE 0

#define SystemTimer__TRIG_LEVEL 3
#define SystemTimer__TRIG_RISING 0
#define SystemTimer__TRIG_FALLING 1
#define SystemTimer__TRIG_BOTH 2

#define SystemTimer__INTR_MASK_TC 1
#define SystemTimer__INTR_MASK_CC_MATCH 2
#define SystemTimer__INTR_MASK_NONE 0
#define SystemTimer__INTR_MASK_TC_CC 3

#define SystemTimer__UNCONFIG 8
#define SystemTimer__TIMER 1
#define SystemTimer__QUAD 3
#define SystemTimer__PWM_SEL 7

#define SystemTimer__COUNT_UP 0
#define SystemTimer__COUNT_DOWN 1
#define SystemTimer__COUNT_UPDOWN0 2
#define SystemTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define SystemTimer_PRESCALE_DIVBY1                ((uint32)(0u << SystemTimer_PRESCALER_SHIFT))
#define SystemTimer_PRESCALE_DIVBY2                ((uint32)(1u << SystemTimer_PRESCALER_SHIFT))
#define SystemTimer_PRESCALE_DIVBY4                ((uint32)(2u << SystemTimer_PRESCALER_SHIFT))
#define SystemTimer_PRESCALE_DIVBY8                ((uint32)(3u << SystemTimer_PRESCALER_SHIFT))
#define SystemTimer_PRESCALE_DIVBY16               ((uint32)(4u << SystemTimer_PRESCALER_SHIFT))
#define SystemTimer_PRESCALE_DIVBY32               ((uint32)(5u << SystemTimer_PRESCALER_SHIFT))
#define SystemTimer_PRESCALE_DIVBY64               ((uint32)(6u << SystemTimer_PRESCALER_SHIFT))
#define SystemTimer_PRESCALE_DIVBY128              ((uint32)(7u << SystemTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define SystemTimer_MODE_TIMER_COMPARE             ((uint32)(SystemTimer__COMPARE         <<  \
                                                                  SystemTimer_MODE_SHIFT))
#define SystemTimer_MODE_TIMER_CAPTURE             ((uint32)(SystemTimer__CAPTURE         <<  \
                                                                  SystemTimer_MODE_SHIFT))
#define SystemTimer_MODE_QUAD                      ((uint32)(SystemTimer__QUAD            <<  \
                                                                  SystemTimer_MODE_SHIFT))
#define SystemTimer_MODE_PWM                       ((uint32)(SystemTimer__PWM             <<  \
                                                                  SystemTimer_MODE_SHIFT))
#define SystemTimer_MODE_PWM_DT                    ((uint32)(SystemTimer__PWM_DT          <<  \
                                                                  SystemTimer_MODE_SHIFT))
#define SystemTimer_MODE_PWM_PR                    ((uint32)(SystemTimer__PWM_PR          <<  \
                                                                  SystemTimer_MODE_SHIFT))

/* Quad Modes */
#define SystemTimer_MODE_X1                        ((uint32)(SystemTimer__X1              <<  \
                                                                  SystemTimer_QUAD_MODE_SHIFT))
#define SystemTimer_MODE_X2                        ((uint32)(SystemTimer__X2              <<  \
                                                                  SystemTimer_QUAD_MODE_SHIFT))
#define SystemTimer_MODE_X4                        ((uint32)(SystemTimer__X4              <<  \
                                                                  SystemTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define SystemTimer_COUNT_UP                       ((uint32)(SystemTimer__COUNT_UP        <<  \
                                                                  SystemTimer_UPDOWN_SHIFT))
#define SystemTimer_COUNT_DOWN                     ((uint32)(SystemTimer__COUNT_DOWN      <<  \
                                                                  SystemTimer_UPDOWN_SHIFT))
#define SystemTimer_COUNT_UPDOWN0                  ((uint32)(SystemTimer__COUNT_UPDOWN0   <<  \
                                                                  SystemTimer_UPDOWN_SHIFT))
#define SystemTimer_COUNT_UPDOWN1                  ((uint32)(SystemTimer__COUNT_UPDOWN1   <<  \
                                                                  SystemTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define SystemTimer_INVERT_LINE                    ((uint32)(SystemTimer__INVERSE         <<  \
                                                                  SystemTimer_INV_OUT_SHIFT))
#define SystemTimer_INVERT_LINE_N                  ((uint32)(SystemTimer__INVERSE         <<  \
                                                                  SystemTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define SystemTimer_TRIG_RISING                    ((uint32)SystemTimer__TRIG_RISING)
#define SystemTimer_TRIG_FALLING                   ((uint32)SystemTimer__TRIG_FALLING)
#define SystemTimer_TRIG_BOTH                      ((uint32)SystemTimer__TRIG_BOTH)
#define SystemTimer_TRIG_LEVEL                     ((uint32)SystemTimer__TRIG_LEVEL)

/* Interrupt mask */
#define SystemTimer_INTR_MASK_TC                   ((uint32)SystemTimer__INTR_MASK_TC)
#define SystemTimer_INTR_MASK_CC_MATCH             ((uint32)SystemTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define SystemTimer_CC_MATCH_SET                   (0x00u)
#define SystemTimer_CC_MATCH_CLEAR                 (0x01u)
#define SystemTimer_CC_MATCH_INVERT                (0x02u)
#define SystemTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define SystemTimer_OVERLOW_SET                    (0x00u)
#define SystemTimer_OVERLOW_CLEAR                  (0x04u)
#define SystemTimer_OVERLOW_INVERT                 (0x08u)
#define SystemTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define SystemTimer_UNDERFLOW_SET                  (0x00u)
#define SystemTimer_UNDERFLOW_CLEAR                (0x10u)
#define SystemTimer_UNDERFLOW_INVERT               (0x20u)
#define SystemTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define SystemTimer_PWM_MODE_LEFT                  (SystemTimer_CC_MATCH_CLEAR        |   \
                                                         SystemTimer_OVERLOW_SET           |   \
                                                         SystemTimer_UNDERFLOW_NO_CHANGE)
#define SystemTimer_PWM_MODE_RIGHT                 (SystemTimer_CC_MATCH_SET          |   \
                                                         SystemTimer_OVERLOW_NO_CHANGE     |   \
                                                         SystemTimer_UNDERFLOW_CLEAR)
#define SystemTimer_PWM_MODE_ASYM                  (SystemTimer_CC_MATCH_INVERT       |   \
                                                         SystemTimer_OVERLOW_SET           |   \
                                                         SystemTimer_UNDERFLOW_CLEAR)

#if (SystemTimer_CY_TCPWM_V2)
    #if(SystemTimer_CY_TCPWM_4000)
        #define SystemTimer_PWM_MODE_CENTER                (SystemTimer_CC_MATCH_INVERT       |   \
                                                                 SystemTimer_OVERLOW_NO_CHANGE     |   \
                                                                 SystemTimer_UNDERFLOW_CLEAR)
    #else
        #define SystemTimer_PWM_MODE_CENTER                (SystemTimer_CC_MATCH_INVERT       |   \
                                                                 SystemTimer_OVERLOW_SET           |   \
                                                                 SystemTimer_UNDERFLOW_CLEAR)
    #endif /* (SystemTimer_CY_TCPWM_4000) */
#else
    #define SystemTimer_PWM_MODE_CENTER                (SystemTimer_CC_MATCH_INVERT       |   \
                                                             SystemTimer_OVERLOW_NO_CHANGE     |   \
                                                             SystemTimer_UNDERFLOW_CLEAR)
#endif /* (SystemTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define SystemTimer_CMD_CAPTURE                    (0u)
#define SystemTimer_CMD_RELOAD                     (8u)
#define SystemTimer_CMD_STOP                       (16u)
#define SystemTimer_CMD_START                      (24u)

/* Status */
#define SystemTimer_STATUS_DOWN                    (1u)
#define SystemTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   SystemTimer_Init(void);
void   SystemTimer_Enable(void);
void   SystemTimer_Start(void);
void   SystemTimer_Stop(void);

void   SystemTimer_SetMode(uint32 mode);
void   SystemTimer_SetCounterMode(uint32 counterMode);
void   SystemTimer_SetPWMMode(uint32 modeMask);
void   SystemTimer_SetQDMode(uint32 qdMode);

void   SystemTimer_SetPrescaler(uint32 prescaler);
void   SystemTimer_TriggerCommand(uint32 mask, uint32 command);
void   SystemTimer_SetOneShot(uint32 oneShotEnable);
uint32 SystemTimer_ReadStatus(void);

void   SystemTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   SystemTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   SystemTimer_SetPWMDeadTime(uint32 deadTime);
void   SystemTimer_SetPWMInvert(uint32 mask);

void   SystemTimer_SetInterruptMode(uint32 interruptMask);
uint32 SystemTimer_GetInterruptSourceMasked(void);
uint32 SystemTimer_GetInterruptSource(void);
void   SystemTimer_ClearInterrupt(uint32 interruptMask);
void   SystemTimer_SetInterrupt(uint32 interruptMask);

void   SystemTimer_WriteCounter(uint32 count);
uint32 SystemTimer_ReadCounter(void);

uint32 SystemTimer_ReadCapture(void);
uint32 SystemTimer_ReadCaptureBuf(void);

void   SystemTimer_WritePeriod(uint32 period);
uint32 SystemTimer_ReadPeriod(void);
void   SystemTimer_WritePeriodBuf(uint32 periodBuf);
uint32 SystemTimer_ReadPeriodBuf(void);

void   SystemTimer_WriteCompare(uint32 compare);
uint32 SystemTimer_ReadCompare(void);
void   SystemTimer_WriteCompareBuf(uint32 compareBuf);
uint32 SystemTimer_ReadCompareBuf(void);

void   SystemTimer_SetPeriodSwap(uint32 swapEnable);
void   SystemTimer_SetCompareSwap(uint32 swapEnable);

void   SystemTimer_SetCaptureMode(uint32 triggerMode);
void   SystemTimer_SetReloadMode(uint32 triggerMode);
void   SystemTimer_SetStartMode(uint32 triggerMode);
void   SystemTimer_SetStopMode(uint32 triggerMode);
void   SystemTimer_SetCountMode(uint32 triggerMode);

void   SystemTimer_SaveConfig(void);
void   SystemTimer_RestoreConfig(void);
void   SystemTimer_Sleep(void);
void   SystemTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define SystemTimer_BLOCK_CONTROL_REG              (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SystemTimer_BLOCK_CONTROL_PTR              ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define SystemTimer_COMMAND_REG                    (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SystemTimer_COMMAND_PTR                    ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define SystemTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SystemTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define SystemTimer_CONTROL_REG                    (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__CTRL )
#define SystemTimer_CONTROL_PTR                    ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__CTRL )
#define SystemTimer_STATUS_REG                     (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__STATUS )
#define SystemTimer_STATUS_PTR                     ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__STATUS )
#define SystemTimer_COUNTER_REG                    (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__COUNTER )
#define SystemTimer_COUNTER_PTR                    ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__COUNTER )
#define SystemTimer_COMP_CAP_REG                   (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__CC )
#define SystemTimer_COMP_CAP_PTR                   ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__CC )
#define SystemTimer_COMP_CAP_BUF_REG               (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define SystemTimer_COMP_CAP_BUF_PTR               ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define SystemTimer_PERIOD_REG                     (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__PERIOD )
#define SystemTimer_PERIOD_PTR                     ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__PERIOD )
#define SystemTimer_PERIOD_BUF_REG                 (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SystemTimer_PERIOD_BUF_PTR                 ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define SystemTimer_TRIG_CONTROL0_REG              (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SystemTimer_TRIG_CONTROL0_PTR              ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define SystemTimer_TRIG_CONTROL1_REG              (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SystemTimer_TRIG_CONTROL1_PTR              ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define SystemTimer_TRIG_CONTROL2_REG              (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SystemTimer_TRIG_CONTROL2_PTR              ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define SystemTimer_INTERRUPT_REQ_REG              (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__INTR )
#define SystemTimer_INTERRUPT_REQ_PTR              ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__INTR )
#define SystemTimer_INTERRUPT_SET_REG              (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define SystemTimer_INTERRUPT_SET_PTR              ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define SystemTimer_INTERRUPT_MASK_REG             (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define SystemTimer_INTERRUPT_MASK_PTR             ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define SystemTimer_INTERRUPT_MASKED_REG           (*(reg32 *) SystemTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define SystemTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) SystemTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define SystemTimer_MASK                           ((uint32)SystemTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define SystemTimer_RELOAD_CC_SHIFT                (0u)
#define SystemTimer_RELOAD_PERIOD_SHIFT            (1u)
#define SystemTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define SystemTimer_PWM_STOP_KILL_SHIFT            (3u)
#define SystemTimer_PRESCALER_SHIFT                (8u)
#define SystemTimer_UPDOWN_SHIFT                   (16u)
#define SystemTimer_ONESHOT_SHIFT                  (18u)
#define SystemTimer_QUAD_MODE_SHIFT                (20u)
#define SystemTimer_INV_OUT_SHIFT                  (20u)
#define SystemTimer_INV_COMPL_OUT_SHIFT            (21u)
#define SystemTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define SystemTimer_RELOAD_CC_MASK                 ((uint32)(SystemTimer_1BIT_MASK        <<  \
                                                                            SystemTimer_RELOAD_CC_SHIFT))
#define SystemTimer_RELOAD_PERIOD_MASK             ((uint32)(SystemTimer_1BIT_MASK        <<  \
                                                                            SystemTimer_RELOAD_PERIOD_SHIFT))
#define SystemTimer_PWM_SYNC_KILL_MASK             ((uint32)(SystemTimer_1BIT_MASK        <<  \
                                                                            SystemTimer_PWM_SYNC_KILL_SHIFT))
#define SystemTimer_PWM_STOP_KILL_MASK             ((uint32)(SystemTimer_1BIT_MASK        <<  \
                                                                            SystemTimer_PWM_STOP_KILL_SHIFT))
#define SystemTimer_PRESCALER_MASK                 ((uint32)(SystemTimer_8BIT_MASK        <<  \
                                                                            SystemTimer_PRESCALER_SHIFT))
#define SystemTimer_UPDOWN_MASK                    ((uint32)(SystemTimer_2BIT_MASK        <<  \
                                                                            SystemTimer_UPDOWN_SHIFT))
#define SystemTimer_ONESHOT_MASK                   ((uint32)(SystemTimer_1BIT_MASK        <<  \
                                                                            SystemTimer_ONESHOT_SHIFT))
#define SystemTimer_QUAD_MODE_MASK                 ((uint32)(SystemTimer_3BIT_MASK        <<  \
                                                                            SystemTimer_QUAD_MODE_SHIFT))
#define SystemTimer_INV_OUT_MASK                   ((uint32)(SystemTimer_2BIT_MASK        <<  \
                                                                            SystemTimer_INV_OUT_SHIFT))
#define SystemTimer_MODE_MASK                      ((uint32)(SystemTimer_3BIT_MASK        <<  \
                                                                            SystemTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define SystemTimer_CAPTURE_SHIFT                  (0u)
#define SystemTimer_COUNT_SHIFT                    (2u)
#define SystemTimer_RELOAD_SHIFT                   (4u)
#define SystemTimer_STOP_SHIFT                     (6u)
#define SystemTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define SystemTimer_CAPTURE_MASK                   ((uint32)(SystemTimer_2BIT_MASK        <<  \
                                                                  SystemTimer_CAPTURE_SHIFT))
#define SystemTimer_COUNT_MASK                     ((uint32)(SystemTimer_2BIT_MASK        <<  \
                                                                  SystemTimer_COUNT_SHIFT))
#define SystemTimer_RELOAD_MASK                    ((uint32)(SystemTimer_2BIT_MASK        <<  \
                                                                  SystemTimer_RELOAD_SHIFT))
#define SystemTimer_STOP_MASK                      ((uint32)(SystemTimer_2BIT_MASK        <<  \
                                                                  SystemTimer_STOP_SHIFT))
#define SystemTimer_START_MASK                     ((uint32)(SystemTimer_2BIT_MASK        <<  \
                                                                  SystemTimer_START_SHIFT))

/* MASK */
#define SystemTimer_1BIT_MASK                      ((uint32)0x01u)
#define SystemTimer_2BIT_MASK                      ((uint32)0x03u)
#define SystemTimer_3BIT_MASK                      ((uint32)0x07u)
#define SystemTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define SystemTimer_8BIT_MASK                      ((uint32)0xFFu)
#define SystemTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define SystemTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define SystemTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(SystemTimer_QUAD_ENCODING_MODES     << SystemTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(SystemTimer_CONFIG                  << SystemTimer_MODE_SHIFT)))

#define SystemTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(SystemTimer_PWM_STOP_EVENT          << SystemTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(SystemTimer_PWM_OUT_INVERT          << SystemTimer_INV_OUT_SHIFT))         |\
         ((uint32)(SystemTimer_PWM_OUT_N_INVERT        << SystemTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(SystemTimer_PWM_MODE                << SystemTimer_MODE_SHIFT)))

#define SystemTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(SystemTimer_PWM_RUN_MODE         << SystemTimer_ONESHOT_SHIFT))
            
#define SystemTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(SystemTimer_PWM_ALIGN            << SystemTimer_UPDOWN_SHIFT))

#define SystemTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(SystemTimer_PWM_KILL_EVENT      << SystemTimer_PWM_SYNC_KILL_SHIFT))

#define SystemTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(SystemTimer_PWM_DEAD_TIME_CYCLE  << SystemTimer_PRESCALER_SHIFT))

#define SystemTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(SystemTimer_PWM_PRESCALER        << SystemTimer_PRESCALER_SHIFT))

#define SystemTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(SystemTimer_TC_PRESCALER            << SystemTimer_PRESCALER_SHIFT))       |\
         ((uint32)(SystemTimer_TC_COUNTER_MODE         << SystemTimer_UPDOWN_SHIFT))          |\
         ((uint32)(SystemTimer_TC_RUN_MODE             << SystemTimer_ONESHOT_SHIFT))         |\
         ((uint32)(SystemTimer_TC_COMP_CAP_MODE        << SystemTimer_MODE_SHIFT)))
        
#define SystemTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(SystemTimer_QUAD_PHIA_SIGNAL_MODE   << SystemTimer_COUNT_SHIFT))           |\
         ((uint32)(SystemTimer_QUAD_INDEX_SIGNAL_MODE  << SystemTimer_RELOAD_SHIFT))          |\
         ((uint32)(SystemTimer_QUAD_STOP_SIGNAL_MODE   << SystemTimer_STOP_SHIFT))            |\
         ((uint32)(SystemTimer_QUAD_PHIB_SIGNAL_MODE   << SystemTimer_START_SHIFT)))

#define SystemTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(SystemTimer_PWM_SWITCH_SIGNAL_MODE  << SystemTimer_CAPTURE_SHIFT))         |\
         ((uint32)(SystemTimer_PWM_COUNT_SIGNAL_MODE   << SystemTimer_COUNT_SHIFT))           |\
         ((uint32)(SystemTimer_PWM_RELOAD_SIGNAL_MODE  << SystemTimer_RELOAD_SHIFT))          |\
         ((uint32)(SystemTimer_PWM_STOP_SIGNAL_MODE    << SystemTimer_STOP_SHIFT))            |\
         ((uint32)(SystemTimer_PWM_START_SIGNAL_MODE   << SystemTimer_START_SHIFT)))

#define SystemTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(SystemTimer_TC_CAPTURE_SIGNAL_MODE  << SystemTimer_CAPTURE_SHIFT))         |\
         ((uint32)(SystemTimer_TC_COUNT_SIGNAL_MODE    << SystemTimer_COUNT_SHIFT))           |\
         ((uint32)(SystemTimer_TC_RELOAD_SIGNAL_MODE   << SystemTimer_RELOAD_SHIFT))          |\
         ((uint32)(SystemTimer_TC_STOP_SIGNAL_MODE     << SystemTimer_STOP_SHIFT))            |\
         ((uint32)(SystemTimer_TC_START_SIGNAL_MODE    << SystemTimer_START_SHIFT)))
        
#define SystemTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((SystemTimer__COUNT_UPDOWN0 == SystemTimer_TC_COUNTER_MODE)                  ||\
                 (SystemTimer__COUNT_UPDOWN1 == SystemTimer_TC_COUNTER_MODE))

#define SystemTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((SystemTimer__CENTER == SystemTimer_PWM_ALIGN)                               ||\
                 (SystemTimer__ASYMMETRIC == SystemTimer_PWM_ALIGN))               
        
#define SystemTimer_PWM_PR_INIT_VALUE              (1u)
#define SystemTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_SystemTimer_H */

/* [] END OF FILE */
