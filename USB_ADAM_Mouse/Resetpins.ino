void Resetpins(){                   // Reset all simulated joystick switches to open - Optocoupler ICs require a LOW for OPEN/OFF

  digitalWrite(armpin, LOW);
  digitalWrite(firepin, LOW);
  digitalWrite(uppin, LOW);
  digitalWrite(downpin, LOW);
  digitalWrite(leftpin, LOW);
  digitalWrite(rightpin, LOW);
}
