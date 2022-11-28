#include <Sticks.h>

Sticks::Sticks(uint8_t num_axes, Axis* axes) {
    this->_axes = axes;
    this->_count = num_axes;
}
Sticks::Sticks(uint8_t num_axes, uint8_t* pins, char* labels) {
    this->_axes = (Axis*)malloc(sizeof(Axis) * num_axes);
    for (uint8_t i = 0; i < num_axes; i++) {
        this->_axes[i] = Axis(pins[i], labels[i]);
    }
    this->_count = num_axes;
}

void Sticks::begin() {
    for (uint8_t i = 0; i < this->_count; i++) { this->_axes[i].begin(); }
}

void Sticks::loop() {
    for (uint8_t i = 0; i < this->_count; i++) { this->_axes[i].loop(); }
}

Axis* Sticks::getAxis(char axis_label) {
    for (uint8_t i = 0; i < this->_count; i++) {
        if (this->_axes[i].getLabel() == axis_label) return &this->_axes[i];
    }
    return nullptr;
}

uint16_t Sticks::getValue(char axis_label) {
    Axis* axis = this->getAxis(axis_label);
    return axis ? axis->getValue() : 0;
}

AxisMode Sticks::getMode() { return this->_mode; }
void Sticks::setMode(AxisMode mode) {
    for (uint8_t i = 0; i < this->_count; i++) {
        this->_axes[i].setMode(mode);
    }
    this->_mode = mode;
}