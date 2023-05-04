#include <Arduino.h>
#include "user_main.h"

void setup() 
{
    Serial.begin(115200);
}

void loop() 
{
    user_main();
}