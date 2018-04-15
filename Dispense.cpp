#include <Servo.h>

Servo servo;
int pos = 0;
int laser_din=2; //set input data pin
int count;
int tick=0;
int complete=1;
void Dispense(int numpills)
{for(count=1; count<=numpills; count+=1)
{
  Serial.println("Starting For loop with Count");
  complete=1;
while(complete){
    Serial.println("Entering pos loop"); 
    for (pos = 0; pos<= 180; pos +=1)
    {
      servo.write(pos);
      Serial.println("moving to position");
      Serial.println(pos);
      //for (tick=0; tick<=360; tick+=1)    // make this delay ~ 10 ms/ we need to test
        if (digitalRead(laser_din)==LOW)
           {
            Serial.println("Found a pill");
            Serial.println(count);
            complete=0;
           break;
            
           }
          
           
        }
}
        delay(1000);
  
    }
 Serial.println("Program End");


  
  delay(1000);
  servo.write(0);  
//  for (pos =180; pos >= 0; pos -=1)
//    {
//      servo.write(pos);
//      delay(10);
//    }
   delay(1000);
  }




void setup() 
{
servo.attach(9);
servo.write(0);
pinMode(laser_din,INPUT);
Serial.begin(9600);
Serial.println("Enter number of pills");
Dispense(2);
}
 
void loop()
{


}


