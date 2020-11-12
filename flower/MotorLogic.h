/* ********************************* FILE ************************************/
/** \file    Motorlogic.h
 *
 * \brief    This file describes the declaration of the class MotorLogic.
 *
 * \author   Kristof Jebens <kristof.jebens@jntec.de>
 * \date     May 1, 2020 12:34:05 PM
 * \note     (C) Copyright 2020 by Kristof Jebens <kristof.jebens@jntec.de>
 *
 ******************************************************************************/
#ifndef _MOTORLOGIC_H_
#define _MOTORLOGIC_H_


/*****************************************************************************
 * INCLUDE FILES
 ******************************************************************************/

#include "Settings.h"
#include <inttypes.h>
#include <stdlib.h>
#include <FS.h> 
#include "MotorLogic.h"
#include <Ticker.h>



/*****************************************************************************
 * EXPORTED MACROS
 ******************************************************************************/

//#define HISTORY             100  // number of history measurements

/*****************************************************************************
 * CLASSES
 ******************************************************************************/

/* ******************************** CLASS ************************************/
/**
 * \brief  This class represents the logic to drive the motor to different
 *         positions.
 *
 * \author Kristof Jebens <kristof.jebens@jntec.de>
 * \date   May 1, 2020 12:35:11 PM
 * \sa     -
 *
 *****************************************************************************/
class MotorLogic
{
//------------------------------------------------------------------
public:

    /******************************************************
     * constructors, destructor
     ******************************************************/

    // Constructor.
    MotorLogic();


    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ///@name Public types.
    ///@{
    /// State.
    typedef enum
    {
        STATEUNKNOWN = 0,    //< Unknown state
        STATEOPENING,        //< Opening
        STATECLOSING,        //< Closing
        STATEOPEN,           //< Open
        STATECLOSED,         //< Closed
    } EState_t;    

    typedef enum
    {
        OPEN = 0,
        CLOSE,
    } EDirection_t;

    typedef enum
    {
        M32 = 0,
        M16,
        M8,
        M4,
        M2,
        M1,
    } EStepping_t;    
    ///@}    

    /******************************************************
     * methods
     ******************************************************/

    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ///@name Accessors.
    ///@{

    static void setupPins();
    static void reverse( const bool f_reverse_b );
    static bool isCalibrated( );
    static bool isOpening( );
    static bool isClosing( );
    static bool isRunning( );
    static void setDirection( const MotorLogic::EDirection_t f_direction_ui32 );
    static void setDesiredPosition( const uint32_t f_position_ui32 );
    static void setNSteps( const uint32_t f_steps_ui32 );
    static void setCurrentPosition( const uint32_t f_position_ui32 );
    static void setMotorCurrent( const uint32_t f_value_ui32 );
    static void setSteppingMode( const EStepping_t f_mode );
    static uint32_t getSteppingFactor( );
    
    static uint32_t getMotorPosition();
    EDirection_t getDirection();
    uint32_t getState() const;

    static void wakeup();
    static void sleep();
    static void dostep();
    static void rotate( const float f_speed_f );
    static void stop();

    ///@}    
    
    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ///@name Computational methods.
    ///@{

    ///@}


    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ///@name Debug methods.
    ///@{

    ///@}


//------------------------------------------------------------------
protected:

    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ///@name Protected types.
    ///@{

    ///@}


    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ///@name Protected methods.
    ///@{
    
    ///@}


    //- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    ///@name Protected members.
    ///@{
    
    
    ///@}
    
private:

    static void motorloop( void );

    static int32_t  m_motor_state_i32;                  //!< state of the motor
    static Ticker   m_motor_timer;                      //!< Timer object to control the speed of the motor
    static int32_t  m_numberofsteps_i32;                //!< number of requested steps
    static int32_t  m_motorposition_i32;                //!< current motor position
    static bool     m_isopening_b;                      //!< flower is opening flag
    static bool     m_isclosing_b;                      //!< flower is closing flag
    static bool     m_isrunning_b;                      //!< flower is running flag
    static int32_t  m_motor_stepping_i32;               //!< motor stepping factor    
    static uint32_t m_motorcurrent_ui32;                //!< motor current setting
    static bool     m_iscalibrated_b;                   //!< motor is calibrated flag
    static uint32_t m_desiredposition_ui32;             //!< desired position
    static bool     m_reverse_b;                        //!< reverse motor Logic flag

    static MotorLogic::EDirection_t  m_currentDirection;
    static MotorLogic::EState_t  m_currentState;
    static MotorLogic::EStepping_t m_currentStepping;
    
};


#endif /* _MOTORLOGIC_H_ */


/*****************************************************************************
 * END OF FILE
 ******************************************************************************/
