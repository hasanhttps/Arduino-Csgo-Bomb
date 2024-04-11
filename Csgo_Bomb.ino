#include <Keypad.h>
#include <LiquidCrystal.h>
#define Buzzer A0

bool planted = 0;
int tune = 2400;
const byte row = 4;
const byte column = 4;

char text[10] = {'N', 'u', 'm', 'b', 'e', 'r', ' ', ':', ' '};

char keypadMatrix[row][column]{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
}, input;

byte rowPins[row] = {13,12,11,10};
byte columnPins[row] = {9,2,3,4};

Keypad keypadObject = Keypad(makeKeymap(keypadMatrix) , rowPins, columnPins, row, column);
LiquidCrystal lcd(1 ,0 ,5 ,6 ,7 ,8);

long unsigned int number = 0, count = 0, code = 6371673;

void sound(int ms){
  tone(Buzzer,tune);
  delay(ms);
  noTone(Buzzer);
}

void sound(int ms, int frequency){
  tone(Buzzer,frequency);
  delay(ms);
  noTone(Buzzer);
}

void print(int chs){
  
  if ((int)input > 47 && (int)input < 58 && count < 7) {
    number = (number * 10) + ((int)input - 48);
    lcd.print((int)input - 48);
    sound(100);
    count++;
  }
}

void ac(int input){
  if (input == 65) {
    lcd.clear();
    lcd.print(text);
    sound(100);
    delay(100);
    sound(100);
    number = 0;
    count = 0;
  }
}

void bombEffect(int s){
  lcd.setCursor(0, 0);
  for (int i = 0; i < s - 10; i++){
    lcd.clear();
    lcd.print(s - i);
    sound(100, 2700);
    delay(1000);
  }

  for (int i = 10; i > 0; i--){
    lcd.clear();
    lcd.print(i);
    sound(100, 2700);
    delay(i * 10);
  }
  planted=false;
  ac(65);
}

void setup() {
  pinMode(Buzzer,OUTPUT);
  lcd.begin(16,2);
  lcd.print(text);
}

void loop() {
  input = keypadObject.getKey();
  print(input);
  ac(input);

  if (number == code){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bomb has been");
    lcd.setCursor(0,1);
    lcd.print("planted !!");
    delay(600);
    sound(100, 2700);
    delay(100);
    sound(100, 2700);
    planted=true;
    delay(2000);
    bombEffect(40);
  }
}
