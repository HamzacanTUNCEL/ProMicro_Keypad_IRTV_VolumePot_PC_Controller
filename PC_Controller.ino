#include <HID-Project.h>  //include HID_Project library
#include <HID-Settings.h>
#include <Keypad.h>
#include <IRremote.h>
#define IR_RECEIVE_PIN 10
#define ONCLOSE 220
#define VOLUP 154
#define VOLDOWN 205
#define PLAY 216
#define STOP 212
#define RECORD 128
#define FASTBACK 198
#define FASTFORWARD 213
#define SHIFT 209
#define SLOWBACK 134
#define SLOWFORWARD 144
#define PICTURE 131
#define ONE 146
#define TWO 147
#define THREE 204
#define FOUR 142
#define FIVE 143
#define SIX 200
#define SEVEN 138
#define EIGHT 139
#define NINE 196
#define ZERO 135
#define PR 130
#define RADIO 217
#define PAGEUP 221
#define PAGEDOWN 140
#define MUTE 156
#define MUTE_2 137
#define OK 206
#define UP 202
#define DOWN 210
#define LEFT 153
#define RIGHT 193
#define DELETE 149
#define BACKDELETE 197
#define SELECT 214
#define COPYPASTE 208
#define TVAV 218
#define FAV 136
#define VFORMAT 194
#define TXT 195
#define PR 130

