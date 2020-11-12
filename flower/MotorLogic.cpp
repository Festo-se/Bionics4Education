/**************************************************************************/
/*!
  @file     motorLogic.cpp

  @mainpage SkySpirit GmbH\n
            MotorLogic for BionicFlower

  @section intro Introduction

  This file describes the definition of the class MotorLogic.

  It is used to control the DRV8834 stepper driving used for the
  Bionic Flower.

  @section author Author

  Kristof Jebens <kristof.jebens@jntec.de>\n
  May 1, 2020 12:36:50 PM\n
  (C) Copyright 2020 by Kristof Jebens <kristof.jebens@jntec.de>  
  
*/
/**************************************************************************/


/*****************************************************************************
 * INCLUDE FILES
 ******************************************************************************/
#include "Settings.h"
#include "MotorLogic.h"


/*****************************************************************************
 * DEFINES
 ******************************************************************************/

int32_t  MotorLogic::m_motor_state_i32;                 //!< state of the motor
Ticker   MotorLogic::m_motor_timer;                     //!< Timer object to control the speed of the motor
int32_t  MotorLogic::m_numberofsteps_i32;               //!< number of requested steps
int32_t  MotorLogic::m_motorposition_i32 = MOTOR_FULL_STEP_COUNT*32;  //!< current motor position
bool     MotorLogic::m_isopening_b = false;             //!< flower is opening flag
bool     MotorLogic::m_isclosing_b = false;             //!< flower is closing flag
bool     MotorLogic::m_isrunning_b = false;             //!< flower is running flag
int32_t  MotorLogic::m_motor_stepping_i32 = 8;          //!< motor stepping factor
uint32_t MotorLogic::m_motorcurrent_ui32 = 0;           //!< motor current setting
bool     MotorLogic::m_iscalibrated_b = false;          //!< motor is calibrated flag
uint32_t MotorLogic::m_desiredposition_ui32 = 0;        //!< desired position
bool     MotorLogic::m_reverse_b = false;               //!< reverse motor Logic flag

MotorLogic::EDirection_t  MotorLogic::m_currentDirection; //!< current direction of the motor
MotorLogic::EState_t      MotorLogic::m_currentState;     //!< current state of the flower
MotorLogic::EStepping_t   MotorLogic::m_currentStepping;  //!< current stepping mode


/* ********************************* METHOD **********************************/
/**
 * \brief     Constructor.
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 12:37:28 PM
 *
 *****************************************************************************/
