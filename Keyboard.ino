#include "Keyboard.h"

//Defines/Macros
#define ZBUTTON 2
#define XBUTTON 3
#define LABUTTON 4
#define XLED 5
#define ZLED 6
#define UABUTTON 7
#define ENTBUTTON 8
#define ESCBUTTON 9
#define KBSWITCH 10
#define RABUTTON 14
#define DABUTTON 15
#define ACTIVE 16
#define TRUE 1
#define FALSE 0

//Variable Declarations
int zflag, xflag, laflag, daflag, raflag, uaflag, entflag, escflag = 0;
int zdeb, xdeb, ladeb, dadeb, radeb, uadeb, entdeb, escdeb = 0;
//Software to be implemented
int HWDebounce = TRUE; //Set HWDebounce to true if hardware based debounce is implemented otherwise false

void setup() {

  //I/O Declarations
  pinMode(ZBUTTON, INPUT_PULLUP);
  pinMode(XBUTTON, INPUT_PULLUP);
  pinMode(LABUTTON, INPUT_PULLUP);
  pinMode(DABUTTON, INPUT_PULLUP);
  pinMode(RABUTTON, INPUT_PULLUP);
  pinMode(UABUTTON, INPUT_PULLUP);
  pinMode(ENTBUTTON, INPUT_PULLUP);
  pinMode(ESCBUTTON, INPUT_PULLUP);
  pinMode(KBSWITCH, INPUT_PULLUP);
  pinMode(ZLED, OUTPUT);
  pinMode(XLED, OUTPUT);
  pinMode(ACTIVE, OUTPUT);


  Serial.begin(115200);
  Serial.println("Pins initialized.");

  delay(16);
  digitalWrite(ACTIVE, HIGH);
  analogWrite(ZLED, 100);
  analogWrite(XLED, 100);
  delay(13);
  digitalWrite(ACTIVE, LOW);
  analogWrite(ZLED, 0);
  analogWrite(XLED, 0);
  delay(16);
  digitalWrite(ACTIVE, HIGH);
  analogWrite(ZLED, 100);
  analogWrite(XLED, 100);
  delay(13);
  digitalWrite(ACTIVE, LOW);
  analogWrite(ZLED, 0);
  analogWrite(XLED, 0);
  delay(16);
  digitalWrite(ACTIVE, HIGH);
  analogWrite(ZLED, 100);
  analogWrite(XLED, 100);
  delay(13);
  digitalWrite(ACTIVE, LOW);
  analogWrite(ZLED, 0);
  analogWrite(XLED, 0);
  delay(16);
}

