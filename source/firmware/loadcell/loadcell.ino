#include "HX711.h"

HX711 loadcell;

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;

float scale = 1.;
int const avg_count = 10;

void setup() {
  Serial.begin(57600);
  loadcell.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  delay(1000);

  Serial.println("Initializing scale");
  Serial.print("  + Averaging: ");
  Serial.println(avg_count);
  
  Serial.print(" + read: \t\t");
  Serial.println(loadcell.read());			// print a raw reading from the ADC

  Serial.print(" + read average: \t\t");
  Serial.println(loadcell.read_average(20));  	// print the average of 20 readings from the ADC

  Serial.print(" + get value: \t\t");
  Serial.println(loadcell.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print(" + get units: \t\t");
  Serial.println(loadcell.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
						// by the loadcell parameter (not set yet)  

  Serial.println("Commands: (R)ead, (T)are, (C)alibrate, (A)DC");

}


void loop() {
  if (Serial.available() > 0) {
    char const cmd = Serial.read();
    switch (cmd) {
    case 'C':
      scale = Serial.parseFloat(); 
      loadcell.set_scale(scale);
      Serial.print("Scale calibrated: ");
      Serial.println(scale);
      break;
    case 'R':
      Serial.println(loadcell.get_units(avg_count),1);
      break;
    case 'T':
      loadcell.tare();
      break;    
    case 'A':
      Serial.println(loadcell.read_average(avg_count));
      break;    
    default:
      break;
    }
  }

}
