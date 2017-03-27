#include <Keypad.h>
#include <Servo.h>

Servo servo;
byte C4 = 7;
byte C3 = 6;
byte C2 = 5;
byte C1 = 4;
byte R4 = 8;
byte R3 = 9;
byte R2 = 2;
byte R1 = 3;

const byte ROWS2 = 4; //four rows
const byte COLS2 = 4; //four columns
char keys2[ROWS2][COLS2] = {
  {'1','2','3','0'},
  {'4','5','6','0'},
  {'7','8','9','0'},
  {'0','0','0','0'}
};

//byte rowPins2[ROWS2] = {R1, R2, R3, R4}; //connect to the row pinouts of the keypad
//byte colPins2[COLS2] = {C1, C2, C3, C4}; //connect to the column pinouts of the keypad

byte rowPins2[ROWS2] = {3, 2, 9, 8}; //connect to the row pinouts of the keypad
byte colPins2[COLS2] = {4, 5, 6, 7}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys2), rowPins2, colPins2, ROWS2, COLS2 );

int estado = 0;
void setup() {
  Serial.begin(9600);
   keypad.setHoldTime(250);               // Default is 1000mS
   //keypad.setDebounceTime(250); 
  servo.attach(10);
}

void loop() { // Add an event listener.

  switch (estado){
    case 0:
      leer();
      break;
  }
  /*
  servo.write(90);
  delay(1000);
  servo.write(0);
  delay(1000);
  */
}

void leer(){
  String leido = "";
  while(true){
    char tecla = keypad.getKey();
      if ( tecla ){
        Serial.print("You pressed: ");
        Serial.println(tecla);
        servo.write(90);
        delay(250);
        servo.write(0);
        delay(250);
      }
    }
 }
