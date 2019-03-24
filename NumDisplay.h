#pragma once
// FUNCTIONALITY FOR THE NUMBER DISPLAYS
// FOR USE WITH SHIFT REGISTER

// LIBRARIES
#include "eBike.h"
            
// LOOKUP TABLES
bool init_sequence[10][8] = {
            { LOW, HIGH, LOW, LOW, LOW, LOW, LOW, LOW },    
            { LOW, LOW, HIGH, LOW, LOW, LOW, LOW, LOW },    
            { LOW, LOW, LOW, HIGH, LOW, LOW, LOW, LOW },    
            { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW },    
            { LOW, LOW, LOW, LOW, LOW, LOW, LOW, HIGH },    
            { LOW, LOW, LOW, LOW, LOW, LOW, HIGH, LOW },
            { LOW, LOW, LOW, LOW, LOW, HIGH, LOW, LOW },
            { HIGH, LOW, LOW, LOW, LOW, LOW, LOW, LOW }   };
			

bool digits[10][8] = {  
            { LOW,  HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH },    // 0
            { LOW,  LOW,  LOW,  HIGH, LOW, HIGH, LOW, LOW   },    // 1
            { HIGH, LOW,  HIGH, HIGH, LOW, LOW,  HIGH, HIGH },    // 2
            { HIGH, LOW,  HIGH, HIGH, LOW, HIGH, HIGH, LOW  },    // 3
            { HIGH, HIGH, LOW,  HIGH, LOW, HIGH, LOW,  LOW  },    // 4
            { HIGH, HIGH, HIGH, LOW,  LOW, HIGH, HIGH, LOW  },    // 5
            { HIGH, HIGH, LOW,  LOW,  LOW, HIGH, HIGH, HIGH },    // 6
            { LOW,  LOW,  HIGH, HIGH, LOW, HIGH, LOW,  LOW  },    // 7
            { HIGH, HIGH, HIGH, HIGH, LOW, HIGH, HIGH, HIGH },    // 8
            { HIGH, HIGH, HIGH, HIGH, LOW, HIGH, LOW,  LOW  }  }; // 9

// DISPLAY NUMBER
void DisplayNumber(const int num) {
  int left_digit = num / 10;
  int right_digit = num % 10;
  digitalWrite(LATCH, LOW);
  for (int i(0); i < 8; ++i) {
    digitalWrite(CLOCK, LOW);
    digitalWrite(SHIFT_IN, digits[right_digit][i]);
    digitalWrite(CLOCK, HIGH);
  }
  for (int i(0); i < 8; ++i) {
    digitalWrite(CLOCK, LOW);
    digitalWrite(SHIFT_IN, digits[left_digit][i]);
    digitalWrite(CLOCK, HIGH);
  }
  digitalWrite(LATCH, HIGH);
}

void start_up(void) {
  for (int k(0); k < 4; k++) {
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
