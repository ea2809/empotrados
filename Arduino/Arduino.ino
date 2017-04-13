#include <Keypad.h>
#include <Servo.h>
#include <LCD.h>
#include <Wire.h>
#include <LiquidCrystal.h>
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
int pinPeso = 13;
unsigned long anterior = 0;

//Pantalla cristal
byte dir = 0x27;
#define I2C_ADDR    0x27
#define  LED_OFF  0
#define  LED_ON  1
//mjkdz i2c LCD board
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
//LiquidCrystal_I2C lcd(I2C_ADDR, 4, 5, 6, 0, 1, 2, 3, 7, NEGATIVE);
LiquidCrystal_I2C lcd(I2C_ADDR, 6, 5, 4, 11, 12, 13, 14, 7,POSITIVE);
// LiquidCrystal_I2C lcd( dir, 2, 1, 0, 4, 5, 6, 7);


const byte ROWS2 = 4; //four rows
const byte COLS2 = 4; //four columns
char keys2[ROWS2][COLS2] = {
  {'1', '2', '3', '0'},
  {'4', '5', '6', '0'},
  {'7', '8', '9', '0'},
  {'0', '0', '0', '0'}
};

//byte rowPins2[ROWS2] = {R1, R2, R3, R4}; //connect to the row pinouts of the keypad
//byte colPins2[COLS2] = {C1, C2, C3, C4}; //connect to the column pinouts of the keypad

byte rowPins2[ROWS2] = {3, 2, 9, 8}; //connect to the row pinouts of the keypad
byte colPins2[COLS2] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys2), rowPins2, colPins2, ROWS2, COLS2 );

int estado = 4;
String leido = "";

void setup() {
  Serial.begin(9600);
  keypad.setHoldTime(250);               // Default is 1000mS
  servo.attach(10);
  servo.write(0);

  lcd.begin(16,2);
  lcd.clear();
  lcd.setBacklight(true);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() { // Add an event listener.

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
    case 3:
      comprobarPeso();
      break;
    case 4: 
      // escanerPadre();
      break;
  }
  /*
    servo.write(90);
    delay(1000);
    servo.write(0);
    delay(1000);
  */
}

void leer() {
  leido = "";
  while (true) {
    char tecla = keypad.getKey();
    if ( tecla ) {
      leido += tecla;
      if ( leido.length() == 4) {
        break;
      }
    }
  }
  estado = 1;
}

void comprobar() {
  Serial.println(leido);
  while (Serial.available() == 0) {}
  if ( Serial.readString() == "1")
    estado = 2;
  else
    estado = 0;
}

void moverServo() {
  servo.write(90);
  delay(250);
  servo.write(0);
  estado = 0;
}

void comprobarPeso() {
  unsigned long actual;
  Serial.println("**********************");
  anterior = millis();
  while (true) {
    actual = millis();
    int val;
    val = digitalRead(pinPeso);
    if (val) {
      Serial.println("Chicle va");
      // estado = 0
      break;
    }
    if (actual - anterior > 3000) {
      Serial.println("Chicle no ha caido, voy a tirarlo de nuevo");
      // estado = 2
      break;
    }

  }
}

void pruebas_imprimir(){
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis()/1000); 
  }


void escanerPadre()
{
  Wire.begin();
  Serial.println("\nI2C Scanner");
  escanerI2C();
}


void escanerI2C()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 0; address <= 130; address++ )
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.print(address,HEX);
      Serial.println(" !");

      nDevices++;
    }
    else if (error==4)
    {
      Serial.print("Unknow error at address 0x");
      if (address<16)
        Serial.print("0");
      Serial.println(address,HEX);
    }    
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(8000);           // wait 8 seconds for next scan
}

