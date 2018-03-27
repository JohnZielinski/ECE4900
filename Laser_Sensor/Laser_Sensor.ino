int laser_din=2; /* Set Input Pin */

void setup()
{
  pinMode(laser_din,INPUT); /*Set Pin to input mode*/
  Serial.begin(9600);
}
void loop()
{
  if(digitalRead(laser_din)==LOW) /*Read Pin. LOW = No Obstacle, HIGH = Obstacle */
  {
    Serial.println("NO Obstacles!");
    exit(0);
  }
  else
  {
    Serial.println("Obstacles!");
  }
  delay(1);
}
