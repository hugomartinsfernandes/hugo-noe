#include <Arduino.h>
#include "include/timer.h"
#include "include/TM1637.h"
#include "include/RTCZero.h"

#define CLK 2 //pins definitions for TM1637 and can be changed to other ports
#define DIO 3

#define BP_Jaune 9 //pins definitions for yellow button
#define BP_Rouge 8
#define BP_Bleu 10

static int heure = 0;
static int minute = 0;
/// The class fsm_state is a type whose value is restricted to a 
/// subset of values
enum class fsm_state 
{
    s0, s1_low, s1_high, s2, s3_high, s3_low, s4, s5, s6, s201_low, s201_high, s202_low, s202_high, s401_low, s401_high, s402_low, s402_high
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
            rtc.setHours(0);
            rtc.setMinutes(0);
            rtc.setSeconds(0);
            tm1637.display(TimeDisp);
            if (digitalRead ( BP_Bleu ) == LOW)
            {
                my_state = fsm_state::s201_low;
            }  

            else if (digitalRead (BP_Rouge) == LOW)
            {
                my_state = fsm_state::s202_low;
            }

             else if (digitalRead (BP_Jaune) == LOW)
            {
                my_state = fsm_state::s3_low;
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

            heure = heure - 1;
            tm1637.display(TimeDisp);
            my_state = fsm_state::s1_high;

            break;

        case fsm_state::s202_high:

            heure = heure + 1;
            tm1637.display(TimeDisp);
            my_state = fsm_state::s1_high;

            break;

        case fsm_state::s3_low:

            if (digitalRead(BP_Jaune) == HIGH) // si on appuie une fois sur un bouton
            {
                my_state = fsm_state::s3_high;
            }

            break;

        case fsm_state::s3_high:

            if (digitalRead(BP_Bleu) == LOW)
            {
                my_state = fsm_state::s401_low;
            }

            else if (digitalRead(BP_Rouge) == LOW)
            {
                my_state = fsm_state::s402_low;
            }

            else if (digitalRead(BP_Jaune) == LOW)
            {
                my_state = fsm_state::s5;
            }

            break;

        case fsm_state::s401_low:

            if (digitalRead(BP_Bleu) == HIGH)
            {
                my_state = fsm_state::s401_high;
            }

            break;

        case fsm_state::s402_low:

            if (digitalRead(BP_Rouge) == HIGH)
            {
                my_state = fsm_state::s402_high;
            }
            break;

        case fsm_state::s401_high:

            minute --;
            tm1637.display(TimeDisp);
            my_state = fsm_state::s3_high;

            break;

        case fsm_state::s402_high:

            minute ++;
            tm1637.display(TimeDisp);
            my_state = fsm_state::s3_high;

            break;
        
        case fsm_state::s5:

            rtc.setHours(heure);
            rtc.setMinutes(minute);
            rtc.setSeconds(0);

            my_state = fsm_state::s0;

            break; 
    }
}

void setup()
{
    pinMode(8,INPUT_PULLUP);
    pinMode(9,INPUT_PULLUP);
    pinMode(10,INPUT_PULLUP);

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
    
    delay(500);
    switch (my_state)
    {
    case fsm_state::s0:
        heure = rtc.getHours();
        minute = rtc.getMinutes();
    }


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
