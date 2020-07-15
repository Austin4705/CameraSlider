#include "Arduino.h"
#include "BluetoothSerial.h"
#include "bluetoothFunctions.h"
#include "motorFunctions.h"

class gcode{
  private:
  float speed = 10; //  mm/min
  public:
  void G0(int distance, bool dir, float inputSpeed = speed){

  }
};