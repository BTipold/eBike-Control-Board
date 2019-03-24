/*
	BRIAN TIPOLD
	EBIKE DASH
	FOR USE WITH CUSTOM ATMEGA328 CIRCUIT
*/

// HEADERS
#include "NumDisplay.h"
#include "eBike.h"

void start_up(void);
void init_io_registers(void);

// VARIABLES
unsigned long int time;
unsigned long int last_time_wheel_speed = 0;
unsigned long int last_time_num_update = 0;
unsigned long int last_time_signal_lights = 0;
unsigned long int last_time_button = 0;
unsigned int quarter_turn_time = 0;
unsigned int speed = 0;
bool last_wheel_sensor_state = false;
bool wheel_sensor_state = false;
bool signal_light_state = false;

// SETUP
void setup() {
	init_io_registers();
	start_up();
}


// LOOP
void loop() {
	// UPDATE CURRENT TIME COUNT
	time = millis();

	// CHECK IF WHEEL SPEED SENSOR IS ACTIVE
	wheel_sensor_state = digitalRead(WHEEL_SPEED_SENSOR);
	if (wheel_sensor_state && !last_wheel_sensor_state) {
		quarter_turn_time = time - last_time_wheel_speed;
		last_time_wheel_speed = time;
		speed = SPEED_FACTOR / quarter_turn_time;
	}
	last_wheel_sensor_state = wheel_sensor_state;

	// LIGHTS
	if (digitalRead(SIGNAL_LIGHT_LEFT)) {
		if (time - last_time_signal_lights > SIGNAL_LIGHT_TIME) {
			signal_light_state = !signal_light_state;
			digitalWrite(FRONT_LEFT_LIGHT, signal_light_state);
			digitalWrite(BACK_LEFT_LIGHT, signal_light_state);
			analogWrite(FRONT_RIGHT_LIGHT, HEADLIGHT_BRIGHTNESS);
			analogWrite(BACK_RIGHT_LIGHT, BRAKELIGHT_BRIGHTNESS);
			last_time_signal_lights = time;
		}
	}
	else if (digitalRead(SIGNAL_LIGHT_LEFT)) {
		if (time - last_time_signal_lights > SIGNAL_LIGHT_TIME) {
			signal_light_state = !signal_light_state;
			digitalWrite(FRONT_RIGHT_LIGHT, signal_light_state);
			digitalWrite(BACK_RIGHT_LIGHT, signal_light_state);
			analogWrite(FRONT_LEFT_LIGHT, HEADLIGHT_BRIGHTNESS);
			analogWrite(BACK_LEFT_LIGHT, BRAKELIGHT_BRIGHTNESS);
			last_time_signal_lights = time;
		}
	}
	else {
		analogWrite(FRONT_LEFT_LIGHT, HEADLIGHT_BRIGHTNESS);
		analogWrite(FRONT_RIGHT_LIGHT, HEADLIGHT_BRIGHTNESS);
		analogWrite(BACK_LEFT_LIGHT, BRAKELIGHT_BRIGHTNESS);
		analogWrite(BACK_RIGHT_LIGHT, BRAKELIGHT_BRIGHTNESS);
	}

	// DISPLAY
	if (time - last_time_num_update > REFRESH_TIME) {
		DisplayNumber(speed);
		last_time_num_update = time;
	}
}


void start_up(void) {
  for(int k(0); k < 4; k++){
  for (int i(0); i < 8; ++i) {
    digitalWrite(LATCH, LOW);
    for (int j(0); j < 8; ++j) {
      digitalWrite(CLOCK, LOW);
      digitalWrite(SHIFT_IN, init_sequence[i][j]);
      digitalWrite(CLOCK, HIGH);
    }
    for (int j(0); j < 8; ++j) {
      digitalWrite(CLOCK, LOW);
      digitalWrite(SHIFT_IN, init_sequence[i][j]);
      digitalWrite(CLOCK, HIGH);
    }
    delay(100);
    digitalWrite(LATCH, HIGH);
  }
}
}

void init_io_registers(void) {
  DDRD = B01111111;
  DDRB = B00001100;
  DDRC = B00000000;
}
