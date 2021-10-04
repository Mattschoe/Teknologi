#include <Servo.h> //Servo library
#include <LiquidCrystal_I2C.h> //LCD library
#include <Keypad.h> //Keypad library

//LCD Display
#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3
#define En_pin 2
#define Rw_pin 1
#define Rs_pin 0
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
int code = 6969;
int tot, i1, i2, i3, i4;
char c1, c2, c3, c4;

//Servo motor
Servo myservo;
#define servoPin 4
int pos = 0;

//Keypad 
const byte numRows = 4;
const byte numCols = 4;
char keymap[numRows][numCols] = 
{
{'1', '2', '3', 'A'}, 
{'4', '5', '6', 'B'}, 
{'7', '8', '9', 'C'},
{'*', '0', '#', 'D'}
};

//Hvilke pins der er connected til keypaden
byte colPins[numCols] = {13, 12, 11, 10};
byte rowPins[numRows] = {9, 8, 7, 6};

Keypad myKeypad = Keypad(makeKeymap (keymap), rowPins, colPins, numRows, numCols);


void setup() {
  Serial.begin(9600);
  myservo.attach(servoPin); //attacher servo til servopin

  //Lcd
  lcd.begin (16,2);
  lcd.setBacklightPin (BACKLIGHT_PIN, POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.print("Press * to begin");
  delay(1000);
}

void lcdDisplay() {
 char keypressed = myKeypad.getKey();
  if (keypressed == '*') {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Enter Code");
    keypressed = myKeypad.waitForKey();
      if (keypressed != NO_KEY) {
        c1 = keypressed;
        lcd.setCursor(0, 1);
        lcd.print(keypressed);      
      } 
      keypressed = myKeypad.waitForKey();
    
       if (keypressed != NO_KEY) {
        c2 = keypressed;
        lcd.setCursor(1, 1);
        lcd.print(keypressed);    
      }
      keypressed = myKeypad.waitForKey();
    
      if (keypressed != NO_KEY) {
        c3 = keypressed;
        lcd.setCursor(2, 1);
        lcd.print(keypressed); 
      }
      keypressed = myKeyp  ad.waitForKey();
    
      if (keypressed != NO_KEY) {
        c4 = keypressed;
        lcd.setCursor(3, 1);
        lcd.print(keypressed);
      }
    i1 = (c1 - 48) * 1000;
    i2 = (c2 - 48) * 100;
    i3 = (c3 - 48) * 10;
    i4 = (c4 - 48);  
  
    tot = i1 + i2 + i3 + i4;
  
  if (tot == code) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Open");
  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Wrong code");
    delay(3000);
    lcd.clear();
    lcd.print("Press * to try");
    lcd.setCursor(0, 1);
    lcd.print("Again");
  }  
 }
}


void loop() {
  lcdDisplay();
  Serial.println("Tissemand");
}
