/*******************************************************************************
* File Name: SystemTimer.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the SystemTimer
*  component
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

uint8 SystemTimer_initVar = 0u;


/*******************************************************************************
* Function Name: SystemTimer_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default SystemTimer configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (SystemTimer__QUAD == SystemTimer_CONFIG)
        SystemTimer_CONTROL_REG = SystemTimer_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SystemTimer_TRIG_CONTROL1_REG  = SystemTimer_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        SystemTimer_SetInterruptMode(SystemTimer_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        SystemTimer_SetCounterMode(SystemTimer_COUNT_DOWN);
        SystemTimer_WritePeriod(SystemTimer_QUAD_PERIOD_INIT_VALUE);
        SystemTimer_WriteCounter(SystemTimer_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (SystemTimer__QUAD == SystemTimer_CONFIG) */

    #if (SystemTimer__TIMER == SystemTimer_CONFIG)
        SystemTimer_CONTROL_REG = SystemTimer_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        SystemTimer_TRIG_CONTROL1_REG  = SystemTimer_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SystemTimer_SetInterruptMode(SystemTimer_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        SystemTimer_WritePeriod(SystemTimer_TC_PERIOD_VALUE );

        #if (SystemTimer__COMPARE == SystemTimer_TC_COMP_CAP_MODE)
            SystemTimer_WriteCompare(SystemTimer_TC_COMPARE_VALUE);

            #if (1u == SystemTimer_TC_COMPARE_SWAP)
                SystemTimer_SetCompareSwap(1u);
                SystemTimer_WriteCompareBuf(SystemTimer_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == SystemTimer_TC_COMPARE_SWAP) */
        #endif  /* (SystemTimer__COMPARE == SystemTimer_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (SystemTimer_CY_TCPWM_V2 && SystemTimer_TIMER_UPDOWN_CNT_USED && !SystemTimer_CY_TCPWM_4000)
            SystemTimer_WriteCounter(1u);
        #elif(SystemTimer__COUNT_DOWN == SystemTimer_TC_COUNTER_MODE)
            SystemTimer_WriteCounter(SystemTimer_TC_PERIOD_VALUE);
        #else
            SystemTimer_WriteCounter(0u);
        #endif /* (SystemTimer_CY_TCPWM_V2 && SystemTimer_TIMER_UPDOWN_CNT_USED && !SystemTimer_CY_TCPWM_4000) */
    #endif  /* (SystemTimer__TIMER == SystemTimer_CONFIG) */

    #if (SystemTimer__PWM_SEL == SystemTimer_CONFIG)
        SystemTimer_CONTROL_REG = SystemTimer_CTRL_PWM_BASE_CONFIG;

        #if (SystemTimer__PWM_PR == SystemTimer_PWM_MODE)
            SystemTimer_CONTROL_REG |= SystemTimer_CTRL_PWM_RUN_MODE;
            SystemTimer_WriteCounter(SystemTimer_PWM_PR_INIT_VALUE);
        #else
            SystemTimer_CONTROL_REG |= SystemTimer_CTRL_PWM_ALIGN | SystemTimer_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (SystemTimer_CY_TCPWM_V2 && SystemTimer_PWM_UPDOWN_CNT_USED && !SystemTimer_CY_TCPWM_4000)
                SystemTimer_WriteCounter(1u);
            #elif (SystemTimer__RIGHT == SystemTimer_PWM_ALIGN)
                SystemTimer_WriteCounter(SystemTimer_PWM_PERIOD_VALUE);
            #else 
                SystemTimer_WriteCounter(0u);
            #endif  /* (SystemTimer_CY_TCPWM_V2 && SystemTimer_PWM_UPDOWN_CNT_USED && !SystemTimer_CY_TCPWM_4000) */
        #endif  /* (SystemTimer__PWM_PR == SystemTimer_PWM_MODE) */

        #if (SystemTimer__PWM_DT == SystemTimer_PWM_MODE)
            SystemTimer_CONTROL_REG |= SystemTimer_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (SystemTimer__PWM_DT == SystemTimer_PWM_MODE) */

        #if (SystemTimer__PWM == SystemTimer_PWM_MODE)
            SystemTimer_CONTROL_REG |= SystemTimer_CTRL_PWM_PRESCALER;
        #endif  /* (SystemTimer__PWM == SystemTimer_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        SystemTimer_TRIG_CONTROL1_REG  = SystemTimer_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        SystemTimer_SetInterruptMode(SystemTimer_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (SystemTimer__PWM_PR == SystemTimer_PWM_MODE)
            SystemTimer_TRIG_CONTROL2_REG =
                    (SystemTimer_CC_MATCH_NO_CHANGE    |
                    SystemTimer_OVERLOW_NO_CHANGE      |
                    SystemTimer_UNDERFLOW_NO_CHANGE);
        #else
            #if (SystemTimer__LEFT == SystemTimer_PWM_ALIGN)
                SystemTimer_TRIG_CONTROL2_REG = SystemTimer_PWM_MODE_LEFT;
            #endif  /* ( SystemTimer_PWM_LEFT == SystemTimer_PWM_ALIGN) */

            #if (SystemTimer__RIGHT == SystemTimer_PWM_ALIGN)
                SystemTimer_TRIG_CONTROL2_REG = SystemTimer_PWM_MODE_RIGHT;
            #endif  /* ( SystemTimer_PWM_RIGHT == SystemTimer_PWM_ALIGN) */

            #if (SystemTimer__CENTER == SystemTimer_PWM_ALIGN)
                SystemTimer_TRIG_CONTROL2_REG = SystemTimer_PWM_MODE_CENTER;
            #endif  /* ( SystemTimer_PWM_CENTER == SystemTimer_PWM_ALIGN) */

            #if (SystemTimer__ASYMMETRIC == SystemTimer_PWM_ALIGN)
                SystemTimer_TRIG_CONTROL2_REG = SystemTimer_PWM_MODE_ASYM;
            #endif  /* (SystemTimer__ASYMMETRIC == SystemTimer_PWM_ALIGN) */
        #endif  /* (SystemTimer__PWM_PR == SystemTimer_PWM_MODE) */

        /* Set other values from customizer */
        SystemTimer_WritePeriod(SystemTimer_PWM_PERIOD_VALUE );
        SystemTimer_WriteCompare(SystemTimer_PWM_COMPARE_VALUE);

        #if (1u == SystemTimer_PWM_COMPARE_SWAP)
            SystemTimer_SetCompareSwap(1u);
            SystemTimer_WriteCompareBuf(SystemTimer_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == SystemTimer_PWM_COMPARE_SWAP) */

        #if (1u == SystemTimer_PWM_PERIOD_SWAP)
            SystemTimer_SetPeriodSwap(1u);
            SystemTimer_WritePeriodBuf(SystemTimer_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == SystemTimer_PWM_PERIOD_SWAP) */
    #endif  /* (SystemTimer__PWM_SEL == SystemTimer_CONFIG) */
    
}


