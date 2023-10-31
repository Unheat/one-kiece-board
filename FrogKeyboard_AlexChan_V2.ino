#define KEY_PAUSE           0xD0
#define KEY_NUM_LOCK        0xDB
#define KEY_PRINT_SCREEN    0xCE
#define KEY_SCROLL_LOCK     0xCF
#define KEY_LEFT_GUI        0x83
#define KEY_NUM_LOCK        0xDB
#define KEY_PAUSE           0xD0
#define KEY_NUM_LOCK        0xDB
#define KEY_KP_ENTER        0xE0


// 3 chân điều khiển 74hc595
#define LAT     16
#define CLK     10
#define DATA    14

#define IN     5
#define OUT    4

#define DELAY_PRESS   100

#include "Keyboard.h"

byte led1,led2;
bool LED[10] = {0,0,0,0,0,0,0,0,0,0};
// shift, Sym, Num, sup, capslock, g, hand, GUI, ALT, CTRL
byte point;
byte count = 0;
byte countSpace = 0;
byte countShift = 0;
bool capsLock = 0, spaceLock = 0;

byte BT_OUT[4] = {5,4,3,2};
byte BT_IN[5] = {6,7,8,9,15};

byte mode = 0; 
char key[7][15] = {{'p', 'w', 'r', 'a', 'f', 
                    'd', 't', 'h', 'e', 'o',
                    'y', 's', 'n', 'i', 'u'}
                  ,{'j', 'm', 'b', '\'', KEY_TAB, 
                    'v', 'c', 'l', 'z', 'q',
                    'x', 'g', 'k', 0, 0}
                  ,{';', ':', '*', '&', '?', 
                    '_', '@', '-', '!', '/',
                    '{', '[', '(', '<', '"'}
                  ,{'#', '$', '=', '+', KEY_TAB, 
                    '^', '~', '|', '%', 0,
                    '}', ']', ')', '>', '`'}
                  ,{'-', '7', '8', '9', '*', 
                    '+', '4', '5', '6', '/',
                    '0', '1', '2', '3', '-'}
                  ,{ KEY_PAGE_UP,    KEY_PAUSE,      KEY_END,          KEY_HOME,       KEY_ESC, 
                    KEY_PAGE_DOWN,  KEY_UP_ARROW,   KEY_LEFT_ALT,     KEY_LEFT_CTRL,  KEY_INSERT,
                    KEY_LEFT_ARROW, KEY_DOWN_ARROW, KEY_RIGHT_ARROW,  KEY_BACKSPACE,  KEY_DELETE}
                  ,{KEY_NUM_LOCK, 0, KEY_PRINT_SCREEN, KEY_SCROLL_LOCK, 0, 
                    0, KEY_LEFT_GUI, 0, 0, 0,
                    0, 0, 0, 0, 0}  };


void setup() {
  pinMode(LAT, OUTPUT);
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);

  for(int i = 0; i<OUT; i++){
    pinMode(BT_OUT[i], OUTPUT);
    digitalWrite(BT_OUT[i], HIGH);
  }
  for(int i = 0; i<IN; i++){
    pinMode(BT_IN[i], INPUT_PULLUP);
  }
  
  Serial.begin(9600);
  Keyboard.begin();
  LoadLed();
}

void loop() {
  //if(mode)  mode = 0;
  
  digitalWrite(BT_OUT[3], LOW);
  delay(1);
  checkShift();
  checkEnter();
  checkSymbol();
  checkNumber();
  checkSpace();
  digitalWrite(BT_OUT[3], HIGH);
  delay(1);

  ScanKey(mode);    
  Keyboard.releaseAll(); 
}


