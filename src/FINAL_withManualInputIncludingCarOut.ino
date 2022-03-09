#define triggerPin 1 // Trigger pin for sonar sensor
#define echoPin 7// Echo pin for sonar sensor
#define E1 6  // Enable Pin for motor
#define I1 8  // Control pin 1 for motor
#define I2 9  // Control pin 2 for motor


// include the library code:
//#include <Keyboard.h>

#include <LiquidCrystal.h>
#include<Servo.h>

Servo  servoMain;
//Servo  servoGate;

char incomingByte;   // for incoming serial data

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

double distance;

boolean manual = 1;

void setup() {
    
   
    servoMain.attach(13);
    //servoGate.attach(10);
    Serial.begin (9600);
   
    pinMode(triggerPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(E1, OUTPUT);
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(10, OUTPUT);
    digitalWrite(10, LOW);
  //  pinMode(ManIn, INPUT);//MANINPUT
    //PID
    //initialize the variables we're linked to
   int sensorValue = analogRead(A0); 
   
   //initialize servo angle 0
     servoMain.write(0);
    // delay(1000);
   
    //servoGate.write(0);
  
   // set up the LCD's number of columns and rows:
   lcd.begin(16, 2);
   // Print a message to the LCD.

   
   
   
   }
 
void loop() {


     double gain = 6.89;
     double error = distance - 3.0;
     double Pcontrol= gain*error;
     
     // read the input on analog pin 0:
     int sensorValue = analogRead(A0);
    
     // print out the value you read:
     Serial.println(sensorValue);
  
     delay(1);        
     // delay in between reads for stability 


  
    long duration, distance;
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration/2)/29.1;
 
 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    
   // lcd.clear();
    
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    //lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    //lcd.print(millis() / 1000);



    //CODE FOR MANUAL INPUT
//start comment when automatic 

if(1){
      if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();

                // say what you got:
                lcd.setCursor(0,1);
                lcd.print("Manual Input");
                Serial.print("I received: ");
                Serial.println(incomingByte);
                
        }
        switch(incomingByte){
          case'f' :  analogWrite(E1, 255);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Full Speed");
          lcd.setCursor(0,1);
          lcd.print("Manual Input");
          break;
          case'm' : analogWrite(E1, 180);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Meduim Speed");
          lcd.setCursor(0,1);
          lcd.print("Manual Input");
          break;
          case'o' : analogWrite(E1, 0);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("OFF");
          lcd.setCursor(0,1);
          lcd.print("Manual Input");
          break;
          case'9': servoMain.write(90);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Servo 90");
          lcd.setCursor(0,1);
          lcd.print("Manual Input");
          break;
          case'4': servoMain.write(45);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Servo 45");
          lcd.setCursor(0,1);
          lcd.print("Manual Input");
          break;
          case'0': servoMain.write(0);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Servo 0");
          lcd.setCursor(0,1);
          lcd.print("Manual Input");
          break;
          case'e' : 
          digitalWrite(I1, LOW);
          digitalWrite(I2, HIGH);
          analogWrite(E1, 255);
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("Car Out");
          lcd.setCursor(0,1);
          lcd.print("Manual Input");
          break;
        }
         if (incomingByte == 'h' || incomingByte == 'H')
        {
         // digitalWrite(10, HIGH);
        }
        else
        {
        //digitalWrite(10, LOW);
        } 
}//end comment when automatic

    else{//Remove when automatic
    
      if (distance >40|| distance <= 0){
        //servoGate.write(0);

         //first things first motor code
         analogWrite(E1, 0);  // Stop 
         
         //Message On LCD
         //lcd.setCursor(0, 1);
         //lcd.print("BY: HADABA...KHALED...MOSTAFA"); // indicates the belt is ready to transport the next car
         lcd.clear();
         lcd.setCursor(0, 0);
         char Welcome[] = {'W','e','l','c','o','m','e',' ','t','o',' ','t', 'h' ,'e',' ', 'S','m','a','r','t',' ', 'P','a','r','k','i','n','g' ,' ','S','y','s','t','e','m'};
         for(int thisChar=0; thisChar<35;thisChar++){
         
         if(thisChar >15){
         lcd.scrollDisplayLeft();
          }
          lcd.print(Welcome[thisChar]);
          delay (500);
          }
        
         
        // lcd.autoscroll();
        /* lcd.print("Welcome to the Smart Parking System");
         lcd.autoscroll();
         Serial.println("Out of range");
         lcd.setCursor(0, 1);
         lcd.print("Warning!");
         Serial.println("Warning!");
         lcd.noAutoscroll();*/

         } 
  else{ 
  
    if (distance <= 40 && distance >=17){
       //Message On LCD
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Car is in:  ");
       Serial.print("Car is in:  ");
       lcd.print(distance);
       Serial.print(distance);
       lcd.print("cm");
       Serial.println("cm");
       //Serial.println("Warning!");
       Serial.println("You are safe!");
      
       //Belt Running Speed
        analogWrite(E1, Pcontrol);
       //analogWrite(E1, 255);  // Run in Full speed
      }
    if (distance < 17 && distance > 3 ){
       //Message On LCD
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("Car is in:  ");
       Serial.print("Car is in:  ");
       lcd.print(distance);
       Serial.print(distance);
       lcd.print("cm");
       Serial.println(" cm; ");
       Serial.println("You are safe!");
      int gain = 10;
      int error = distance - 3;
      
     switch(error){
      case 1 : gain = 175;break;
      case 2 : gain = 90;break;
      case 3 : gain = 62;break;
      case 4 : gain = 48;break;
      case 5 : gain = 39;break;
      case 6 : gain = 34;break;
      case 7 : gain = 30;break;
      case 8 : gain = 27;break;
      case 9 : gain = 24;break;
      case 10 : gain = 22;break;
      case 11 : gain = 21;break;
      case 12 : gain = 20;break;
      case 13 : gain = 19;break;
     }
      int Pcontrol= gain*error;
      
       //Belt Running Speed
       analogWrite(E1, Pcontrol);  // Run in half speed
       }
    
    if (distance <= 3){
       lcd.clear();
       lcd.setCursor(0, 0);
       lcd.print("you reached your");
       lcd.setCursor(0, 1);
       lcd.print("destination!");
       //Serial.println("Warning!");
       Serial.println("You are safe!");
       analogWrite(E1, 0);  // Stop

       delay(5000);
       servoMain.write(100);
       //delay(1000);
    
 
       Serial.print("AngleOK!!");
       }
       }
     

 
    delay(1000);
     }//Remove bracket when automatic
}


