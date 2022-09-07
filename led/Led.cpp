//
// Created by PC on 2022/9/6.
//
#include "Led.h"

void ledBlink(int gpio,int i)
{
    wiringPiSetup();

    int ledPin = gpio;//our led pin number, WiringPi Pin mode

    pinMode(ledPin, OUTPUT);

    if(i == 0)
    {
        cout<<" set led pin high"<<endl;
        digitalWrite(ledPin, HIGH);
    }
    else
    {
        cout<<" set led pin low"<<endl;
        digitalWrite(ledPin, LOW);
    }
}
