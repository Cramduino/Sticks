#include <Axis.h>

Axis::Axis(uint8_t pin, char label) {
    this->_pin = pin;
    this->_label = label;
}

bool Axis::_is_dead(uint16_t value) {
    if (value >= this->getZeroPos()) { return (value - this->getZeroPos()) < (this->getDeadzoneWidth() / 2); }
    else return (this->getZeroPos() - value) < (this->getDeadzoneWidth() / 2);
}

void Axis::begin() {
    pinMode(this->_pin, INPUT);
}

void Axis::loop() {
    this->_value = analogRead(this->_pin);
    switch (this->_mode) {
        case AxisMode::CALIBRATE_LIMITS:
            if (this->_value > this->getUpperLimit()) { this->setUpperLimit(this->_value); }
            if (this->_value < this->getLowerLimit()) { this->setLowerLimit(this->_value); }
            break;
        case AxisMode::CALIBRATE_DEADZONE:
            if (!this->isDead()) {
                uint16_t gap = (this->_value > this->getZeroPos()) ? this->_value - this->getZeroPos() : this->getZeroPos() - this->_value;
                this->setDeadzoneWidth(gap * 2);
            }
            break;
        default: break;
    }
}

uint16_t Axis::getValue() { return this->_value; }

AxisMode Axis::getMode() { return this->_mode; }
void Axis::setMode(AxisMode mode) {
    switch (mode) {
        case AxisMode::CALIBRATE_LIMITS:
            this->_value = analogRead(this->_pin);
            this->setZeroPos(this->_value);
            this->setLowerLimit(this->_value);
            this->setUpperLimit(this->_value);
            break;
        case AxisMode::CALIBRATE_DEADZONE:
            this->setDeadzoneWidth(0);
            break;
        default: break;
    }
    this->_mode = mode;
}

uint8_t Axis::getPin() { return this->_pin; }
char Axis::getLabel() { return this->_label; }

uint16_t Axis::getLowerLimit() { return this->_limit_lower; }
void Axis::setLowerLimit(uint16_t value) { this->_limit_lower = value; }

uint16_t Axis::getUpperLimit() { return this->_limit_upper; }
void Axis::setUpperLimit(uint16_t value) { this->_limit_upper = value; }

uint16_t Axis::getZeroPos() { return this->_zero_position; }
void Axis::setZeroPos(uint16_t value) { this->_zero_position = value; }

uint16_t Axis::getDeadzoneWidth() { return this->_deadzone_width; }
void Axis::setDeadzoneWidth(uint16_t value) { this->_deadzone_width = value; }

uint16_t Axis::getRange() { return this->_limit_upper - this->_limit_lower; }

bool Axis::isDead() {
    return this->_is_dead(this->_value);
}