void ReadSens(){                         // Read trimmer pot on senspin line for analog value for fine tuning mouse_sensitivity value

  if  (prec == false){                   // Is mouse in normal operating mode?
    sens_adj = analogRead(senspin)/70-9; // Create a range of -9 to +5 from a 0 - 1023 analog line read of the trimmer pot
    mouse_sensitivity = 12 + sens_adj;   // Create a mouse sensitivity range of 3 - 17 based off sens_adjust value
    joy_delay = mouse_sensitivity - 7;   // Create joystick delay value 3 - 10 based off mouse sensitivity value
      if (joy_delay <= 3){               // Don't allow sensitivity lower than 3 or it will not work with games
       joy_delay = 3;
      }
    joy_holddelay = joy_delay + 5;
  }
  if  (prec == true){                    // Is mouse in precision mode for paint programs?
    mouse_sensitivity = 1;               // Override normal operating mode settings with new percision values
    joy_delay = 2;
    joy_holddelay = 15;
  }
//  Serial.print("Mouse sensitivity value = ");  // View sensitivity and joystick delay values in terminal for testing
//  Serial.println(mouse_sensitivity);
//  Serial.print("Joy delay value = ");
//  Serial.println(joy_delay);
//  Serial.print("Joy hold delay value = ");
//  Serial.println(joy_holddelay);
}
