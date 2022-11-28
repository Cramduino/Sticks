#pragma once

#include <Arduino.h>
#include <Axis.h>

class Sticks {

    private:
        Axis*    _axes;
        uint8_t  _count = 0;
        AxisMode _mode = AxisMode::NORMAL;

    public:
        Sticks(uint8_t num_axes, Axis* axes);
        Sticks(uint8_t num_axes, uint8_t* pins, char* labels);
        
        void begin();
        void loop();

        Axis* getAxis(char axis_label);
        uint16_t getValue(char axis_label);

        AxisMode getMode();
        void setMode(AxisMode mode);

};