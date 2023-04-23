/*     Simple Stepper Motor Control Exaple Code
 *      
 *  by Dejan Nedelkovski, www.HowToMechatronics.com
 *  
 *  10 pressings = 22.38 s
 *  1 pressing = 2.238 s
 *  26.81 rounds/min
 *  1608.57 rounds/h
 *  38605.9 rounds/d
 *  270241 round/week
 */
 /*
  * Motor voltage setting
  * resistor R1/S1/S2: R10 = 0.1 Ohm
  * Vref = Imax * 8 * R1
  * let's use stepper at 80% of max. current of 2A = 1.6A
  * Vref = 1.6 * 8 * 0.1 = 1.28A
  * or 80% of motor max. current of 1.7A = 1.36V
  * Vref = 1.36 * 8 * 0.1 = 1.09V
  */
#include <ctype.h>

// defines pins numbers
const int dirPin = 3; // LOW = up; HIGH = down
const int stepPin = 4;
const int enPin = 5;


float step_mode = 4; // MS2 == HIGH
int delay_steps = round(2000/step_mode);
int delay_pause = 100;

int steps_per_rev = 200*step_mode;
int mm_per_rev = 8;
float des_pressing_dist;
float pressing_rots;
int pressing_steps;


int loop_count = 1;
 
String val = "s";
String val_inside = "s";
String input = "s";

String readString;
int iterations = 1;
int dist;

void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);

}
void loop() {
  while (Serial.available()) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = Serial.read();
    readString += c;
  }
  
  if (readString.length() > 0) {
    input = readString;
    //Serial.println(input);
    readString="";

    if(input.startsWith("r")){
      val = input.substring(0, 1);
      // Serial.println(val);
      iterations = input.substring(1, 5).toInt();
      // Serial.println(iterations);
      dist = input.substring(5, input.length()).toInt();
      // Serial.println(dist);
    } else{
      val = input;
    }

    if (val == "r"){
      Serial.print("running for iterations: ");
      Serial.print(iterations);
      Serial.print('\n');
      for(int loop_count = 1; loop_count <= iterations; loop_count++) {
          digitalWrite(LED_BUILTIN, HIGH);
          //this should take ~ 0.875 s
  
          des_pressing_dist = dist;
          pressing_rots = des_pressing_dist/mm_per_rev; // *step_mode;
          pressing_steps = pressing_rots*steps_per_rev;
          //Serial.print(pressing_steps);
          
          //Serial.print("press\n");
          digitalWrite(enPin, LOW);
          digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
          for(int x = 0; x < pressing_steps; x++) {
            // curr_delay = delay_steps; // delay_steps + round(delay_steps/2) - x;
            digitalWrite(stepPin,HIGH);
            delayMicroseconds(delay_steps);
            digitalWrite(stepPin,LOW);
            delayMicroseconds(delay_steps);
          }
          delay(delay_pause);
         
          //Serial.print("release\n");
          digitalWrite(dirPin,LOW); //Changes the rotations direction
          // Makes 400 pulses for making two full cycle rotation
          for(int x = 0; x < pressing_steps; x++) {
            digitalWrite(stepPin,HIGH);
            delayMicroseconds(delay_steps);
            digitalWrite(stepPin,LOW);
            delayMicroseconds(delay_steps);
          }
          delay(delay_pause);
          
          while (Serial.available()) {
            delay(2);  //delay to allow byte to arrive in input buffer
            char c = Serial.read();
            readString += c;
          }
          
          if (readString.length() > 0) {
          val_inside = readString;
          readString="";
            if(val_inside == "s"){
              val = "s";
              loop_count = iterations;
              Serial.print("stopping.\n");
              digitalWrite(LED_BUILTIN, LOW);
            }
          }
          Serial.print("Loop iteration: ");
          Serial.print(loop_count);
          Serial.println();
      }

      //get press up again
      digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
        for(int x = 0; x < pressing_steps; x++) {
          // curr_delay = delay_steps; // delay_steps + round(delay_steps/2) - x;
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(delay_steps);
          digitalWrite(stepPin,LOW);
          delayMicroseconds(delay_steps);
        }
      delay(delay_pause);
          
      Serial.print("All done!\n");
      Serial.print("de-energizing steppers");
      digitalWrite(enPin, HIGH);
      Serial.println();
    }
    if(val == "i"){
      // move inside 1 mm
      Serial.print("towards 1mm\n");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(enPin, LOW);
      
      des_pressing_dist = 1;
      //Serial.print(des_pressing_dist);
      pressing_rots = des_pressing_dist/mm_per_rev; // *step_mode;
      //Serial.print(pressing_rots);
      pressing_steps = pressing_rots*steps_per_rev;
      //Serial.print(pressing_steps);
      digitalWrite(dirPin,HIGH);
      for(int x = 0; x < pressing_steps; x++) {
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(delay_steps);
          digitalWrite(stepPin,LOW);
          delayMicroseconds(delay_steps);
        }
      digitalWrite(LED_BUILTIN, LOW);
    }
    if(val == "o"){
      // move outside 1 mm
      Serial.print("away 1mm\n");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(enPin, LOW);
      
      des_pressing_dist = 1;
      //Serial.print(des_pressing_dist);
      pressing_rots = des_pressing_dist/mm_per_rev; // *step_mode;
      //Serial.print(pressing_rots);
      pressing_steps = pressing_rots*steps_per_rev;
      //Serial.print(pressing_steps);
      digitalWrite(dirPin,LOW);
      for(int x = 0; x < pressing_steps; x++) {
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(delay_steps);
          digitalWrite(stepPin,LOW);
          delayMicroseconds(delay_steps);
        }
      digitalWrite(LED_BUILTIN, LOW);
    }
    if(val == "t"){
      // move inside (towards) 10 mm
      Serial.print("towards 1mm\n");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(enPin, LOW);
      
      des_pressing_dist = 10;
      //Serial.print(des_pressing_dist);
      pressing_rots = des_pressing_dist/mm_per_rev; // *step_mode;
      //Serial.print(pressing_rots);
      pressing_steps = pressing_rots*steps_per_rev;
      //Serial.print(pressing_steps);
      digitalWrite(dirPin,HIGH);
      for(int x = 0; x < pressing_steps; x++) {
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(delay_steps);
          digitalWrite(stepPin,LOW);
          delayMicroseconds(delay_steps);
        }
      digitalWrite(LED_BUILTIN, LOW);
    }
    if(val == "a"){
      // move outside (away) 10 mm
      Serial.print("away 1mm\n");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(enPin, LOW);
      
      des_pressing_dist = 10;
      //Serial.print(des_pressing_dist);
      pressing_rots = des_pressing_dist/mm_per_rev; // *step_mode;
      //Serial.print(pressing_rots);
      pressing_steps = pressing_rots*steps_per_rev;
      //Serial.print(pressing_steps);
      digitalWrite(dirPin,LOW);
      for(int x = 0; x < pressing_steps; x++) {
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(delay_steps);
          digitalWrite(stepPin,LOW);
          delayMicroseconds(delay_steps);
        }
      digitalWrite(LED_BUILTIN, LOW);
    }

    if(val == "d"){
      // disable steppers
      Serial.print("de-energizing steppers");
      digitalWrite(enPin, HIGH);
    }
    if(val == "e"){
      // disable steppers
      Serial.print("energizing steppers");
      digitalWrite(enPin, LOW);
    }
  }
}
