#pragma once
// FUNCTIONALITY FOR THE NUMBER DISPLAYS
// FOR USE WITH SHIFT REGISTER

// LIBRARIES
#include "eBike.h"

// DISPLAY NUMBER
void DisplayNumber(int num) {
	int left_digit = num / 10;
	int right_digit = num % 10;
	digitalWrite(LATCH, LOW);
	for (int i(0); i < 8; ++i) {
		digitalWrite(CLOCK, LOW);
		digitalWrite(SHIFT_IN, digits[left_digit][i]);
		digitalWrite(CLOCK, HIGH);
	}
	for (int i(0); i < 8; ++i) {
		digitalWrite(CLOCK, LOW);
		digitalWrite(SHIFT_IN, digits[left_digit][i]);
		digitalWrite(CLOCK, HIGH);
	}
	digitalWrite(LATCH, HIGH);
}

// LOOKUP TABLE
bool digits[10][8] = {  { LOW,  HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH	},		// 0
						{ LOW,  HIGH, LOW,  LOW,  LOW, LOW,  LOW,  HIGH	},		// 1
						{ HIGH, LOW,  HIGH, HIGH, LOW, LOW,  HIGH, HIGH	},		// 2
						{ HIGH, LOW,  HIGH, HIGH, LOW, HIGH, HIGH, LOW	},		// 3
						{ HIGH, HIGH, LOW,  HIGH, LOW, HIGH, LOW,  LOW	},		// 4
						{ HIGH, HIGH, HIGH, LOW,  LOW, HIGH, HIGH, LOW	},		// 5
						{ HIGH, HIGH, LOW,  LOW,  LOW, HIGH, HIGH, HIGH	},		// 6
						{ LOW,  LOW,  HIGH, HIGH, LOW, HIGH, LOW,  LOW	},		// 7
						{ HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH	},		// 8
						{ HIGH, HIGH, HIGH, HIGH, LOW, HIGH, LOW,  LOW	}  };	// 9