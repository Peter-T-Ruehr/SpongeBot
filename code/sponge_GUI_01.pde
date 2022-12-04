import controlP5.*; //import ControlP5 library
import processing.serial.*;

Serial port;
String COM = "COM7";
String val;    // read serial port
String num;
String dist;
int send;
float f;

ControlP5 cp5; //create ControlP5 object

void setup(){ //Same as setup in arduino
  PFont fontL=createFont("arial", 15);
  PFont font=createFont("arial", 11);
  
  int button_width = 120;
  int button_height = 60;
  int button_dist = 10;
  int button_pos_x_l = 90;
  int button_pos_x_r = button_pos_x_l+button_width+button_dist;
 
  int r = 1;
  
  cp5 = new ControlP5(this);
  
    cp5.addTextfield("Sponge test")
     .setPosition(20,0)
     .setFont(fontL)
     ;   
  r = 1; 
  cp5.addButton("run")  //The button
    .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(fontL)
  ;    
  cp5.addButton("stop")  //The button
    .setPosition(button_pos_x_r, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(fontL)
  ; 
  
  r = 2;
  cp5.addButton("towards_1mm")  //The button
    .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ; 
  cp5.addButton("away_1mm")  //The button
    .setPosition(button_pos_x_r, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ; 
  
  r = 3;
  cp5.addButton("towards_10mm")  //The button
    .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ; 
  cp5.addButton("away_10mm")  //The button
    .setPosition(button_pos_x_r, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ; 
  
  r = 4;
  cp5.addButton("energize")  //The button
    .setPosition(button_pos_x_r, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ; 
  cp5.addButton("de_energize")  //The button
    .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ;
  
  r = 5;
  cp5.addTextfield("iterations")
    .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1))
    .setSize(button_width, button_height)
    .setFont(font)
    .setAutoClear(false); 
    
  cp5.addTextfield("distance")
    .setPosition(button_pos_x_r, button_height*r+button_dist*(r-1))
    .setSize(button_width, button_height)
    .setFont(font)
    .setAutoClear(false); 

  size(430, 450);                          //Window size, (width, height)
  port = new Serial(this, COM, 9600);   //Change this to your port
}

void draw(){  //Same as loop in arduino

  background(150, 0 , 150); //Background colour of window (r, g, b) or (0 to 255)
  
  if ( port.available() > 0)
  { // If data is available,
    val = port.readStringUntil('\n'); 
    if ( val != null ){
      println(val);
    }
  }
}

void run(){
  // iterations
  num = cp5.get(Textfield.class,"iterations").getText();
  // if num or n2 is less than 4 digits add a zero to the front of them.
   while (num.length() < 4){
     num = '0' + num;
   }
   // distance
  dist = cp5.get(Textfield.class,"distance").getText();
  // if num or n2 is less than 4 digits add a zero to the front of them.
   while (dist.length() < 4){
     dist = '0' + dist;
   }
   print("submitted " + num + " iterations with a distance of " + dist + " mm to the test stand.");
  //println();
  port.write('r'+num+dist);
}
void stop(){
  port.write('s');
}
void towards_1mm(){
  port.write('i');
}
void away_1mm(){
  port.write('o');
}
void towards_10mm(){
  port.write('t');
}
void away_10mm(){
  port.write('a');
}
void de_energize(){
  port.write('d');
}
void energize(){
  port.write('e');
}
