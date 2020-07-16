
#include <Arduino.h>
#include "BluetoothSerial.h"
BluetoothSerial bluetooth; //class delcataion for bluetooth
//pins
#define ledPin 2 //onboard 
#define enablePin 34
#define resetPin 35
#define sleepPin 32
#define stepPin 33
#define dirPin 25
#define buttonPin 26
//common consts
#define resolutionPerStep 16
#define stepsPerRotation 200
#define distanceForFullRotation 40 //in mm, this num = teeth on board(20) * distance between teeth(2mm)  
#define railLegnth 500 // useable amount, dont include cutoff for mounting or something
#define homingSpeed 20 //mm/s

//globl ints (mostly for interfacing with multicore or intrupts)
volatile bool buttonPressed = 0;
//classes
class bluetoothFunctions{
  public:
    String readData(){
      String data = "";
      while(bluetooth.available()){
      char charData = bluetooth.read();
      data += charData;
      //// Serial.write(bluetooth.read());    
    }
    return(data);
    }
    void writeData(String inputString){
      for(int counter = 0; counter < inputString.length(); counter++){
          char letter = inputString.charAt(counter); 
          bluetooth.write(letter);
      }
     //bluetooth.write(inputString[inputString.length()]);
    }
    bool findNumber(char inputChar){
    switch (inputChar)
    {
    case '0':
      return (1);
    case '1':
      return (1);
      break;
    case '2':
      return (1);
      break;
    case '3':
      return (1);
      break;
    case '4':
      return (1);
      break;
    case '5':
      return (1);
      break;
    case '6':
      return (1);
      break;
    case '7':
      return (1);
      break;
    case '8':
      return (1);
      break;
    case '9':
      return (1);
      break;
    default:
      return (0);
      break;
    }
  }
  //ill write this tom
  void parseData(String input, int& distance, int& speed, bool& dir){
    if(input.charAt(0) == 'D'){
      //parses here
      int intValues[3] = {0}; //array of 3 to store 3 var
      int startChar = 1; //where the parcer whole start in the program, at char after 1
      String valString = ""; //the string where the value being parsed gets put in
      //put the number into the string
      bool numberOver = 0;
      for (int counter = 0; counter < 3; counter++){ //finds the value 3 different times D100 10 1
        numberOver = 0;
        for(int counterInside = startChar; counterInside < input.length() && numberOver != 1; counterInside++){ //starts at char to start looking for numbers
          if(findNumber(input.charAt(counterInside)) == 1){ //if char is a number
            valString += input.charAt(counterInside); //add to total number
          }
          else{
            startChar = counterInside+1; //number is over ad start at the next char
            numberOver = 1; //throws error to stop loop
            }
        }
        //output the character and reset the string
        intValues[counter] = valString.toInt();
       // Serial.println(String(intValues[counter]));
      //  Serial.println(valString);
        valString = "";
        // Serial.print("Counter ");
        // Serial.print(counter);
      }

      //sets refrence parameters equal to values
      distance = intValues[0];
      speed = intValues[1];
      dir = intValues[2];
      //debbuging
      // Serial.println(String(distance));
      // Serial.println(String(speed));
      // Serial.println(String(dir));

    //parses here
    }
    else{
      writeData("ErrorInvalidCommand");
    }
  }

};
bluetoothFunctions bte;
class motorFunctions{
  private:
  float assumedDistance = 0; //what the pc thinks the rail is at from closet to motor(thats 0)
  int calculateSteps(int degrees){
    int steps = static_cast<int>((degrees / 360.0) * (resolutionPerStep * stepsPerRotation));
    return(steps); 
  }
  float timeBetweenSteps(int totalSteps, float seconds){ // outputs time in ms
    return((seconds/1000) / totalSteps);
  }
  int degreesForDistance(int distance){
    return(9 * distance);// distance / 40 = degrees / 360;   degrees = 360distance /40; degrees = 9distance
  }
  public:
  void driveDegrees(int degrees, int speed, bool direction){
    int steps = calculateSteps(degrees);
    float middleTime = timeBetweenSteps(steps, speed);
    int checkTime = millis();
    setDirection(direction);
    for(int stepCounter = 0; stepCounter < steps; stepCounter++){
        if(millis() >= checkTime + (stepCounter * middleTime)){
          digitalWrite(stepPin, LOW);
          digitalWrite(stepPin, HIGH);
          digitalWrite(stepPin, LOW);         
        }
        else{}
    }
  }
  void driveDistance(int distance, int speed, bool direction){ 
    int degreesToDrive = degreesForDistance(distance);
    driveDegrees(degreesToDrive, speed, direction);
  }
  void driveTotalDistance(){ //allows driving for larger distances than rail legnth

  }
  void homeCarriage(){ //drives the entire amount of the rail and checks if button pressesd,
  // simalar to drive degrees but checks every step if the button interupt has caused a bool to be flipped, 
  //if it doesnt get the flipped button, throw error
    int steps = calculateSteps(degreesForDistance(railLegnth + 20));
    float middleTime = timeBetweenSteps(steps, homingSpeed / railLegnth);
    int checkTime = millis();
    setDirection(1);//drive right to home (CW)
    if(buttonPressed == 0){ // checks if its allready there to save overhead
      for(int stepCounter = 0; stepCounter < steps; stepCounter++){
          if(millis() >= checkTime + (stepCounter * middleTime)){
            if(buttonPressed == 1){
              break;
            }
            else{
            digitalWrite(stepPin, LOW);
       //     delay(15);
            digitalWrite(stepPin, HIGH);
          //  delay(20);
            digitalWrite(stepPin, LOW);          
            }
          }
          else{}
      }
    }
    else{}
    //the thing has homed untill button has been pressed, checks if its been pressed and throws error if havent, 
    //cant throw exit in arduino, used while(1);
    if(buttonPressed == 0){
      bte.writeData("Error, not homed, please reset.");
      while(1){}
    }
    else{}
    buttonPressed = 0;
  }

