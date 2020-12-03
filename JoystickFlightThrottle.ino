#include <Joystick.h>

//Joystick_ Joystick;
Joystick_ Joystick(0x04, JOYSTICK_TYPE_JOYSTICK,
                   0, 0,                 // Button Count, Hat Switch Count
                   false, false, false,  // X and Y, but no Z Axis
                   false, false, false,  // No Rx, Ry, or Rz
                   false, true,          // Yes rudder, yes throttle
                   false, false, false); // No accelerator, brake, or steering

void setup()
{
  // Initialize Joystick library
  Joystick.begin(false); // False = don't send automatically. We will sendState() at the end of the loop
  //Joystick.setThrottleRange(-512, 512);
}

void loop()
{
  // Read analog axes
  int inputVal = analogRead(A3);

  // Hack: Current potentiometer is logarithmic. Try to simulate that halfway is middle of range.
  int mappedValue;
  if (inputVal >= 922)
  {
    // Potentiometer is placed that we get high input value when throttle is 0%
    mappedValue = map(inputVal, 922, 1023, 512, 0);
  }
  else
  {
    // Potentiometer is placed that we get 0 input value when throttle is 100%
    mappedValue = map(inputVal, 0, 922, 1023, 512);
  }

  //int mappedValue = map(inputVal , 0, 1023, 1023, 0);
  Joystick.setThrottle(mappedValue);

  Joystick.sendState();
  delay(10);
}
