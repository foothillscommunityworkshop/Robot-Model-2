#include "FcwServo.h"
#include <Servo360.h>
#include "Arduino.h"

Servo Right;
Servo Left;

//Servo direction parameters
const int DForward = 1;
const int DBackward = 2;
const int DRight = 3;
const int DLeft = 4;

void FcwServoSetup(int RightPin, int LeftPin)
{
    Right.attach(RightPin);  // attaches the right servo to the servo object
    Left.attach(LeftPin);  // attaches the left servo to the servo object
    
    digitalWrite(RightPin, LOW);
    digitalWrite(LeftPin, LOW);
}


//Servo turn function
void Turn(int RL){
    if (RL == DRight) {
        Right.write(180);
        Left.write(180);
    }
    else if (RL == DLeft) {
        Right.write(0);
        Left.write(0);
    }
}

//Servo turn randomly right or left function
void TurnRandom() {
    if (random(1,10001) > 5000) {
        Turn(DRight);
    }
    else {
        Turn(DLeft);
    }
}

//Servo stop function
void Stop() {
    Right.write(90);
    Left.write(90);
}

//Servo move forward or backward function
void Run(int FB) {
    if (FB == DForward) {
        Right.write(0);
        Left.write(180);
    }
    else if (FB == DBackward){
        Right.write(180);
        Left.write(0);
    }
}

