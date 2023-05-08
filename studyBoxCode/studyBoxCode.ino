#include <LiquidCrystal.h>
#include <Servo.h>
Servo myServo;

#define BUTTON_END 13
#define BUTTON_UP 12
#define BUTTON_DOWN 11
int ledPin = 6; // the digital pin the LED is connected to

// if button is pressed than 1 else 0

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 2, 3, 4, 5);

int contrastPin = 9; // Replace with the actual pin number connected to the contrast pin of your LCD screen
int timeMinutes = 1;
int timeHours = 0;
char timeString[6];
bool changeTime = false;

void setup() {
  Serial.begin(9600);

  myServo.attach(10); // attach the servo to pin 10
   myServo.write(0);
  pinMode(contrastPin, OUTPUT);
  pinMode(BUTTON_END, INPUT_PULLUP);
  pinMode(BUTTON_UP, INPUT_PULLUP);
  pinMode(BUTTON_DOWN, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT); // set the LED pin as an output

  analogWrite(contrastPin, 100); // adjust the value to change the contrast

  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, Student!");
  delay(3000);
}

void loop() 
{
  digitalWrite(ledPin, HIGH); // turn on the LED
  lcd.clear();
  lcd.print("Time: ");
  setTimeString(timeHours, timeMinutes);
  //String time = String(timeString);
  lcd.print(timeString);

  while(digitalRead(BUTTON_END))
  {
    if(changeTime)
    {
      lcd.clear();
      lcd.print("Time: ");
      setTimeString(timeHours, timeMinutes);
      lcd.print(timeString);
      changeTime = false;
    }

    if(!digitalRead(BUTTON_UP))
    {
      IncreaseTime();
      changeTime = true;
      delay(500);
    }
    if(!digitalRead(BUTTON_DOWN))
    {
      DecreaseTime();
      changeTime = true;
      delay(500);
    }
  }
  CountDown();
  LockBox();
  myServo.write(0);
  /*lcd.clear();
  lcd.print("Done!");*/
  delay(3000);
}

void IncreaseTime()
{
  if(timeMinutes >= 50)
  {
    timeMinutes = 0;
    timeHours = 1;
  }
  else
    timeMinutes += 10;
  
}

void DecreaseTime()
{
  if(timeMinutes <= 00)
  {
    timeMinutes = 50;
    timeHours = 0;
  }
  else
    timeMinutes -= 10;
}

void CountDown() // Gives user 15 seconds to put inside the phone
{
  int i;

  for( i =0; i <15 ; i++)
  {
    lcd.clear();
    lcd.print("Time Left:");
    lcd.setCursor(0, 1);
    lcd.print(15-i);
    lcd.print(" Sec");
    delay(1000);  
  }
  return;
}


void LockBox()
{
  int i;
  int minutesDelay = timeMinutes + (timeHours*60);
  int secondsDelay = minutesDelay * 60;
  int minToDisplay = secondsDelay/60 - i/60;
  digitalWrite(ledPin, LOW); // turn off the LED
  lcd.clear();
  lcd.print("Locked, Study!");
  lcd.setCursor(0, 1);
  lcd.print("Time Left:");
  lcd.print((secondsDelay/60) - i/60);
  myServo.write(160);
  for( i =0; i <secondsDelay ; i++)
  {
    if(!digitalRead(BUTTON_DOWN) && !digitalRead(BUTTON_UP))
    {
      if(GiveUp())
        return;
    }
    if(((secondsDelay/60) - i/60) != minToDisplay)
    {
      minToDisplay = (secondsDelay/60) - i/60;
     lcd.clear();
     lcd.print("Locked, Study!");
     lcd.setCursor(0, 1);
     lcd.print("Time Left:");
     lcd.print((secondsDelay/60) - i/60);
     lcd.print(" Min");
    }

    delay(1000);  
  }
  myServo.write(160);
  lcd.clear();
  lcd.print("Congratz!");

}

void setTimeString(int hours, int minutes)
{
  sprintf(timeString, "%02d:%02d", hours, minutes);
}

bool GiveUp()
{
 
  lcd.clear();
  lcd.print("Loser!");
  delay(1000);
  while(true)
  {
    lcd.clear();
    lcd.print("Do You Confrim?");
    lcd.setCursor(0, 1);
    lcd.print("yes <-  -> NO :)");
    if(!digitalRead(BUTTON_UP))
    {
      return false;
    }
    if(!digitalRead(BUTTON_DOWN))
    {
      return true;
    }
    delay(500);
  }
}

