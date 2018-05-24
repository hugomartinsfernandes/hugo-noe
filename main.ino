#include <Arduino.h>
#include "include/timer.h"
#include "include/TM1637.h"
#include "include/RTCZero.h"

#define CLK 2 //pins definitions for TM1637 and can be changed to other ports
#define DIO 3

#define BP_Jaune 9 //pins definitions for yellow button
#define BP_Rouge 8
#define BP_Bleu 10

/// The class fsm_state is a type whose value is restricted to a 
/// subset of values
enum class fsm_state 
{
    s0, s1_low, s1_high, s2, s3, s4, s5, s6, s201_low, s201_high, s202_low, s202_high
};

// Declaration of a variable of type fsm_state
fsm_state my_state = fsm_state::s0;

// Declaration of a int8_t array with 4 elements
int8_t TimeDisp[] = {0, 0, 0, 0};

// Declaration of a TM1637 variable
TM1637 tm1637 = {CLK, DIO};

/* Create an rtc object */
RTCZero rtc;

void automate()
{
    // Manage the state transitions from the state value
    switch (my_state)
    {
        case fsm_state::s0 : //si mode normal

            if ( digitalRead( BP_Jaune ) == LOW )// si on appuie une fois sur un bouton
            {
                my_state = fsm_state::s1_low;
            }

            break;

        case fsm_state::s1_low : //si mode normal

            if (digitalRead( BP_Jaune ) == HIGH) // si on appuie une fois sur un bouton
            {
                my_state = fsm_state::s1_high;
            }
        
            break;

        case fsm_state::s1_high :

            if (digitalRead ( BP_Bleu ) == LOW)
            {
                my_state = fsm_state::s201_low;
            }  

            else if (digitalRead (BP_Rouge) == LOW)
            {
                my_state = fsm_state::s202_low;
            }               
            
            break;

        case fsm_state::s201_low:

            if (digitalRead (BP_Bleu) == HIGH)
            {
                my_state = fsm_state::s201_high;
            }

            break;

        case fsm_state::s202_low:

            if (digitalRead (BP_Rouge) == HIGH)
            {
                my_state = fsm_state::s202_high;
            }
            break;

        case fsm_state::s201_high:

            //sethour --

            my_state = fsm_state::s1_high;
        


    }
}

void setup()
{
    tm1637.set();
    tm1637.init();

    rtc.begin(); // initialize RTC

    // Make the function automate() being called 
    // every 1000 microseconds
    set_timer4_interrupt(10000,automate);

}




void loop()
{
    static int display_point = 0;
    static int heure = 0;
    static int minute = 0;
    delay(500);

    TimeDisp[3] = minute % 10;
    TimeDisp[2] = minute / 10;
    TimeDisp[1] = heure % 10;
    TimeDisp[0] = heure / 10;

    if (display_point == 0)
    {
        tm1637.point(POINT_ON);
        display_point = 1;
    }
    else
    {
        tm1637.point(POINT_OFF);
        display_point = 0;
    }

    tm1637.display(TimeDisp);
}