  void sleepDriver(){
    digitalWrite(sleepPin, LOW);
  }
  void awakeDriver(){
    digitalWrite(sleepPin, HIGH);
  }
  void disableDriver(){
    digitalWrite(enablePin, HIGH);
  }
  void enableDriver(){
    digitalWrite(enablePin, LOW);
  }
  void setDirection(bool direction){
    if (direction == 0){//dir 0 is left 1 is right
      digitalWrite(dirPin, LOW);
    }
    else{
      digitalWrite(dirPin, HIGH);
    }    
  }
};
motorFunctions stepper;

//interupts
void buttonInterupt(){ //make it changeing 
  if(digitalRead(buttonPin) == 1){ //the button has just been hit
    buttonPressed = 1;
  }  
  else{ //the button has just left
    buttonPressed = 0;
  }
}

void setup() {
//setting up bte
  bluetooth.begin("Camera Slider");

  //pins for stepper and led
  pinMode(ledPin, OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  pinMode(sleepPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(buttonPin, INPUT);

//startup value
  digitalWrite(ledPin, LOW); //debugging LED
  digitalWrite(enablePin, LOW); //truns on driver
  digitalWrite(resetPin, LOW);
  digitalWrite(resetPin, LOW);
  digitalWrite(stepPin, LOW);

  //interuputs
  attachInterrupt(buttonPin, buttonInterupt, CHANGE);

  //home device
  //void homeCarriage();
  //tell user finished Initalized;

  //bluetooth.write("T(time s) speed(mm/s) dir(0 is left, 1 is right) ex T300 10 1");
   Serial.begin(115200);
  bte.writeData("Done setting up camera slider, now active, functions: ");
  bte.writeData("D (distance mm) totalTime(s) dir(0 is left, 1 is right), ex D 300 10 1");
  // Serial.println("Startup Done");
}


//simple ik, the var there are refrence btw
void loop() {
  int distance;
  int speed;
  bool dir;
  String inputStr = bte.readData();
  if (inputStr != ""){
    Serial.println(inputStr);
    bte.writeData(inputStr);
    bte.parseData(inputStr, distance, speed, dir);
    stepper.driveDistance(distance, speed, dir);
  }
}







// class gcode{
//   private:
//   float speed = 10; //  mm/min
//   public:
//   void G0(int distance, bool dir, float speed){
//   }
// };