const byte ROWS = 4; 
const byte COLS = 4; 
#define REVERSED false  //if your controller is reversed change it to true
int count_press=0;
int count_press_cp=0;
int counterTVAV=0;
int val = 0;
int previousval = 0;
int val2 = 0;
char hexaKeys[ROWS][COLS] = {
  {'0', '1', '2', '3'},
  {'4', '5', '6', '7'},
  {'8', '9', 'A', 'B'},
  {'C', 'D', 'E', 'F'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void SentenceWriter(String sentence){
    // iterate over each character in the sentence
    for (int i = 0; i < sentence.length(); i++) {
        // write the current character to the serial monitor
        Keyboard.write(sentence[i]);
        // check if the current character is a newline
        if (sentence[i] == '\n')
          delay(1000); // delay for half a second
        else
          delay(1); // delay for 1 millisecond
    }
}


void setup() {
  Serial.begin(9600);
  IrReceiver.begin(IR_RECEIVE_PIN);
  Consumer.begin();  //initialize computer connection
  delay(1000);       //wait for computer to connect
  for (int a = 0; a < 50; a++) {
    Consumer.write(MEDIA_VOLUME_DOWN);  //set the volume to 0
    delay(2);
  }
}

void loop() {
  if (IrReceiver.decode()) {
    delay(40);
    IrReceiver.resume();
    if (IrReceiver.decodedIRData.command!=0)
    Serial.println(IrReceiver.decodedIRData.command);
    int command=IrReceiver.decodedIRData.command;
    switch (command) {
      case PLAY:{
        Consumer.write(MEDIA_PLAY_PAUSE);
        break;
      }
      case VOLUP:{
        Consumer.write(MEDIA_VOLUME_UP);
        break;
      }
      case VOLDOWN:{
        Consumer.write(MEDIA_VOLUME_DOWN);
        break;
      }
      case MUTE:{
        Consumer.write(MEDIA_VOLUME_MUTE);
        break;
      }
      case ONCLOSE:{
        Keyboard.press(KEY_LEFT_ALT);
        Keyboard.press(KEY_F4);

        Keyboard.releaseAll();
        break;
      }
      case PICTURE:{
        Keyboard.press(KEY_LEFT_WINDOWS);
        Keyboard.press(KEY_PRINTSCREEN);
        Keyboard.releaseAll();
        break;
      }
      case PR:{
        Keyboard.press(KEY_SPACE);
        Keyboard.releaseAll();
        break;
      }
      case STOP:{
        Consumer.write(MEDIA_STOP);
        break;
      }
      case FASTFORWARD:{
        Consumer.write(MEDIA_NEXT);
        break;
      }
      case FASTBACK:{
        Consumer.write(MEDIA_PREVIOUS);
        break;
      }
      case SLOWFORWARD:{
        Consumer.write(MEDIA_FAST_FORWARD);
        break;
      }
      case SLOWBACK:{
        Consumer.write(MEDIA_REWIND);
        break;
      }
      case OK:{
        Keyboard.write(KEY_ENTER);
        break;
      }
      case PAGEUP:{
        Keyboard.write(KEY_PAGE_UP);
        break;
      }
      case PAGEDOWN:{
        Keyboard.write(KEY_PAGE_DOWN);
        break;
      }
      case UP:{
        Keyboard.write(KEY_UP_ARROW);
        break;
      }
      case DOWN:{
        Keyboard.write(KEY_DOWN_ARROW);
        break;
      }
      case LEFT:{
        Keyboard.write(KEY_LEFT_ARROW);
        break;
      }
      case RIGHT:{
        Keyboard.write(KEY_RIGHT_ARROW);
        break;
      }
        case RECORD:{
        Keyboard.write(KEY_TAB);
        break;
      }
      case BACKDELETE:{
        Keyboard.write(KEY_BACKSPACE);
        break;
      }
      case DELETE:{
        Keyboard.write(KEY_DELETE);
        break;
      }
      case ONE:{
        Keyboard.write('1');
        break;
      }
      case TWO:{
        Keyboard.write('2');
        break;
      }
      case THREE:{
        Keyboard.write('3');
        break;
      }
      case FOUR:{
        Keyboard.write('4');
        break;
      }
      case FIVE:{
        Keyboard.write('5');
        break;
      }
      case SIX:{
        Keyboard.write('6');
        break;
      }
      case SEVEN:{
        Keyboard.write('7');
        break;
      }
      case EIGHT:{
        Keyboard.write('8');
        break;
      }
      case NINE:{
        Keyboard.write('9');
        break;
      }
      case ZERO:{
        Keyboard.write('0');
        break;
      }
      case SHIFT:{
        Keyboard.press(KEY_LEFT_WINDOWS);
        Keyboard.write(KEY_TAB);
        Keyboard.release(KEY_LEFT_WINDOWS);
        break;
      }
      case MUTE_2:{
        Keyboard.write(KEY_ESC);
        break;
      } 
      case VFORMAT:{
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press('s');
        Keyboard.releaseAll();
        break;
      } 
      case TXT:{
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press('t');
        Keyboard.releaseAll();
        break;
      } 
      case FAV:{
        Keyboard.press(KEY_LEFT_WINDOWS);
        Keyboard.press('d');
        Keyboard.releaseAll();
        break;
      } 
      case TVAV:{
        if (counterTVAV==0){
        Keyboard.write(KEY_F11);
        counterTVAV++;
        }
        else{
        Keyboard.write('f');
        counterTVAV=0;
        }
        break;
      }
      case SELECT:{
        if (count_press==0){
          Keyboard.press(KEY_LEFT_SHIFT);
          count_press++;
        }
        else if (count_press==1){
          Keyboard.release(KEY_LEFT_SHIFT);
          count_press=0;
        }
        break;
      }
      case COPYPASTE:{
        if (count_press_cp==0){
          Keyboard.release(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('c');
          Keyboard.releaseAll();
          count_press_cp++;
        }
        else if (count_press_cp==1){
          Keyboard.release(KEY_LEFT_SHIFT);
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('v');
          Keyboard.releaseAll();
          count_press_cp=0;
        }
        break;
      }
     // case ON:{}

    }
  }
  char customKey = customKeypad.getKey();
  if (customKey=='0'){
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(HID_KEYBOARD_F4);
    Keyboard.releaseAll();
  }
  else if (customKey=='1'){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(HID_KEYBOARD_ESCAPE);
    Keyboard.releaseAll();

  }
  else if (customKey=='2')
  {}
  else if (customKey=='3')
  {}
  else if (customKey=='4'){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('O');
    Keyboard.releaseAll();
  }
  else if (customKey=='5')
    Consumer.write(CONSUMER_EMAIL_READER);
  else if (customKey=='6')
    Consumer.write(CONSUMER_EXPLORER);
  else if (customKey=='7')
    Consumer.write(CONSUMER_CALCULATOR);
  else if (customKey=='8')
    Consumer.write(MEDIA_PLAY_PAUSE);
  else if (customKey=='9'){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('S');
    Keyboard.releaseAll();
  }
  else if (customKey=='A'){
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press('T');
    Keyboard.releaseAll();
  }
  else if (customKey=='B')
  {}
  else if (customKey=='C')
    Consumer.write(MEDIA_PREVIOUS);
  else if (customKeypad.isPressed('D'))
    Consumer.write(MEDIA_REWIND);
  else if (customKeypad.isPressed('E')) 
    Consumer.write(MEDIA_FAST_FORWARD);  
  else if (customKey=='F')
    Consumer.write(MEDIA_NEXT);
  
  val = analogRead(1);              //read potentiometer value
  val = map(val, 0, 1023, 0, 101);  //map it to 102 steps
  if (REVERSED) {
    val = 102 - val;
  }
  if (abs(val - previousval) > 1) {  //check if potentiometer value has changed
    previousval = val;
    val /= 2;  //divide it by 2 to get 51 steps
    while (val2 < val) {
      Consumer.write(MEDIA_VOLUME_UP);  //turn volume up to appropiate level
      val2++;
      delay(2);
    }
    while (val2 > val) {
      Consumer.write(MEDIA_VOLUME_DOWN);  //turn volume down to appropiate level
      val2--;
      delay(2);
    }
  }
  delay(10);  
}  
