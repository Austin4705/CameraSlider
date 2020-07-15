#include "Arduino.h"
#include "BluetoothSerial.h"
#include "gcode.h"
#include "motorFunctions.h"

class bluetoothFunctions{
  public:
  string parseData(string input){
return(input);
  }
  string readData(){
    if(bluetooth.available){
      return(bluetooth.read());
    }
    else{}
  }
  void writeData(string input){
    if(bluetooth.available){
      bluetooth.write(input);
    }
    else{}
  }
  void writeData(int input){
    if(bluetooth.available){
      bluetooth.write(input);
    }
    else{}
  }
  void writeData(float input){
    if(bluetooth.available){
      bluetooth.write(input);
    }
    else{}
  }
};