#include <Arduino.h>
#include <Sticks.h>

Axis axes[3] = {
    Axis(A5, 'P'),
    Axis(A6, 'T'),
    Axis(A7, 'Z')
};
Sticks sticks = Sticks(3, axes);

uint32_t next_print = 0;
uint32_t print_every = 250;
bool done = false;

void setup() {
    Serial.begin(115200);
    sticks.begin();
}

void loop() {
    sticks.loop();
    if (millis() >= next_print) {
        next_print = millis() + print_every;
        Serial.print(sticks.getValue('P'));
        Serial.print(", ");
        Serial.print(sticks.getValue('T'));
        Serial.print(", ");
        Serial.print(sticks.getValue('Z'));
        
        Serial.println();
    }
}