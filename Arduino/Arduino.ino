#include <Keypad.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

Servo servo;
byte C4 = 7;
byte C3 = 6;
byte C2 = 5;
byte C1 = 4;
byte R4 = 8;
byte R3 = 9;
byte R2 = 2;
byte R1 = 3;
int pinServo = 10;

unsigned long anterior = 0;

#define I2C_ADDR 0x27
  
LiquidCrystal_I2C lcd(I2C_ADDR,16,2);  // set the LCD address to 0x20 for a 16 chars and 2 line display

const byte ROWS2 = 4; //four rows
const byte COLS2 = 4; //four columns

char keys2[ROWS2][COLS2] = {
  {'0', '0', '0', '0'},
  {'3', '6', '9', '0'},
  {'2', '5', '8', '0'},
  {'1', '4', '7', '0'}
};

byte rowPins2[ROWS2] = {3, 2, 9, 8};
byte colPins2[COLS2] = {4, 5, 6, 7};

Keypad keypad = Keypad( makeKeymap(keys2), rowPins2, colPins2, ROWS2, COLS2 );

int estado = 0;
String leido = "";

void setup() {
  Serial.begin(9600);
  keypad.setHoldTime(250);
  servo.attach(pinServo);
  lcd.init();
  lcd.backlight();
}

void loop() {
  switch (estado) {
    case 0:
      leer();
      break;
    case 1:
      comprobar();
      break;
    case 2:
      moverServo();
      break;
  }
}

void leer() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Codigo: ");
  lcd.setCursor(0, 1);
  servo.write(180);
  delay(2000);
  leido = "";
  while (true) {
    char tecla = keypad.getKey();
    if ( tecla ) {
      lcd.print('*');
      leido += tecla;
      if ( leido.length() == 4) {
        break;
      }
    }
  }
  estado = 1;
}

void comprobar() {  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Comprobando...");
  Serial.println(leido);
  while (Serial.available() == 0) {}
  if ( Serial.readString() == "1"){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Perfecto");
    delay(1000);
    estado = 2;
  }else{
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error");
    delay(1000);
    estado = 0;
  }
}

void moverServo() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sacando chicle...");
  servo.write(45);
  delay(2000);
  estado = 0;
}