void Enablepins(){                  // Enable individual output pins to turn on optocoupler outputs - Optocoupler ICs require a HIGH for CLOSED/ON
 
  if (left)                         // Left movement output enable
  {
    digitalWrite(leftpin, HIGH);
    if (!hold)
    {
      left = left - 1;
    }
  }
  if (right)                        // Right movement output enable
  {
    digitalWrite(rightpin, HIGH);
    if (!hold)
    {
      right = right - 1;
    }
  }
  if (up)                           // Up movement output enable
  {
    digitalWrite(uppin, HIGH);
    if (!hold)
    {
      up = up - 1;
    }
  }
  if (down)                         // Down movement output enable
  {
    digitalWrite(downpin, HIGH);
    if (!hold)
    {
      down = down - 1;
    }
  }
  if (arm)                          // ARM button output enable
  {
    digitalWrite(armpin, HIGH);
  }
  if (fire)                         // FIRE button output enable
  {
    digitalWrite(firepin, HIGH);
  }
}
