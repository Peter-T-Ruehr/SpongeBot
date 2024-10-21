import controlP5.*; //import ControlP5 library
import processing.serial.*;

PrintWriter output;

Serial port;
String COM = "COM4";
String val = "1";    // read serial port
String num = "1";
// String curr_iteration = "1";
String dist;
int send;
float f;
String curr_worker = "NA";

ControlP5 cp5; //create ControlP5 object
// CheckBox checkbox;
RadioButton radioButton;

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
  cp5.addButton("up_1mm")  //The button
    .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ; 
  cp5.addButton("down_1mm")  //The button
    .setPosition(button_pos_x_r, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ; 
  
  r = 3;
  cp5.addButton("up_10mm")  //The button
    .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1))  //x and y coordinates of upper left corner of button
    .setSize(button_width, button_height)      //(width, height)
    .setFont(font)
  ; 
  cp5.addButton("down_10mm")  //The button
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
    
  r = 6;  
  // Create a radiobuttons with string labels
  // checkbox = cp5.addCheckBox("myCheckbox")
  radioButton = cp5.addRadioButton("myRadioButton")
                .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1)+17)
                .setSize(20, 20)        // Size of each checkbox
                .setColorForeground(color(120))  // Checkbox color
                .setColorActive(color(255))      // Checkbox color when active
                .setColorLabel(color(255))       // Label color
                .setItemsPerRow(3)       // Arranges checkboxes in one column
                .setSpacingColumn(50);      // Spacing between rows
      
  // Add labeled checkboxes
  radioButton.addItem("Leandra", 1);
  radioButton.addItem("Peter", 2);
  radioButton.addItem("other", 3);
    
  r = 7; 
  // Create a textlabel
  cp5.addTextlabel("dynamicLabel")
     .setText("curr. iteratuion: " + val)
     .setPosition(button_pos_x_l, button_height*r+button_dist*(r-1)+5)
     .setFont(createFont("Arial", 20))
     .setColor(color(255, 255, 255));
     

  size(430, 530);                          //Window size, (width, height)
  port = new Serial(this, COM, 9600);   //Change this to your port
}

void draw(){  //Same as loop in arduino

  background(150, 0 , 150); //Background colour of window (r, g, b) or (0 to 255)
  
  if ( port.available() > 0)
  { // If data is available,
    val = port.readStringUntil('\n'); 
    if ( val != null ){
      println(val);
      // Update the label with the sensor value
      cp5.get(Textlabel.class, "dynamicLabel").setText("curr. iteration: " + val + " / " + int(num));
  // }
    }
  }
  
  // Display the state of checkboxes
  for (int i = 0; i < radioButton.getArrayValue().length; i++) {
    if (radioButton.getArrayValue()[i] == 1.0) {
      curr_worker = radioButton.getItem(i).getName();
      // print(curr_worker);
    }
  }
}

void run(){
  
  
  // Generate a timestamp using year, month, day, hour, minute, second
  String timestamp = year() + "-" + nf(month(), 2) + "-" + nf(day(), 2) + "_" +
                     nf(hour(), 2) + "-" + nf(minute(), 2) + "-" + nf(second(), 2);
  
  // Create a filename with the current date and time
  String fileName = "data_" + timestamp + ".csv";
  
  // Create the CSV file to write data
  output = createWriter(fileName);
  
  // Print the filename in the console (optional)
  println("Saving data to: " + fileName);
  
  // Write the header to the CSV file
  output.println("time,worker,iterations,distance");
  
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
   print("submitting " + num + " iterations with a distance of " + dist + " mm to the test stand...");
  port.write('r'+num+dist);
  
  // Write the current time and sensor value to the CSV file
  output.println(timestamp + "," + curr_worker + "," + num + "," + dist);
  
  output.flush();  // Flush any remaining data to the file
  output.close();  // Close the file properly
}
void stop(){
  port.write('s');
}
void up_1mm(){
  port.write('i');
}
void down_1mm(){
  port.write('o');
}
void up_10mm(){
  port.write('t');
}
void down_10mm(){
  port.write('a');
}
void de_energize(){
  port.write('d');
}
void energize(){
  port.write('e');
}
