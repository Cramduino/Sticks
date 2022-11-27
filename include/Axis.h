#pragma once

#include <Arduino.h>
#include <AxisMode.h>

class Axis {

    private:

        uint8_t _pin;
        char _label;

        AxisMode _mode = AxisMode::NORMAL;

        uint16_t _value;
        uint16_t _limit_lower = 0;
        uint16_t _limit_upper = UINT16_MAX;
        uint16_t _zero_position = UINT16_MAX / 2;
        uint16_t _deadzone_width = 0;

        bool _is_dead(uint16_t value);

    public:
        Axis(uint8_t pin, char label);

        void begin();
        void loop();

        uint16_t getValue();

        AxisMode getMode();
        void setMode(AxisMode mode);

        uint8_t getPin();
        char getLabel();
    
        uint16_t getLowerLimit();
        void setLowerLimit(uint16_t value);

        uint16_t getUpperLimit();
        void setUpperLimit(uint16_t value);

        uint16_t getZeroPos();
        void setZeroPos(uint16_t value);

        uint16_t getDeadzoneWidth();
        void setDeadzoneWidth(uint16_t value);

        uint16_t getRange();
        bool isDead();

};