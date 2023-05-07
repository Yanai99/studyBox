#include <LiquidCrystal.h>
#define BUTTON_END 13
#define BUTTON_UP 12
#define BUTTON_DOWN 11

// if button is pressed than 1 else 0

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 2, 3, 4, 5);

int contrastPin = 9; // Replace with the actual pin number connected to the contrast pin of your LCD screen
int timeHours = 0;
String time = "00:40"; 

void setup() {
  Serial.begin(9600);

  pinMode(contrastPin, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  analogWrite(contrastPin, 100); // adjust the value to change the contrast
  // set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, Student!");
  delay(3000);
}

void loop() 
{
  while(digitalRead(BUTTON_PIN))
  {
    if(!digitalRead(BUTTON_UP))
    {

    }
    if(!digitalRead(BUTTON_DOWN))
    {

    }
  }
  Serial.println(digitalRead(BUTTON_PIN));
  delay(100);
}
