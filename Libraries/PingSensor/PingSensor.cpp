#include <pins_arduino.h>
#include <Arduino.h>
#include "PingSensor.h"

int _trigPinId = 0;
int _echoPinId = 0;

//Set the values for the sending of the trigger pulse
#define TIMER_US 50                                   // 50 uS timer duration
#define TICK_COUNTS 20                              // 200 mS worth of timer ticks


volatile long echo_start = 0;                         // Records start of echo pulse
volatile long echo_end = 0;                           // Records end of echo pulse
volatile long echo_duration = 0;                      // Duration - difference between end and start
volatile int trigger_time_count = 0;                  // Count down counter to trigger pulse time

void PingSensorSetup(int trigPinId, int echoPinId)
{
    _trigPinId = trigPinId;
    _echoPinId = echoPinId;
    
    //Setup the trigger pin
    pinMode(trigPinId, OUTPUT);
    digitalWrite(trigPinId, LOW);
    
    //Setup the echo pin
    pinMode(echoPinId, INPUT);
    digitalWrite(echoPinId, HIGH);

    
// WAS using the internal timer for the sendng of the pulse BUT Its creating problems at this point.
//I need to research it more and test some more.
//Timer0
/*
    TCCR0A = (1 << WGM01);
    TCCR0B = (1 << CS00) | (1 << CS01) | (1 << CS02);
    
    OCR0A = 194;
    
    TIMSK0 = (1 << OCIE0A);
*/
//Timer2
/*
    //Using Timer2 Interrupt to send out our sonic pulse.
    TCCR2A = (1 << WGM21);
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);

     OCR2A = 194; //Gives us .009 or 01 Sec
    
    // When the OCR2A register matches the Timer2 count, cause an interrupt
    TIMSK2 = _BV(OCIE2A);
*/
 
    //Attach the interrupt Pin2
    attachInterrupt(0, echo_interrupt, CHANGE);  // Attach interrupt to the sensor echo input
}




/*
  Get the current duration
 */
long CurrentDuration()
{
    Manual_trigger_pulse();
    delay(51);
    return echo_duration;
}

/*
 * Manually trigger the Sonic pulse
 */
void Manual_trigger_pulse()
{
    digitalWrite(_trigPinId, HIGH);              // Set the trigger output high
    delay(50);
    digitalWrite(_trigPinId, LOW);               // Set the trigger output low

}

// --------------------------
// trigger_pulse() called every 10 uS to schedule trigger pulses.
// Generates a pulse one timer tick long.
// Minimum trigger pulse width for the HC-SR04 is 10 us. This system
// delivers a 50 uS pulse.
// --------------------------
/*
ISR (TIMER2_COMPA_vect)
{
    static volatile int state = 0;                 // State machine variable
    
    --trigger_time_count;
    
    if (trigger_time_count <= 0)                   // Count to 200mS
    {
        // Time out - Initiate trigger pulse
        trigger_time_count = TICK_COUNTS;           // Reload
        state = 1;                                  // Changing to state 1 initiates
       
    }
    
    switch(state)                                  // State machine handles delivery of trigger pulse
    {
        case 0:                                      // Normal state does nothing
            break;
            
        case 1:                                      // Initiate pulse
            digitalWrite(_trigPinId, HIGH);              // Set the trigger output high
            state = 2;                                // and set state to 2
            break;
            
        case 2:                                      // Complete the pulse
        default:
            digitalWrite(_trigPinId, LOW);               // Set the trigger output low
            state = 0;                                // and return state to normal 0
            break;
    }
}
*/
//Timer0
/*
ISR (TIMER0_COMPA_vect)
{
    static volatile int state = 0;                 // State machine variable
    
    --trigger_time_count;
    
    if (trigger_time_count <= 0)                   // Count to 200mS
    {
        
        // Time out - Initiate trigger pulse
        trigger_time_count = TICK_COUNTS;           // Reload
        state = 1;                                  // Changing to state 1 initiates
        
    }
    
    switch(state)                                  // State machine handles delivery of trigger pulse
    {
        case 0:                                      // Normal state does nothing
            break;
            
        case 1:                                      // Initiate pulse
            digitalWrite(_trigPinId, HIGH);              // Set the trigger output high
            state = 2;                                // and set state to 2
            break;
            
        case 2:                                      // Complete the pulse
        default:
            digitalWrite(_trigPinId, LOW);               // Set the trigger output low
            state = 0;                                // and return state to normal 0
            break;
    }
}
*/


// --------------------------
// echo_interrupt() External interrupt from HC-SR04 echo signal.
// Called every time the echo signal changes state.
//
// Note: this routine does not handle the case where the timer
//       counter overflows which will result in the occassional error.
// --------------------------
void echo_interrupt()
{
    uint8_t oldSREG = SREG;
    cli ();
    switch (digitalRead(_echoPinId))                     // Test to see if the signal is high or low
    {
        case HIGH:                                      // High so must be the start of the echo pulse
            echo_end = 0;                                 // Clear the end time
            echo_start = micros();                        // Save the start time
            break;
            
        case LOW:                                       // Low so must be the end of hte echo pulse
            echo_end = micros();                          // Save the end time
            echo_duration = echo_end - echo_start;        // Calculate the pulse duration
            break;
    }
    SREG = oldSREG;
}