void loop() {

  //Only begins Keyboard if grounded
  //Keyboard functions only run within loop
  //Must be LOW to be able to program the stand alone board
  if(digitalRead(KBSWITCH) == LOW){
    Keyboard.begin();
  }

  //Keyboard input mode
  while(digitalRead(KBSWITCH) == LOW){
    digitalWrite(ACTIVE, HIGH);
    if(digitalRead(ZBUTTON) == LOW && zflag == 0){
      Keyboard.press(122);
      analogWrite(ZLED, 100);
      zflag = 1;
    }
    if(digitalRead(ZBUTTON) == HIGH && zflag == 1){
      Keyboard.release(122);
      analogWrite(ZLED, 0);
      zflag = 0;
    }
    if(digitalRead(XBUTTON) == LOW && xflag == 0){
      Keyboard.press(120);
      analogWrite(XLED, 100);
      xflag = 1;
    }
    if(digitalRead(XBUTTON) == HIGH && xflag == 1){
      Keyboard.release(120);
      analogWrite(XLED, 0);
      xflag = 0;
    }
    if(digitalRead(LABUTTON) == LOW && laflag == 0){
      Keyboard.press(0xD8);
      laflag = 1;
    }
    if(digitalRead(LABUTTON) == HIGH && laflag == 1){
      Keyboard.release(0xD8);
      laflag = 0;
    }
    if(digitalRead(DABUTTON) == LOW && daflag == 0){
      Keyboard.press(0xD9);
      daflag = 1;
    }
    if(digitalRead(DABUTTON) == HIGH && daflag == 1){
      Keyboard.release(0xD9);
      daflag = 0;
    }
    if(digitalRead(RABUTTON) == LOW && raflag == 0){
      Keyboard.press(0xD7);
      raflag = 1;
    }
    if(digitalRead(RABUTTON) == HIGH && raflag == 1){
      Keyboard.release(0xD7);
      raflag = 0;
    }
    if(digitalRead(UABUTTON) == LOW && uaflag == 0){
      Keyboard.press(0xDA);
      uaflag = 1;
    }
    if(digitalRead(UABUTTON) == HIGH && uaflag == 1){
      Keyboard.release(0xDA);
      uaflag = 0;
    }
    if(digitalRead(ENTBUTTON) == LOW && entflag == 0){
      Keyboard.press(0xB0);
      entflag = 1;
    }
    if(digitalRead(ENTBUTTON) == HIGH && entflag == 1){
      Keyboard.release(0xB0);
      entflag = 0;
    }
    if(digitalRead(ESCBUTTON) == LOW && escflag == 0){
      Keyboard.press(0xB1);
      escflag = 1;
    }
    if(digitalRead(ESCBUTTON) == HIGH && escflag == 1){
      Keyboard.release(0xB1);
      escflag = 0;
    }
  }

  Keyboard.end();

  digitalWrite(ACTIVE, LOW);

  //Releases keys if buttons are pressed while mode is switched
  if(xflag == 1 || zflag == 1 || laflag == 1 || daflag == 1 || raflag == 1 || uaflag == 1 || escflag == 1 || entflag == 1){
    xflag = zflag = laflag = daflag = raflag = uaflag = escflag = entflag = 0;
    Keyboard.releaseAll();
  }

  //Debug serial & button flashing
  if(digitalRead(ZBUTTON) == LOW && zdeb == 0){
    digitalWrite(ACTIVE, HIGH);
    Serial.println("Z button pressed.");
    zdeb = 1;
  }
  if(digitalRead(ZBUTTON) == HIGH && zdeb == 1){
    zdeb = 0;
  }
  if(digitalRead(XBUTTON) == LOW && xdeb == 0){
    digitalWrite(ACTIVE, HIGH);
    Serial.println("X button pressed.");
    xdeb = 1;
  }
  if(digitalRead(XBUTTON) == HIGH && xdeb == 1){
    xdeb = 0;
  }
  if(digitalRead(LABUTTON) == LOW && ladeb == 0){
    digitalWrite(ACTIVE, HIGH);
    Serial.println("Left button pressed.");
    ladeb = 1;
  }
  if(digitalRead(LABUTTON) == HIGH && ladeb == 1){
    ladeb = 0;
  }
  if(digitalRead(DABUTTON) == LOW && dadeb == 0){
    digitalWrite(ACTIVE, HIGH);
    Serial.println("Down button pressed.");
    dadeb = 1;
  }
  if(digitalRead(DABUTTON) == HIGH && dadeb == 1){
    dadeb = 0;
  }
  if(digitalRead(RABUTTON) == LOW && radeb == 0){
    digitalWrite(ACTIVE, HIGH);
    Serial.println("Right button pressed.");
    radeb = 1;
  }
  if(digitalRead(RABUTTON) == HIGH && radeb == 1){
    radeb = 0;
  }
  if(digitalRead(UABUTTON) == LOW && uadeb == 0){
    digitalWrite(ACTIVE, HIGH);
    Serial.println("Up button pressed.");
    uadeb = 1;
  }
  if(digitalRead(UABUTTON) == HIGH && uadeb == 1){
    uadeb = 0;
  }
  if(digitalRead(ENTBUTTON) == LOW && entdeb == 0){
    digitalWrite(ACTIVE, HIGH);
    Serial.println("Enter button pressed.");
    entdeb = 1;
  }
  if(digitalRead(ENTBUTTON) == HIGH && entdeb == 1){
    entdeb = 0;
  }
  if(digitalRead(ESCBUTTON) == LOW && escdeb == 0){
    digitalWrite(ACTIVE, HIGH);
    Serial.println("Escape button pressed.");
    escdeb = 1;
  }
  if(digitalRead(ESCBUTTON) == HIGH && escdeb == 1){
    escdeb = 0;
  }
  if(zdeb == 1 || xdeb == 1 || ladeb == 1 || dadeb == 1 || radeb == 1 || uadeb == 1 || entdeb == 1 || escdeb == 1){
    digitalWrite(ACTIVE, HIGH);
  }
  else{
    digitalWrite(ACTIVE, LOW);
  }
}

