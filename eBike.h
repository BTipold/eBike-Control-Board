#pragma once

#include "NumDisplay.h"

// PINS
#define SHIFT_IN			2
#define LATCH				3
#define CLOCK				4
#define FRONT_LEFT_LIGHT	5
#define FRONT_RIGHT_LIGHT	6
#define BACK_RIGHT_LIGHT	9
#define BACK_LEFT_LIGHT		10
#define WHEEL_SPEED_SENSOR	A0
#define SIGNAL_LIGHT_LEFT	A1
#define SIGNAL_LIGHT_RIGHT	A2
#define BRAKES				A3
#define HIGHBEAMS			A4
#define LIGHTS				A5

// CONSTANTS
#define RADIUS 13
#define REFRESH_TIME 500
#define SIGNAL_LIGHT_TIME 750

// MACROS
#define HEADLIGHT_BRIGHTNESS (100 + !digitalRead(HIGHBEAMS) * 155) * !digitalRead(LIGHTS)
#define BRAKELIGHT_BRIGHTNESS !digitalRead(BRAKES) * 255

const float SPEED_FACTOR = (3.1415 / 2 * RADIUS * 0.0000254) / (0.000000278);
