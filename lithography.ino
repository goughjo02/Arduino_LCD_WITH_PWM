#include "Arduino.h"
#include <LiquidCrystal.h>


byte lcdData7 = 2;
byte lcdData6 = 3;
byte lcdData5 = 4;
byte lcdData4 = 5;
byte lcdReadWrite = 11;
byte lcdDisplayContrast = 12;

#define PWM_OUT 9
#define PWM_IN A4

#define GROUND_JOY_PIN A3            //joystick ground pin will connect to Arduino analog pin A3
#define VOUT_JOY_PIN A2              //joystick +5 V pin will connect to Arduino analog pin A2
#define XJOY_PIN A1
#define YJOY_PIN A0
int XVal;
int Var1;
int Var2;
int percent;
LiquidCrystal lcd(lcdDisplayContrast, lcdReadWrite, lcdData4, lcdData5, lcdData6, lcdData7);

int count = 0;


void setup()
{
	pinMode(VOUT_JOY_PIN, OUTPUT) ;    //pin A3 shall be used as output
	pinMode(GROUND_JOY_PIN, OUTPUT) ;  //pin A2 shall be used as output
	digitalWrite(VOUT_JOY_PIN, HIGH) ; //set pin A3 to high (+5V)
	digitalWrite(GROUND_JOY_PIN,LOW) ;
	XVal = 0;
	Var1 = 170;
	Var2 = 50;
	pinMode(PWM_OUT, OUTPUT) ;
	pinMode(PWM_IN, INPUT) ;
	Serial.begin(115200);
	lcd.begin(16, 2);
	//lcd.blink();
	lcd.clear();
	printTitle1();
	//printTitle2();
	printVar1();
	//printVar2();
	cursorHome();
}

// The loop function is called in an endless loop
void loop()
{
	//updateJoystickX();
	updateJoystickY();
	int Val = analogRead(PWM_IN) ;
	Serial.println(Val);
	printVar1();
	//printVar2();
	delay(20);
}

void printTitle1() {
	lcd.setCursor(1, 0);
	lcd.print("PWM");
}
void printTitle2() {
	lcd.setCursor(8, 0);
	lcd.print("two");
}
void updateJoystickX() {
	int joystickXVal = analogRead(XJOY_PIN) ;
	if (joystickXVal > 800 && XVal < 1) {
		XVal = 1;
		lcd.setCursor(7, 1);
	} else if (joystickXVal < 300 && XVal > 0) {
		XVal = 0;
		lcd.setCursor(0, 1);
	}
}
void updateJoystickY() {
	int joystickYVal = analogRead(YJOY_PIN) ;
	if (XVal == 0 && joystickYVal > 800 && Var1 > 0) {
		Var1 = Var1 - 1;
		analogWrite(PWM_OUT, Var1);
	} else if (XVal == 0 && joystickYVal < 300 && Var1 < 255) {
		Var1 = Var1 + 1;
		analogWrite(PWM_OUT, Var1);
	} else if (XVal == 1 && joystickYVal > 800 && Var2 > 0) {
		Var2 = Var2 - 1;
	} else if (XVal == 1 && joystickYVal < 300 && Var2 < 100) {
		Var2 = Var2 + 1;
	}
}

void cursorHome() {
	if (XVal == 1) {
		lcd.setCursor(7, 1);
	} else {
		lcd.setCursor(0, 1);
	}
}

void printVar1() {
	lcd.setCursor(1, 1);
	percent = (Var1 * 100 / 255);
	lcd.print(percent, DEC);
	lcd.print("%   ");
	cursorHome();
}
void printVar2() {
	lcd.setCursor(8, 1);
	lcd.print(Var2, DEC);
	lcd.print("%   ");
	cursorHome();
}
