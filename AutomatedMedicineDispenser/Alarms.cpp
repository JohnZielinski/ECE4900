/*
//int [6] askGuiForTimeAndDate() Returns an Array of the time and date in format (Hours (##), Minuets (##), Seconds (##), Month (##), Day(##), Year (##))
//int [4] askGuiForTimeAndPills() Returns an array of the time in format (Hours (##), Minuets (##), Seconds (##), Number of pills at this time (##))
//int askGuiForNumberOfPillSlotsBeingUsed() Returns an int of the number of pill slots being used
 
#include <Time.h>
#include <TimeAlarms.h>

void setup()
{
  //Serial.begin(9600);
  //Serial.println("Please eterer the curret Time and stuff");
 //int time[6] = askGuiForTimeAndDate();
  setTime (Time[0], Time[1], Time[2], Time[3], Time[4], Time[5]);      
 

// create the alarms
  int pillSlotsUsed = askGuiForNumberOfPillSlotsBeingUsed(); // An integer that holds the number of pill slots currently being used.
  int pillCount [5]; //An Array that Stores the number of pills to dispense for each specfic pill slot

	int counter = 1; 
	if(counter <= pillSlotsUsed)
		{
			int time [4] = askGuiForTimeAndPills()
			Alarm.alarmRepeat(time[0], time[1], time[2], pillSlotOne);
      pillCount[1] = time[4];
			counter++;
		}

	if(counter <= pillSlotsUsed)
		{
			int time [4] = askGuiForTimeAndPills()
			Alarm.alarmRepeat(time[0], time[1], time[2], pillSlotTwo);
			pillCount[2] = time[4];
			counter++;
		}
		

	if(counter <= pillSlotsUsed)
		{
			int time [4] = askGuiForTimeAndPills()
			Alarm.alarmRepeat(time[0], time[1], time[2], pillSlotThree);
			pillCount[3] = time[4];
			counter++;
		}


	if(counter <= pillSlotsUsed)
		{
			int time [4] = askGuiForTimeAndPills()
			Alarm.alarmRepeat(time[0], time[1], time[2], PillSlotFour);
			pillCount[4] = time[4];
		}
}



void  loop(){  
  digitalClockDisplay();//Displays the current time. This was here before
  //Alarm.delay(1000); // wait one second between clock display
}

// functions to be called when an alarm triggers:
void PillSlotOne{
  Dispense(1,PillCount[1]);
  Serial.print("GET YOU DAMN PILLS FO'");    
}

void PillSlotTwo{
  Dispense(2,PillCount[2]);
  Serial.print("GET YOU DAMN PILLS FO'");      
}

void PillSlotThree{
  Dispense(3,PillCount[3]);
  Serial.print("GET YOU DAMN PILLS FO'");      
}

void PillSlotFour{
  Dispense(4,PillCount[4]);
  Serial.print("GET YOU DAMN PILLS FO'");      
}



// Print the current time to serial
void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println(); 
}

void printDigits(int digits)
{
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
*/
