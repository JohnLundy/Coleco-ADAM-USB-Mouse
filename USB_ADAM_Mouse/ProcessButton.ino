void ProcessButton(){               // Read precision mode button for activity

  byte precbuttonstate = digitalRead(precpin);// Read precision button state
  if (precbuttonstate == LOW){      // Precision button has been pressed
    delay( 280 );                   // Hold for a bit to debounce and prevent toggling precision mode on/off right away
    prec = !prec;
    if (prec){
     digitalWrite(ledpin,HIGH);     // Turn LED on when precision mode is active
    }
    if (!prec){
      digitalWrite(ledpin,LOW);     // Turn LED off when precision mode is not active
    }
  }
}