void ScanKey(byte modeX){
  // Start Scan key
  count = 0;
  for(byte i=0; i<OUT-1; i++){
    digitalWrite(BT_OUT[i], LOW);
    delay(1);
    for(byte j=0; j<IN; j++){
      point = IN*i+j;
      if(!digitalRead(BT_IN[j]) && key[modeX][point] !=0){
        Keyboard.write(key[modeX][point]);
        while(!digitalRead(BT_IN[j])){
          count++;
          if(count > 50)
            break;
          delay(5);
        }
        count = 0;
      }
    }
    digitalWrite(BT_OUT[i], HIGH);
    delay(1);
  }
//  if(modeX == 1){
//    digitalWrite(BT_OUT[3], LOW);
//    delay(1);
//    if(!digitalRead(BT_IN[1])){
//        Keyboard.write('.');
//        while(!digitalRead(BT_IN[1])){
//          count++;
//          if(count > 50)
//            break;
//          delay(5);
//        }
//        count = 0;
//      }
//      if(!digitalRead(BT_IN[2])){
//        Keyboard.write(',');
//        while(!digitalRead(BT_IN[2])){
//          count++;
//          if(count > 50)
//            break;
//          delay(5);
//        }
//        count = 0;
//      }
//      digitalWrite(BT_OUT[3], HIGH);
//      delay(1);
//  }
  // Stop Scan key
}
////////////////////
void checkShift(){
  if(!digitalRead(BT_IN[0])){
    // check double
    while(!digitalRead(BT_IN[0])){
      countShift++;
      delay(5);
      if(countShift > 100)
        break;
    }
    while(countShift <= 100){
      countShift++;
      delay(5);
      if(countShift > 100)
        break;
      if(!digitalRead(BT_IN[0])){
        LED[4] = 1 - LED[4];
        Keyboard.press(KEY_CAPS_LOCK);
        LoadLed();
        while(!digitalRead(BT_IN[0])){
          countShift++;
          delay(5);
          if(countShift > 100)
            break;
        }
        break;
      }
    }
    // end check double
    Keyboard.press(KEY_LEFT_SHIFT);
    if(LED[0] == 0){
      LED[0] = 1;
      LoadLed();
    }
  } else {
    Keyboard.release(KEY_LEFT_SHIFT); 
    if(LED[0] == 1){
      LED[0] = 0;
      LoadLed();
    }
    if(countShift)
      countShift = 0;
  }
}
void checkEnter(){
  if(!digitalRead(BT_IN[1])){
    if(mode == 1)
      Keyboard.write('.');
    else  Keyboard.write(KEY_KP_ENTER);
    while(!digitalRead(BT_IN[1])){
      count++;
      if(count > 50)
        break;
      delay(5);
    }
    count = 0;
  }
}
void checkSymbol(){
  if(!digitalRead(BT_IN[2])){
    if(mode == 1)
      Keyboard.write(',');
    else  {
      if(mode == 2){
        mode = 0;
        if(LED[1] == 1){
          LED[1] = 0;
          LoadLed();
        }
      } else {
        mode = 2;
        if(LED[1] == 0){
          LED[1] = 1;
          LED[2] = 0;
          LoadLed();
        }
      }
    }
    while(!digitalRead(BT_IN[2])){
        count++;
        if(count > 50)
          break;
        delay(5);
      }
      count = 0;
  }
}
void checkNumber(){
  if(!digitalRead(BT_IN[3])){
    if(mode == 4){
      mode = 0;
      if(LED[2] == 1){
        LED[2] = 0;
        LoadLed();
      }
    } else {
      mode = 4;
      if(LED[2] == 0){
        LED[2] = 1;
        LED[1] = 0;
        LoadLed();
      }
    }
    while(!digitalRead(BT_IN[3]));
    delay(100);
  }
}
void checkSpace(){
  if(!digitalRead(BT_IN[4])){
    // check double
    while(!digitalRead(BT_IN[4])){
      countSpace++;
      delay(5);
      if(countSpace > 100){
        break;
      }
    }
    while(countSpace <= 100){
      countSpace++;
      delay(5);
      if(countSpace > 100){
        Keyboard.write(' ');
        
        break;
      }
      if(!digitalRead(BT_IN[4])){
        LED[3] = 1 - LED[3];
        LoadLed();
        while(!digitalRead(BT_IN[4])){
          countSpace++;
          delay(5);
          if(countSpace > 100)
            break;
        }
        break;
      }
    }
    // end check double
    if(countSpace > 100){
      if(!digitalRead(BT_IN[4])){
        if(mode==0 || mode==2 || mode==4)
          mode++;
      }
    }
  } else  {
    if( LED[3] &&(mode==0 || mode==2 || mode==4))
      mode++;
    if(LED[3]==0 && (mode==1 || mode==3 || mode==5))
      mode--;
    if(countSpace)
      countSpace = 0;
  }
            
}
/////////////////////
void LoadLed(){
  led1 =  LED[0] + LED[1]*2 + LED[2]*4 + LED[3]*8 
        + LED[4]*16 + LED[5]*32 + LED[6]*64; 
  led1 = led1<<1;
  led2 =  LED[7]*16 + LED[8]*32 + LED[9]*64;
  led2 = led2<<1;
  digitalWrite(LAT, LOW);
  shiftOut(DATA, CLK, MSBFIRST, led2);
  shiftOut(DATA, CLK, MSBFIRST, led1);
  digitalWrite(LAT, HIGH);
}