MotorLogic::MotorLogic()
{
    m_currentState = STATEOPEN;
    m_currentDirection = OPEN;
    m_currentStepping = M32;
    m_reverse_b = false;
    m_motor_stepping_i32 = 32;
    m_motor_state_i32 = 0;
    m_motorposition_i32 = MOTOR_FULL_STEP_COUNT*32;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     setup input output pins for DRV8834
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 10, 2020 2:19:05 PM
 *
 * \return    void
 *
 *****************************************************************************/
void 
MotorLogic::setupPins()
{
    // pin configuration
    pinMode( 33, OUTPUT );  // Direction
    pinMode( 25, OUTPUT );  // Step
    pinMode( 13, OUTPUT );  // NSLP
    pinMode( 17, OUTPUT );  // M0
    pinMode( 18, OUTPUT );  // M1
    pinMode( 19, INPUT );   // NFLT
}

/* ********************************* METHOD **********************************/
/**
 * \brief     reverse the motor
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 10, 2020 2:19:05 PM
 *
 * \return    void
 *
 *****************************************************************************/
void 
MotorLogic::reverse( const bool f_reverse_b )
{
    m_reverse_b = f_reverse_b;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     is the motor calibrated
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 10, 2020 2:19:05 PM
 *
 * \return    void
 *
 *****************************************************************************/
bool 
MotorLogic::isCalibrated( )
{
    return m_iscalibrated_b;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     is the motor opening
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 10, 2020 2:19:05 PM
 *
 * \return    void
 *
 *****************************************************************************/
bool 
MotorLogic::isOpening( )
{
    return m_isopening_b;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     is the motor closing
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 10, 2020 2:19:05 PM
 *
 * \return    void
 *
 *****************************************************************************/
bool 
MotorLogic::isClosing( )
{
    return m_isclosing_b;
}


/* ********************************* METHOD **********************************/
/**
 * \brief     is the motor running
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      Aug 14, 2020 1:19:05 PM
 *
 * \return    void
 *
 *****************************************************************************/
bool 
MotorLogic::isRunning( )
{
    return m_isrunning_b;
}



/* ********************************* METHOD **********************************/
/**
 * \brief     Set direction
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 10, 2020 2:19:05 PM
 *
 * \return    Returns the current position.
 *
 *****************************************************************************/
void
MotorLogic::setDirection( const EDirection_t f_direction_ui32 )
{
    m_currentDirection = f_direction_ui32;
    if (OPEN == f_direction_ui32)
    {
       if (m_reverse_b)
       {
          digitalWrite( 33, LOW );
       }
       else
       {
          digitalWrite( 33, HIGH );
       }
    }
    else
    {
       if (m_reverse_b)
       {
          digitalWrite( 33, HIGH );
       }
       else
       {
          digitalWrite( 33, LOW );
       }
    }
}

/* ********************************* METHOD **********************************/
/**
 * \brief     Set desired position
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 10, 2020 2:19:05 PM
 *
 * \return    void
 *
 *****************************************************************************/
void
MotorLogic::setDesiredPosition( const uint32_t f_position_ui32 )
{
    m_desiredposition_ui32 = f_position_ui32;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     Set number of steps for full movement
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 10, 2020 2:13:28 PM
 *
 *****************************************************************************/
void
MotorLogic::setNSteps( const uint32_t f_steps_ui32 )
{
    m_numberofsteps_i32 = f_steps_ui32;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     set setCurrent Motor Position
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void
MotorLogic::setCurrentPosition( const uint32_t f_position_ui32 )
{
    m_motorposition_i32 = f_position_ui32;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     set Motor Current
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void 
MotorLogic::setMotorCurrent( const uint32_t f_value_ui32 )
{
    m_motorcurrent_ui32 = f_value_ui32;
    dacWrite(DAC2, f_value_ui32);
}

/* ********************************* METHOD **********************************/
/**
 * \brief     set stepping mode of the DRV8834
 *            M0 is connected to IO17
 *            M1 is connected to IO18
 *            setting M0 to floating is not working
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void 
MotorLogic::setSteppingMode( const EStepping_t f_mode )
{
    // DRV8834 stepping:
    // M1 M0 StepMode
    // 0  0  Full step (2-phase excitation)
    // 0  1  1/2 step (1-2 phase excitation)
    // 0  Z  1/4 step (W1-2 phase excitation)
    // 1  0  8 microsteps/step
    // 1  1  16 microsteps/step
    // 1  Z  32 microsteps/step

    switch (f_mode)
    {
        case M1:
          m_motor_stepping_i32 = 32;
          m_currentStepping = M1;
          pinMode( 17, OUTPUT );    // M0
          digitalWrite( 17, LOW );  // M0
          digitalWrite( 18, LOW );  // M1
        break;      
        case M2:
          m_motor_stepping_i32 = 16;
          m_currentStepping = M2;
          pinMode( 17, OUTPUT );    // M0
          digitalWrite( 17, HIGH ); // M0
          digitalWrite( 18, LOW );  // M1
        break;
        case M4: // M0 float not working
          //m_motor_stepping_i32 = 8;
          //m_currentStepping = M4;
          //pinMode( 17, INPUT );     // M0
          //digitalWrite( 17, LOW );  // M0
          //digitalWrite( 18, LOW );  // M1
        break;
        case M8:
          m_motor_stepping_i32 = 4;
          m_currentStepping = M8;
          pinMode( 17, OUTPUT );    // M0
          digitalWrite( 17, LOW );  // M0
          digitalWrite( 18, HIGH ); // M1
        break;
        case M16:
          m_motor_stepping_i32 = 2;
          m_currentStepping = M16;
          pinMode( 17, OUTPUT );    // M0
          digitalWrite( 17, HIGH ); // M0
          digitalWrite( 18, HIGH ); // M1
        break; 
        case M32: // M0 float not working
          //m_motor_stepping_i32 = 1;
          //m_currentStepping = M32;
          //digitalWrite( 17, LOW );  // M0
          //pinMode( 17, INPUT );     // M0
          //digitalWrite( 18, HIGH ); // M1
        break;  
        default:
        break;    
    }
}


/* ********************************* METHOD **********************************/
/**
 * \brief     return the micro stepping factor
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
uint32_t
MotorLogic::getSteppingFactor( )
{
  return m_motor_stepping_i32;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     stop any motor movement
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void 
MotorLogic::stop( )
{
    m_motor_timer.detach();
}

/* ********************************* METHOD **********************************/
/**
 * \brief     get motor position
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
uint32_t
MotorLogic::getMotorPosition() 
{
    return m_motorposition_i32;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     get motor direction
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
MotorLogic::EDirection_t
MotorLogic::getDirection()
{
    return m_currentDirection;
}

/* ********************************* METHOD **********************************/
/**
 * \brief     get current state
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
uint32_t 
MotorLogic::getState() const 
{ 
    return m_currentState; 
};


/* ********************************* METHOD **********************************/
/**
 * \brief     DRV8834 wakeup
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void 
MotorLogic::wakeup()
{
    digitalWrite( 13, HIGH );  // wakeup
}

/* ********************************* METHOD **********************************/
/**
 * \brief     DRV8834 sleep
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void 
MotorLogic::sleep()
{
    digitalWrite( 13, LOW );  // sleep
}

/* ********************************* METHOD **********************************/
/**
 * \brief     let the motor run
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void 
MotorLogic::rotate( const float f_speed_f )
{
    m_motor_timer.detach();
    m_motor_timer.attach(f_speed_f, motorloop); // start the motor timer
}

/* ********************************* METHOD **********************************/
/**
 * \brief     just move forward one step
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void 
MotorLogic::dostep()
{
    m_motor_state_i32++;

    if (OPEN == m_currentDirection)
    {
        m_motorposition_i32 += m_motor_stepping_i32;
        if (m_motorposition_i32 >= MOTOR_FULL_STEP_COUNT*32) 
        {
            m_motorposition_i32 = MOTOR_FULL_STEP_COUNT*32;
            m_currentState = STATEOPEN;
        }        
    }
    if (CLOSE == m_currentDirection)
    {
        //Serial.println(m_motorposition_i32);
        m_motorposition_i32 -= m_motor_stepping_i32;
        if (m_motorposition_i32 <= 0) 
        {
            m_motorposition_i32 = 0;
            m_currentState = STATECLOSED;
        }
    }    
    
    // pin toggle
    if (0 == (m_motor_state_i32%2))
    {
        digitalWrite( 25, LOW );  // Step
    }
    else
    {
        digitalWrite( 25, HIGH ); // Step
    }  
}


/* ********************************* METHOD **********************************/
/**
 * \brief     timer routine to toggle the motor step
 *
 * \author    Kristof Jebens <kristof.jebens@jntec.de>
 * \date      May 1, 2020 2:13:28 PM
 *
 *****************************************************************************/
void 
MotorLogic::motorloop( void )
{
    m_motor_state_i32++;
    m_numberofsteps_i32--;
    m_isrunning_b = true;

    if (OPEN == m_currentDirection)
    {
        m_motorposition_i32 += m_motor_stepping_i32;
        m_isopening_b = true;
        m_currentState = STATEOPENING;
        m_isclosing_b = false;        
        if (m_motorposition_i32 >= (32*MOTOR_FULL_STEP_COUNT)) 
        {
            m_motorposition_i32 = 32*MOTOR_FULL_STEP_COUNT;
            m_currentState = STATEOPEN;
            m_motor_timer.detach();
            m_isrunning_b = false;
        }         
    }
    else
    {
        //Serial.println(m_motorposition_i32);
        if (m_motorposition_i32 > 0)
        {
            m_motorposition_i32 -= m_motor_stepping_i32;
            m_isclosing_b = true;
            m_currentState = STATECLOSING;
            m_isopening_b = false;
        }
        // adjust if stepping is > 1
        if (m_motorposition_i32 <= 0) 
        {
            m_motorposition_i32 = 0;
            m_currentState = STATECLOSED;
            m_motor_timer.detach();
            m_isrunning_b = false;
        }
        // upon first time moving to zero the flower is calibrated
        if (0 == m_motorposition_i32) 
        {
            m_iscalibrated_b = true;
        }
    }
    
    if (0 == m_numberofsteps_i32)
    {
        m_isclosing_b = false;
        m_isopening_b = false;      
        m_motor_timer.detach();
        m_isrunning_b = false;
        setMotorCurrent(0);
        sleep();
    }

    // pin toggle
    if (0 == (m_motor_state_i32%2))
    {
        digitalWrite( 25, LOW );  // Step
    }
    else
    {
        digitalWrite( 25, HIGH ); // Step
    }  
    //m_server.setMotorposition((int32_t) (GUIFACTOR * (float) m_motorposition_i32));
    //g_actual_web_values_a[0] = (int32_t) (GUIFACTOR * (float) m_motorposition_i32);
}


/*****************************************************************************
 * END OF FILE
 ******************************************************************************/