/*******************************************************************************
* Function Name: SystemTimer_Enable
********************************************************************************
*
* Summary:
*  Enables the SystemTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    SystemTimer_BLOCK_CONTROL_REG |= SystemTimer_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (SystemTimer__PWM_SEL == SystemTimer_CONFIG)
        #if (0u == SystemTimer_PWM_START_SIGNAL_PRESENT)
            SystemTimer_TriggerCommand(SystemTimer_MASK, SystemTimer_CMD_START);
        #endif /* (0u == SystemTimer_PWM_START_SIGNAL_PRESENT) */
    #endif /* (SystemTimer__PWM_SEL == SystemTimer_CONFIG) */

    #if (SystemTimer__TIMER == SystemTimer_CONFIG)
        #if (0u == SystemTimer_TC_START_SIGNAL_PRESENT)
            SystemTimer_TriggerCommand(SystemTimer_MASK, SystemTimer_CMD_START);
        #endif /* (0u == SystemTimer_TC_START_SIGNAL_PRESENT) */
    #endif /* (SystemTimer__TIMER == SystemTimer_CONFIG) */
    
    #if (SystemTimer__QUAD == SystemTimer_CONFIG)
        #if (0u != SystemTimer_QUAD_AUTO_START)
            SystemTimer_TriggerCommand(SystemTimer_MASK, SystemTimer_CMD_RELOAD);
        #endif /* (0u != SystemTimer_QUAD_AUTO_START) */
    #endif  /* (SystemTimer__QUAD == SystemTimer_CONFIG) */
}


/*******************************************************************************
* Function Name: SystemTimer_Start
********************************************************************************
*
* Summary:
*  Initializes the SystemTimer with default customizer
*  values when called the first time and enables the SystemTimer.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  SystemTimer_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time SystemTimer_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the SystemTimer_Start() routine.
*
*******************************************************************************/
void SystemTimer_Start(void)
{
    if (0u == SystemTimer_initVar)
    {
        SystemTimer_Init();
        SystemTimer_initVar = 1u;
    }

    SystemTimer_Enable();
}


