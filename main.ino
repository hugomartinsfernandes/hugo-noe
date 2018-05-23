#include <Arduino.h>
#include "include/timer.h"
#define CLK 2 //pins definitions for TM1637 and can be changed to other ports
#define DIO 3
/// The class fsm_state is a type whose value is restricted to a 
/// subset of values
enum class fsm_state 
{
    s0, s1, s2, s3, s4, s5, S6
}

// Declaration of a variable of type fsm_state
fsm_state my_state = fsm_state::s0;

void automate()
{
    static int ms = 0;

    // Update the state only every 1000 function calls
    if(ms == 999)
    {
        ms = 0;

        // Manage the state transitions from the state value
        switch (my_state)
        {
           
            case fsm_state::s0: //si mode normal
            if digitalRead(pin, LOW) && digitalRead(pin, HIGH) // si on appuie une fois sur un bouton
                my_state = fsm_state::s1: // --> mode réglage enclenché
            
        break;

            case fsm_state::s1: // si mode réglage heure
            if digitalRead(pin, LOW) && digitalRead(pin, HIGH) // si on appuie une fois sur le bouton +
                my_state = fsm_state::s201: // incrémenter l'heure + l'afficher

        break;

            case fsm_state::s1: // si mode réglage heure
            if digitalRead(pin, LOW) && digitalRead(pin, HIGH) //si on appuie une fois sur le bouton -
                my_state = fsm_state::s202 // décrémenter l'heure + afficher

        break;

            case fsm_state::s1: // si mode réglage heure
            if digitalRead(pin, LOW) && digitalRead(pin, HIGH) // si on appuie une 2eme fois sur le bouton réglage
                my_state = fsm_state::s3: // passage au mode réglage des minutes

        break;

            case fsm_state::s3: // si mode réglage minute
            if digitalRead(pin, LOW) && digitalRead(pin, HIGH) // si on appuie une fois sur le bouton +
                my_state = fsm_state::s401: // incrémenter les minutes + l'afficher

        break;

            case fsm_state::s3: // si mode réglage minute
            if digitalRead(pin, LOW) && digitalRead(pin, HIGH) // si on appuie une fois sur le bouton -
                my_state = fsm_state::s402: //décrémenter les minutes + l'afficher

        break;

            case fsm_state::s3: // si mode reglage minute
            if digitalRead(pin, LOW) && digitalRead(pin, HIGH) // si on appuie une fois sur le bouton reglage
                my_state = fsm_state::s5: //sauvegarde de l'heure, redémarrage de l'horloge a partir de cette heure
                //sauvegarde
        }
    }
    else
    {
        ms++;
    }
}

void setup()
{
    pinMode(13,OUTPUT);

    // Make the function automate() being called 
    // every 1000 microseconds
    set_timer4_interrupt(1000,automate);
    tm1637.set();
    tm1637.init();
}

void loop()
{
    // Manage the outputs from the state value
    switch (my_state)
    {
        case fsm_state::s0:

            digitalWrite(13,LOW);

            break;

        case fsm_state::s1:

            digitalWrite(13, HIGH);

            break;
    }
}

// Declaration of a int8_t array with 4 elements
int8_t TimeDisp[] = {0, 0, 0, 0};

// Declaration of a TM1637 variable
TM1637 tm1637(CLK, DIO);


void loop()
{
    static int display_point = 0;

    delay(500);

    TimeDisp[3] = 8;
    TimeDisp[2] = 1;
    TimeDisp[1] = 0;
    TimeDisp[0] = 2;

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
