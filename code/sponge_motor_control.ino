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

// defines pins numbers
const int dirPin = 3;
const int stepPin = 4;
const int enPin = 5;

boolean state = false;

int steps_per_rev = 200;
int mm_per_rev = 8;
float des_pressing_dist;
float pressing_rots;
int pressing_steps;

float step_mode = 1;

int loop_count = 1;
int delay_steps = round(500/step_mode);
int dealay = 10;
 
char val = "s";
char val_inside = "s";

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
  state = false;
  if (Serial.available()) {
    val = Serial.read();
    while(val == 'r'){
       
      //if (state == false) {
        digitalWrite(LED_BUILTIN, HIGH);
        if(state == false){
          Serial.print("running...\n");
          state = true;
        }
        //this should take ~ 0.875 s

        des_pressing_dist = 35;
        pressing_rots = des_pressing_dist/mm_per_rev*step_mode;
        pressing_steps = pressing_rots*steps_per_rev;
        //Serial.print(pressing_steps);
        
        //Serial.print("press\n");
        digitalWrite(enPin, LOW);
        digitalWrite(dirPin,HIGH); // Enables the motor to move in a particular direction
        for(int x = 0; x < pressing_steps; x++) {
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(delay_steps);
          digitalWrite(stepPin,LOW);
          delayMicroseconds(delay_steps);
        }
        delay(dealay);
       
        //Serial.print("release\n");
        digitalWrite(dirPin,LOW); //Changes the rotations direction
        // Makes 400 pulses for making two full cycle rotation
        for(int x = 0; x < pressing_steps; x++) {
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(delay_steps);
          digitalWrite(stepPin,LOW);
          delayMicroseconds(delay_steps);
        }
        delay(dealay);
        
        val_inside = Serial.read();
        if(val_inside == 's'){
          val = 's';
          Serial.print("stopping.\n");
          //state = false;
          digitalWrite(LED_BUILTIN, LOW);
        }
        Serial.print("Loop iteration: ");
        Serial.print(loop_count);
        Serial.println();
        loop_count += 1;
      //}
    }
    if(val == 'i'){
      // move inside 1 mm
      Serial.print("towards 1mm\n");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(enPin, LOW);
      
      des_pressing_dist = 1;
      //Serial.print(des_pressing_dist);
      pressing_rots = des_pressing_dist/mm_per_rev*step_mode;
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
    if(val == 'o'){
      // move outside 1 mm
      Serial.print("away 1mm\n");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(enPin, LOW);
      
      des_pressing_dist = 1;
      //Serial.print(des_pressing_dist);
      pressing_rots = des_pressing_dist/mm_per_rev*step_mode;
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
    if(val == 't'){
      // move inside (towards) 10 mm
      Serial.print("towards 1mm\n");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(enPin, LOW);
      
      des_pressing_dist = 10;
      //Serial.print(des_pressing_dist);
      pressing_rots = des_pressing_dist/mm_per_rev*step_mode;
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
    if(val == 'a'){
      // move outside (away) 10 mm
      Serial.print("away 1mm\n");
      digitalWrite(LED_BUILTIN, HIGH);
      digitalWrite(enPin, LOW);
      
      des_pressing_dist = 10;
      //Serial.print(des_pressing_dist);
      pressing_rots = des_pressing_dist/mm_per_rev*step_mode;
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

    if(val == 'd'){
      // disable steppers
      Serial.print("de-energizing steppers");
      digitalWrite(enPin, HIGH);
    }
    if(val == 'e'){
      // disable steppers
      Serial.print("energizing steppers");
      digitalWrite(enPin, LOW);
    }
  }
}
