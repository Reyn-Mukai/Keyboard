#include <Keyboard.h>

//Debounce Length (ms)
#define debounceMain 10
#define debounceSecondary 10

//Keybindings
#define xchar 0x78
#define zchar 0x7A
#define lachar 0xD8
#define dachar 0xD9
#define rachar 0xD7
#define uachar 0xDA
#define entchar 0xB0
#define escchar 0xB1

#define ZBUTTON 2
#define XBUTTON 3
#define LABUTTON 7
#define XLED 5
#define ZLED 6
#define UABUTTON 9
#define ENTBUTTON 15
#define ESCBUTTON 14
#define KBSWITCH 10
#define RABUTTON A0
#define DABUTTON 8
#define ACTIVELED 16
#define TRUE 1
#define FALSE 0

//Variable Declarations
volatile int xflag, zflag = 0;
volatile unsigned long xtimer, ztimer = 0;
int laflag, daflag, raflag, uaflag, entflag, escflag = 0;
unsigned long latimer, datimer, ratimer, uatimer, enttimer, esctimer = 0;
int active = 0;

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
  pinMode(ACTIVELED, OUTPUT);

  //attachInterrupt(digitalPinToInterrupt(XBUTTON), kbPressX, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(ZBUTTON), kbPressZ, CHANGE);

  clockTest();

  Serial.begin(115200);
  Serial.println("Pins initialized.");
}

void loop() {
  
  libInit();
  libTerm();

  while(digitalRead(KBSWITCH) == LOW){
    digitalWrite(ACTIVELED, HIGH);
    kbPress(LABUTTON, NULL, lachar, &laflag, &latimer);
    kbPress(DABUTTON, NULL, dachar, &daflag, &datimer);
    kbPress(RABUTTON, NULL, rachar, &raflag, &ratimer);
    kbPress(UABUTTON, NULL, uachar, &uaflag, &uatimer);
    kbPress(ESCBUTTON, NULL, escchar, &escflag, &esctimer);
    kbPress(ENTBUTTON, NULL, entchar, &entflag, &enttimer);
    kbPress(XBUTTON, XLED, xchar, &xflag, &xtimer);
    kbPress(ZBUTTON, ZLED, zchar, &zflag, &ztimer);
  }

  kbDeb(LABUTTON, &laflag, &latimer);
  kbDeb(DABUTTON, &daflag, &datimer);
  kbDeb(RABUTTON, &raflag, &ratimer);
  kbDeb(UABUTTON, &uaflag, &uatimer);
  kbDeb(ENTBUTTON, &entflag, &enttimer);
  kbDeb(ESCBUTTON, &escflag, &esctimer);
  kbDeb(XBUTTON, &xflag, &xtimer);
  kbDeb(ZBUTTON, &zflag, &ztimer);
}

void libInit(){
  if(digitalRead(KBSWITCH) == LOW && active == false){
    active = true;
    flagReset();
    digitalWrite(ACTIVELED, HIGH);
    Keyboard.begin();
    Serial.println("KB lib active");
  }
}

void libTerm(){
  if(digitalRead(KBSWITCH) == HIGH && active == true){
    active = false;
    flagReset();
    digitalWrite(ACTIVELED, LOW);
    Keyboard.releaseAll();
    Keyboard.end();
    Serial.println("KB lib inactive");
  }
}

void flagReset(){
  laflag=raflag=daflag=uaflag=escflag=entflag=xflag=zflag=0;
  Serial.println("Flags reset");
}

void writeAll(int level){
  digitalWrite(XLED, level);
  digitalWrite(ZLED, level);
  digitalWrite(ACTIVELED, level);
}

void clockTest(){
  if(digitalRead(XBUTTON) == LOW && digitalRead(ZBUTTON) == LOW){
    for(int i=0; i<3; i++){
      writeAll(HIGH);
      delay(1000);
      writeAll(LOW);
      delay(1000);
    }
  }
}
/*
void kbPressX(){
  if(digitalRead(XBUTTON) == LOW && xflag == 0){
    if(active == true){
      Keyboard.press(xchar);
      analogWrite(XLED, 100);
    }
    else{
      digitalWrite(ACTIVELED, HIGH);
      Serial.print("Pin: ");
      Serial.print(XBUTTON);
      Serial.println(" is LOW");
    }
    xtimer = millis();
    xflag = 1;
  }
  if(digitalRead(XBUTTON) == HIGH && xflag == 1 && millis()-xtimer > debounceMain){
    if(active == true){
      Keyboard.release(xchar);
      analogWrite(XLED, 0);
    }
    else{
      digitalWrite(ACTIVELED, LOW);
      Serial.print("Pin: ");
      Serial.print(XBUTTON);
      Serial.println(" is HIGH");
    }
    xflag = 0;
  }
}

void kbPressZ(){
  if(digitalRead(ZBUTTON) == LOW && zflag == 0){
    if(active == true){
      Keyboard.press(zchar);
      analogWrite(ZLED, 100);
    }
    else{
      digitalWrite(ACTIVELED, HIGH);
      Serial.print("Pin: ");
      Serial.print(ZBUTTON);
      Serial.println(" is LOW");
    }
    ztimer = millis();
    zflag = 1;
    if(ztimer == 5 && digitalRead(ZBUTTON) == HIGH){
      Keyboard.release(zchar);
      zflag = 0;
    }
  }
  if(digitalRead(ZBUTTON) == HIGH && zflag == 1 && millis()-ztimer > debounceMain){
    if(active == true){
      Keyboard.release(zchar);
      analogWrite(ZLED, 0);
    }
    else{
      digitalWrite(ACTIVELED, LOW);
      Serial.print("Pin: ");
      Serial.print(ZBUTTON);
      Serial.println(" is HIGH");
    }
    zflag = 0;
  }
}
*/
void kbPress(int pin, int led, int key, int *flag, unsigned long *timer){
  if(digitalRead(pin) == LOW && *flag == 0){
    digitalWrite(led, HIGH);
    Keyboard.press(key);
    *timer = millis();
    *flag = 1;
  }
  if(digitalRead(pin) == HIGH && *flag == 1 && millis()-*timer > debounceSecondary){
    digitalWrite(led, LOW);
    Keyboard.release(key);
    digitalWrite(ACTIVELED, LOW);
    *flag = 0;
  }
}

void kbDeb(int pin, int *flag, unsigned long *timer){
  if(digitalRead(pin) == LOW && *flag == 0){
    Serial.print("Pin: ");
    Serial.print(pin);
    Serial.println(" is LOW");
    digitalWrite(ACTIVELED, HIGH);
    *timer = millis();
    *flag = 1;
  }
  if(digitalRead(pin) == HIGH && *flag == 1 && millis()-*timer > debounceSecondary){
    Serial.print("Pin: ");
    Serial.print(pin);
    Serial.println(" is HIGH");
    digitalWrite(ACTIVELED, LOW);
    *flag = 0;
  }
}

