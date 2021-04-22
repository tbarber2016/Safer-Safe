#include <Keypad.h> //lib for keypad
#include <Servo.h> //lib for servo
#define alarm 10 //setting alarm buzzer to pin 10
#define fsrpin A0 // setting fsr sensor to analog 0
Servo Motor; //calling a motor

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns
int count = 0;

char keys[ROW_NUM][COLUMN_NUM] = { //set up keypad
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the rows to keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the columns to keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

String password = "1234"; 
String u_input;
String n_password = "1534";
int fsrRead;
bool locked = true;
void setup(){
  Serial.begin(9600);
  Motor.attach(13); //attach motor to pin 13
  pinMode(alarm, OUTPUT); //make alarm output mode
}

void loop(){
  char key = keypad.getKey(); //check what keys are being presssed
  fsrRead = analogRead(fsrpin); //read value on fsr
  //Serial.print("Analog reading = ");
  //Serial.println(fsrRead);
  if (locked == true && fsrRead == 0){
        Serial.println("Sound the alarm");
         tone(alarm, 1000);
     }
  
  if (key){
    Serial.println(key);

    if(key == 'D') {
       if(password == u_input) { //enter password then press D to initiate change password sequence
      int i = 0;
      tone(alarm, 1000);
      delay(50);
      noTone(alarm);
      delay(50);
      tone(alarm, 1000);
      delay(50);
      noTone(alarm);
       while(i<4){
         char key = keypad.getKey();

          if(key)

            {

                n_password[j++]=key; //get value of new password must be 4 digits
                Serial.println(n_password);
                password = n_password;
                Serial.println(password);
            }
                
                key=0;

                }
            }
    }
    if(key == '*') {
      u_input = "";
       locked = true; //reset input and relock motor
       int pos = Motor.read();
        Serial.println(pos);
         if (pos != 13) { //if motor is not locked beep 
          tone(alarm, 1700);
          delay(100);
          noTone(alarm);
         }
      Motor.write(13);
    } else if(key == '#') {
      if(password == u_input) { // if password correct beep and unlock
        Serial.println("passcode correct");
        Motor.write(90);
        tone(alarm, 2000);
        delay(50);
        tone(alarm, 1500);
        delay(100);
        noTone(alarm);
        locked = false;
        count = 0;
      } else if (password == n_password){ //if password change beep and change pw
        Serial.println("passcode changed");
        tone(alarm, 2000);
        delay(100);
        noTone(alarm);
        n_password="    ";
      } else {
        Serial.println("wrong passcode try again"); //if password wront beep
        count++;
        tone(alarm, 500);
        delay(100);
        noTone(alarm);
        if (count ==3) { //if password wront 3 times or more alarm
          Serial.println("Sound the alarm");
          tone(alarm, 1000); 
          }
          
      }
      

      u_input = ""; //
    } else {
      u_input += key; 
    }
  }
}