/*******************************************************************************
* Function Name: SystemTimer_Stop
********************************************************************************
*
* Summary:
*  Disables the SystemTimer.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_BLOCK_CONTROL_REG &= (uint32)~SystemTimer_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the SystemTimer. This function is used when
*  configured as a generic SystemTimer and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the SystemTimer to operate in
*   Values:
*   - SystemTimer_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - SystemTimer_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - SystemTimer_MODE_QUAD - Quadrature decoder
*         - SystemTimer_MODE_PWM - PWM
*         - SystemTimer_MODE_PWM_DT - PWM with dead time
*         - SystemTimer_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_MODE_MASK;
    SystemTimer_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - SystemTimer_MODE_X1 - Counts on phi 1 rising
*         - SystemTimer_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - SystemTimer_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_QUAD_MODE_MASK;
    SystemTimer_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - SystemTimer_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - SystemTimer_PRESCALE_DIVBY2    - Divide by 2
*         - SystemTimer_PRESCALE_DIVBY4    - Divide by 4
*         - SystemTimer_PRESCALE_DIVBY8    - Divide by 8
*         - SystemTimer_PRESCALE_DIVBY16   - Divide by 16
*         - SystemTimer_PRESCALE_DIVBY32   - Divide by 32
*         - SystemTimer_PRESCALE_DIVBY64   - Divide by 64
*         - SystemTimer_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_PRESCALER_MASK;
    SystemTimer_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the SystemTimer runs
*  continuously or stops when terminal count is reached.  By default the
*  SystemTimer operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_ONESHOT_MASK;
    SystemTimer_CONTROL_REG |= ((uint32)((oneShotEnable & SystemTimer_1BIT_MASK) <<
                                                               SystemTimer_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetPWMMode(uint32 modeMask)
{
    SystemTimer_TRIG_CONTROL2_REG = (modeMask & SystemTimer_6BIT_MASK);
}



/*******************************************************************************
* Function Name: SystemTimer_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_PWM_SYNC_KILL_MASK;
    SystemTimer_CONTROL_REG |= ((uint32)((syncKillEnable & SystemTimer_1BIT_MASK)  <<
                                               SystemTimer_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_PWM_STOP_KILL_MASK;
    SystemTimer_CONTROL_REG |= ((uint32)((stopOnKillEnable & SystemTimer_1BIT_MASK)  <<
                                                         SystemTimer_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_PRESCALER_MASK;
    SystemTimer_CONTROL_REG |= ((uint32)((deadTime & SystemTimer_8BIT_MASK) <<
                                                          SystemTimer_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - SystemTimer_INVERT_LINE   - Inverts the line output
*         - SystemTimer_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_INV_OUT_MASK;
    SystemTimer_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: SystemTimer_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_WriteCounter(uint32 count)
{
    SystemTimer_COUNTER_REG = (count & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 SystemTimer_ReadCounter(void)
{
    return (SystemTimer_COUNTER_REG & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - SystemTimer_COUNT_UP       - Counts up
*     - SystemTimer_COUNT_DOWN     - Counts down
*     - SystemTimer_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - SystemTimer_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_UPDOWN_MASK;
    SystemTimer_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_WritePeriod(uint32 period)
{
    SystemTimer_PERIOD_REG = (period & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 SystemTimer_ReadPeriod(void)
{
    return (SystemTimer_PERIOD_REG & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_RELOAD_CC_MASK;
    SystemTimer_CONTROL_REG |= (swapEnable & SystemTimer_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_WritePeriodBuf(uint32 periodBuf)
{
    SystemTimer_PERIOD_BUF_REG = (periodBuf & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 SystemTimer_ReadPeriodBuf(void)
{
    return (SystemTimer_PERIOD_BUF_REG & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_CONTROL_REG &= (uint32)~SystemTimer_RELOAD_PERIOD_MASK;
    SystemTimer_CONTROL_REG |= ((uint32)((swapEnable & SystemTimer_1BIT_MASK) <<
                                                            SystemTimer_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void SystemTimer_WriteCompare(uint32 compare)
{
    #if (SystemTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SystemTimer_CY_TCPWM_4000) */

    #if (SystemTimer_CY_TCPWM_4000)
        currentMode = ((SystemTimer_CONTROL_REG & SystemTimer_UPDOWN_MASK) >> SystemTimer_UPDOWN_SHIFT);

        if (((uint32)SystemTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)SystemTimer__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (SystemTimer_CY_TCPWM_4000) */
    
    SystemTimer_COMP_CAP_REG = (compare & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 SystemTimer_ReadCompare(void)
{
    #if (SystemTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SystemTimer_CY_TCPWM_4000) */

    #if (SystemTimer_CY_TCPWM_4000)
        currentMode = ((SystemTimer_CONTROL_REG & SystemTimer_UPDOWN_MASK) >> SystemTimer_UPDOWN_SHIFT);
        
        regVal = SystemTimer_COMP_CAP_REG;
        
        if (((uint32)SystemTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SystemTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SystemTimer_16BIT_MASK);
    #else
        return (SystemTimer_COMP_CAP_REG & SystemTimer_16BIT_MASK);
    #endif /* (SystemTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SystemTimer_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void SystemTimer_WriteCompareBuf(uint32 compareBuf)
{
    #if (SystemTimer_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (SystemTimer_CY_TCPWM_4000) */

    #if (SystemTimer_CY_TCPWM_4000)
        currentMode = ((SystemTimer_CONTROL_REG & SystemTimer_UPDOWN_MASK) >> SystemTimer_UPDOWN_SHIFT);

        if (((uint32)SystemTimer__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)SystemTimer__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (SystemTimer_CY_TCPWM_4000) */
    
    SystemTimer_COMP_CAP_BUF_REG = (compareBuf & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 SystemTimer_ReadCompareBuf(void)
{
    #if (SystemTimer_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (SystemTimer_CY_TCPWM_4000) */

    #if (SystemTimer_CY_TCPWM_4000)
        currentMode = ((SystemTimer_CONTROL_REG & SystemTimer_UPDOWN_MASK) >> SystemTimer_UPDOWN_SHIFT);

        regVal = SystemTimer_COMP_CAP_BUF_REG;
        
        if (((uint32)SystemTimer__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)SystemTimer__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & SystemTimer_16BIT_MASK);
    #else
        return (SystemTimer_COMP_CAP_BUF_REG & SystemTimer_16BIT_MASK);
    #endif /* (SystemTimer_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: SystemTimer_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 SystemTimer_ReadCapture(void)
{
    return (SystemTimer_COMP_CAP_REG & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 SystemTimer_ReadCaptureBuf(void)
{
    return (SystemTimer_COMP_CAP_BUF_REG & SystemTimer_16BIT_MASK);
}


/*******************************************************************************
* Function Name: SystemTimer_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SystemTimer_TRIG_LEVEL     - Level
*     - SystemTimer_TRIG_RISING    - Rising edge
*     - SystemTimer_TRIG_FALLING   - Falling edge
*     - SystemTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_TRIG_CONTROL1_REG &= (uint32)~SystemTimer_CAPTURE_MASK;
    SystemTimer_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SystemTimer_TRIG_LEVEL     - Level
*     - SystemTimer_TRIG_RISING    - Rising edge
*     - SystemTimer_TRIG_FALLING   - Falling edge
*     - SystemTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_TRIG_CONTROL1_REG &= (uint32)~SystemTimer_RELOAD_MASK;
    SystemTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SystemTimer_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SystemTimer_TRIG_LEVEL     - Level
*     - SystemTimer_TRIG_RISING    - Rising edge
*     - SystemTimer_TRIG_FALLING   - Falling edge
*     - SystemTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_TRIG_CONTROL1_REG &= (uint32)~SystemTimer_START_MASK;
    SystemTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SystemTimer_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SystemTimer_TRIG_LEVEL     - Level
*     - SystemTimer_TRIG_RISING    - Rising edge
*     - SystemTimer_TRIG_FALLING   - Falling edge
*     - SystemTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_TRIG_CONTROL1_REG &= (uint32)~SystemTimer_STOP_MASK;
    SystemTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SystemTimer_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - SystemTimer_TRIG_LEVEL     - Level
*     - SystemTimer_TRIG_RISING    - Rising edge
*     - SystemTimer_TRIG_FALLING   - Falling edge
*     - SystemTimer_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_TRIG_CONTROL1_REG &= (uint32)~SystemTimer_COUNT_MASK;
    SystemTimer_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << SystemTimer_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - SystemTimer_CMD_CAPTURE    - Trigger Capture/Switch command
*     - SystemTimer_CMD_RELOAD     - Trigger Reload/Index command
*     - SystemTimer_CMD_STOP       - Trigger Stop/Kill command
*     - SystemTimer_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    SystemTimer_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: SystemTimer_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the SystemTimer.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - SystemTimer_STATUS_DOWN    - Set if counting down
*     - SystemTimer_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 SystemTimer_ReadStatus(void)
{
    return ((SystemTimer_STATUS_REG >> SystemTimer_RUNNING_STATUS_SHIFT) |
            (SystemTimer_STATUS_REG & SystemTimer_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: SystemTimer_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - SystemTimer_INTR_MASK_TC       - Terminal count mask
*     - SystemTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetInterruptMode(uint32 interruptMask)
{
    SystemTimer_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: SystemTimer_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - SystemTimer_INTR_MASK_TC       - Terminal count mask
*     - SystemTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SystemTimer_GetInterruptSourceMasked(void)
{
    return (SystemTimer_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: SystemTimer_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - SystemTimer_INTR_MASK_TC       - Terminal count mask
*     - SystemTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 SystemTimer_GetInterruptSource(void)
{
    return (SystemTimer_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: SystemTimer_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - SystemTimer_INTR_MASK_TC       - Terminal count mask
*     - SystemTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_ClearInterrupt(uint32 interruptMask)
{
    SystemTimer_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: SystemTimer_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - SystemTimer_INTR_MASK_TC       - Terminal count mask
*     - SystemTimer_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void SystemTimer_SetInterrupt(uint32 interruptMask)
{
    SystemTimer_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
