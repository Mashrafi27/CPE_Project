// including the libraries for M5stack, string and for the SD card
#include<M5Core2.h>
#include <String.h>
#include <SPI.h>
#include <SD.h>

//defining three colours and one function for easier use
#define TFT_PINK 0xFC9F
#define green 0x2589
#define red 0xe8e4
#define clr() m5.Lcd.clear();

// creating a dynamic memory for storing the ecg data while showing the graph
int n = 5000;
double *araY = new double[n];

// creating to object of class file for reading and writing files from the SD card
File fY_l;
File fY_g;

// three varibles for three pins that are connected to the m5stack from the sensor
int Lo_p = 23;
int Lo_m = 38;
int output = 36;

// control varibales for different selection_FunctionName functions.
int pos_main =  1;
int pos_set = 1;
int pos_med = 1;
int pos_pat = 1;

// this is control variable for analyzing the ecg data
int analysis = 0;

// this char variable is for changing which screen to show
char ch;

// variable for brightness
int br = 2900;

void setup() {
  // three pins coming from the sensors are set to INPUT because we want to get inputs from these pins
  pinMode(Lo_p,INPUT);
  pinMode(Lo_m,INPUT);
  pinMode(output,INPUT);
  
  // Initializing the M5Stack and SD class 
  M5.begin();
  SD.begin();

  // setting the brightness
  M5.Axp.SetLcdVoltage(br);

  // creating a while loop to print the Instructions
  while(!m5.BtnA.isPressed()){ // waits for the button A to be pressed to break the loop
    M5.update(); // checks if button is pressed or not
    Instructions(); // executes the instruction function
  }
  clr(); // clears the screen because the loop is broken (meaning the button A is pressed) 
  ch = 'M'; // sets the value of ch to 'M' because after proceding from the instruction it will go to the main_menu
}

void loop() {
  M5.update();
  // a single function runs based on the value of ch. A single function normally represents one single instance of a particular screen. It's inside the loop function so it executes indefinitely unless the value of ch is changed
  if(ch == 'M') main_menu();
  else if(ch == 'P') Patient();
  else if(ch == 'm') Meditator();
  else if(ch == 'S') settings();
  else if(ch == 'b') brightness();
  else if(ch == 'd') load_data();
  else if(ch == 'g') show_graph();
  // put your main code here, to run repeatedly:

}
void Instructions()
{
  M5.Lcd.setTextDatum(MC_DATUM); // sets the text alignment to MC = middle center
  M5.Lcd.drawString("Press button B for moving up", 160, 90, 2);
  M5.Lcd.drawString("Press button C for moving down", 160, 110, 2);
  M5.Lcd.drawString("Press button A for selecting", 160, 130, 2);
  m5.Lcd.drawString("Press A to continue to main menu", 160, 150, 2);
  // draws the four strings as the instructions in the middle, with text size 2
}
void main_menu()
{
  M5.Lcd.setTextDatum(MC_DATUM); // same as before, alignment
  m5.Lcd.drawString("Patient", 160, 60, 4);
  m5.Lcd.drawString("Meditator", 160, 120, 4);
  m5.Lcd.drawString("Settings", 160, 180, 4);
  // the three options to go from the main menu
  selection_mainmenu(); // it will do all the works for selecting any of the options
}
void selection_mainmenu()
{
  M5.update(); // waits for button to be pressed
  switch(pos_main) // in this switch statement depending on the value of pos_main, which signifies where the cursor will be with which we will select the option, 1 means the first option, and so on.
  {
    case 1:
      m5.Lcd.drawRect(100,40,120,40,RED); // it draws a red rectangle around that option that the cursor is placed on
      break;
    case 2:
      m5.Lcd.drawRect(100,100,120,40,RED); 
      break;
    case 3:
      m5.Lcd.drawRect(100,160,120,40,RED); 
      break;
  }
  if(m5.BtnA.isPressed()){ // here it deals with if the button A, which is for selection is pressed
    switch(pos_main) // again using switch statement, depending on the value of pos_main, which will signify which option the user selecting it will take action
    {
    case 1: 
      ch = 'P'; // for each case it will set the value of ch for which the void loop function will shift the function to the respective optional function, in this case it will take the user to the patient menu so the value of ch is set as 'P', which will prompt in the void loop function for the Patient function to be started
      clr(); // it clears the screen subsequently as the next function would be overwritten and would cause excess things written in the screen
      break;
    case 2:
      ch = 'm';
      clr();
      break;
    case 3:
      ch = 'S';
      clr();
      break;
    }
  }
  for(int i = 0;i<20;i++){ // loop is just for accuracy in pressing the buttor, delaying the press checking capability
    if(m5.BtnB.isPressed()){ 
      pos_main = (pos_main-1)%3; // if B is pressed then pos_main is decremented, changing the position of the cursor, the value modulo 3 is take for the value to be always within only three values
    }
    else if(m5.BtnC.isPressed()){
      pos_main = (pos_main+1)%3; // if C is pressed then pos_main is incremented, changing the position of the cursor
    }
    if(pos_main == 0) pos_main = 3; // this is because the code cannot produce the modulo of negative numbers, so if the vaue of pos_main is 0 and it decrements it becomes -1, which is 2 module 3, but it doesn't work here, so we articially turn 0 into 3 and work with 1,2,3 instead of 0,1,2
    delay(1);
  }
  m5.Lcd.drawRect(100,40,120,40,BLACK); // turns all the rectangles black, which is essentially clearing the rectangles, sort of like refresh because if the cursor is changed then the previous rectangle will still be in place if it is not removed
  m5.Lcd.drawRect(100,100,120,40,BLACK);
  m5.Lcd.drawRect(100,160,120,40,BLACK);
}


//.....................patient......................//
void Patient() // it is similar to the main_menu function
{
  m5.Lcd.drawString("Load Data from Patient", 160, 70, 4);
  m5.Lcd.drawString("Show existing Data", 160, 130, 4);
  m5.Lcd.drawString("Back", 160, 190, 4);
  selection_patient();
}
void selection_patient() // this is also similar to the main menu's inside selection function function
{
  M5.update();
  switch(pos_pat)
  {
    case 1:
      m5.Lcd.drawRect(10,50,300,40,RED);
      break;
    case 2:
      m5.Lcd.drawRect(10,110,300,40,RED);
      break;
    case 3:
      m5.Lcd.drawRect(10,170,300,40,RED);
      break;
  }
  if(m5.BtnA.isPressed()){
    switch(pos_pat)
    {
    case 1:
      ch = 'd';
      clr();
      fY_l = SD.open("/x.txt", FILE_WRITE); // when the option for loading data is selected then the file where the data would be written is opened here because it should be called only once before writing because calling it means it will overwrite on every previous data that was there, so we can not open it in the loop where it would be called every time one value is added and ultimately will cease the file to have multiple values
      break;
    case 2:
      clr();
      ch = 'g';
      fY_g = SD.open("/x.txt"); // similarly the file is oepend to for reading when showing the graph option is selected, here we don't necessarily need to write the FILE_READ because it is the default
      break;
    case 3:
      ch = 'M'; // in here what it can do is if the back option is selected then it makes it go back to the main_menu
      clr();
      break;
    }
  }
  for(int i = 0;i<20;i++){
    if(m5.BtnB.isPressed()){
      pos_pat = (pos_pat-1)%3;
    }
    else if(m5.BtnC.isPressed()){
      pos_pat = (pos_pat+1)%3;
    }
    if(pos_pat == 0) pos_pat = 3;
    delay(1);
  }
  m5.Lcd.drawRect(10,50,300,40,BLACK);
  m5.Lcd.drawRect(10,110,300,40,BLACK);
  m5.Lcd.drawRect(10,170,300,40,BLACK);
}
void load_data() // this is the load data function, it loads data from the sensor to the text file in the SD card
{
  if(digitalRead(Lo_p) || digitalRead(Lo_m)){ // Lo_p and Lo_m are two pins connected with the sensor which indicates if the electrodes are connected to the body or not, if it's not connceted then
    M5.Lcd.drawString("Electrodes not connected to the body", 160, 100, 2); // it shows some messages that it's not connceted and 
    M5.Lcd.drawString("Press B to return", 160, 140, 2); // says if button is pressed then it will go back to the Patient menu
    if(M5.BtnB.isPressed()){ // if that is pressed then
      clr(); // it does the same old job, clearing the screen and 
      ch = 'P'; // setting the value of ch to the intended screen to go, in this case the Patient menu screen
    }
  }
  else { // if the electrodes are indeed connceted
    clr(); // then is clears the screen
    if(fY_l){ // and provided that the file is there to take the data. (if the SD card is not present then it just won't work)
      M5.Lcd.drawString("Taking data. Wait for a while.", 160, 120, 2); // shows that it's taking data
      for(int i = 0; i < 200000;i++){ // takes the data for the amount of time indicated by the number in the loop condition
        int x = analogRead(output); // takes the data using the analogRead function from the output pin
        fY_l.println(x); // and puts the value in the file
        delay(1);
      }
      clr(); // after it is finished taking the data clears the screen and
      M5.Lcd.drawString("Data Taken.", 160, 120, 2); // says that it has completed taking the data
      delay(1000);
      ch = 'P'; // and goes back to the previous place in the 
      clr(); // same old way but
      fY_l.close(); // doesn't forget to close the file
    }
  }
}
void show_graph() // this is the show_graph function which 
{
  int p = 0; // sets the value of p to 0 in the first time, it won't loop back to here, so no need to worry about it.
    if(fY_g.available()){ // if the file is there
      while(p<90000){ // then for a certain amount of time
        String ys = fY_g.readStringUntil('\n'); // it reads the string in the text file until the new line, essentially grabbing a whole line 
        double yd = atof(ys.c_str()); // we are interested in mathematical data, so it converts the string into a double using the atof() function
        araY[p] = yd/4096; // scaling down to between 0 and 1
        araY[p]*=150; // scaling up a bit, so that we can show a graph showable in the screen of the M5stack, which is of 240 pixels height
        p++; // increments the p
      }
     for(int j = 1;j<20000;j+=4){ // now its time to draw the graph, this is the loop for changing the frame, essentially it shifts 4 pixels, or 4 data each time
        for(int i = 1;i < 320;i++){ // this is the loop to draw in the 320 pixel length, considering that the x-axis, for which the value of the ecg data will represent the y-axis along the 240 pixel height
          double y1 = 240.0 - araY[j+i-1]; // puts two adjacent data into to values, it's not necessary, but still, looks neat
          double y2 = 240.0 - araY[i+j]; // also, we are using j+i, i here represents where we are in the screen's x-axis, but j represents the frame where we are, which is essentially the element that should be in the 0th length in the screen, so it is added to i to get the exact value from the array to plot on the graph
          M5.Lcd.drawPixel(i, y2, 0xffff); // first it draws the pixel
          M5.Lcd.drawLine(i-1,y1,i,y2, 0xffff); // and then it draws the line between the two values
        }
      // here we do the analysis of the data a bit to show green or red colour on the screen
      if(analysis > 240) M5.Lcd.fillScreen(red); // if the value of analysis, which the number of places passed without presence of a peak is greater than 24, so there is irregularity, so it shows red
      else M5.Lcd.fillScreen(green); // and it shown green instead
      if(araY[j] > 100 && analysis > 0 && analysis < 160){ // there is another thing to do, if it shows the peak, but pretty fast
        analysis = 0; // first making the anaysis zero because it counts from the previous sighting of a peak, so everytime there is a peak it resets to zero
        M5.Lcd.fillScreen(red); // it also turns it red
      }
      else if(araY[j] > 100) analysis = 0; // otherwise in general it just resets it to 0
      else analysis++; // otherwise it increments it
      // one thing to note here is that we are changing 4 pixels in a frame, normally, there is a peak in around 800 milliseconds, divided by 4 it is 200, so we are taking the range to be 160-240 milliseconds for the graph to remain green and otherwise red
      }
    }
  ch = 'P'; // after showing it quits to the patient menu
  clr(); // in the same old way but
  fY_g.close(); // closing the file
}


//..................................
void Meditator()
{
  // initializing the variable for storing the number of breathing
  int t; 
  // Sets the text color, size, and position
  M5.Lcd.setTextColor(TFT_PINK,BLACK);
  M5.Lcd.setTextSize(2); //sets the text size to 2
  M5.Lcd.setCursor(100,0); // 
  M5.Lcd.print("Meditation \n");
  M5.Lcd.setCursor(110,20);
  M5.Lcd.print("duration\n\n\n");
  M5.Lcd.setTextSize(2);
  //Prints instructions for choosing duration
  M5.Lcd.print("Press Button A for \n1 minute\n"); 
  M5.Lcd.print("Press Button B for \n3 minutes\n");
  M5.Lcd.print("Press Button C for \n5 minutes\n");
  M5.Lcd.setCursor(0,0);
  M5.update();
  // In this part, 4-7-8 breathing technique is used: inhales for 4 seconds, holds for 7 seconds, and exhales for 8 seconds
  // BtnA == 1 min; BtnB == 3 min; BtnC ==5 min;
  // If the user selects 1 minute
  if (M5.BtnA.wasPressed()){
    M5.Lcd.clear();
    t = 60/19; //Divide 60 seconds by 19 seconds (which is 4+7+8)
    M5.Lcd.print("Scan QR code for song\n");
    //Displays QR code on the screen for music Marconi Union - Weightless
    M5.Lcd.qrcode("https://www.youtube.com/watch?v=UfcAVejslrU",60,50,150,3);
    M5.Lcd.setCursor(0,210);
    //Warns the user that meditation will start in 15 seconds
    M5.Lcd.print("Starting in 15 seconds");
    delay(15000);
    M5.Lcd.clear();
    //Calls the function breathing() and passes number of breaths
    breathing(t);
  }
  //Similar to the 1 minute
  if (M5.BtnB.wasPressed()){
    M5.Lcd.clear();
    t = 180/19; // Divide 180 seconds by 19 seconds
    M5.Lcd.print("Scan QR code for song\n");
    M5.Lcd.qrcode("https://www.youtube.com/watch?v=UDVtMYqUAyw",60,50,150,3); // Interstellar Main Theme
    M5.Lcd.setCursor(0,210);
    M5.Lcd.print("Starting in 15 seconds");
    delay(15000);
    M5.Lcd.clear();
    breathing(t);
  }
  // Similar to the 1 minute 
  if (M5.BtnC.wasPressed()){
    M5.Lcd.clear();
    t = 300/19; // Divide 300 seconds by 190 seconds
    M5.Lcd.print("Scan QR code for song\n");
    M5.Lcd.qrcode("https://www.youtube.com/watch?v=Mr9T-943BnE",60,50,150,3); // Rain sound
    M5.Lcd.setCursor(0,210);
    M5.Lcd.print("Starting in 15 seconds");
    delay(15000);
    M5.Lcd.clear();
    breathing(t);
  }
}
void breathing(int t){
  M5.Lcd.setTextColor(TFT_PINK,BLACK);
  M5.Lcd.setTextSize(4);  
  //The vibrating pattern continues for the total number of breathing
  for(int i = 0; i<t; i++){
    M5.Lcd.setCursor(0,0);
    M5.Lcd.print("Breathe in\n"); 
    M5.Axp.SetLDOEnable(3, true);
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);
    delay(3000); //delay of 1000 and 3000 sums up to 4 seconds of inhaling
    M5.Lcd.clear();
    M5.Lcd.print("Hold your \nbreath\n");
    M5.Axp.SetLDOEnable(3, true);
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);
    delay(6000); //delay of 1000 and 6000 sums up to 7 seconds of holding breath
    M5.Lcd.clear();
    M5.Lcd.print("Exhale\n");
    M5.Axp.SetLDOEnable(3, true);
    delay(1000);
    M5.Axp.SetLDOEnable(3, false);
    delay(7000); //delay of 1000 and 7000 sums up to 8 seconds of exhaling
    M5.Lcd.clear();
  }
}

void settings() // settings also works almost the same way as the main_menu or the patient menu
{
 
  m5.Lcd.drawString("Brightness", 160, 32, 4);
  m5.Lcd.drawString("Back", 160, 76, 4);
  selection_settings(); 
}
void selection_settings() // the selection embedded in here works also the same way
{
  M5.update();
  M5.Lcd.setTextDatum(MC_DATUM);
  switch(pos_set)
  {
    case 1:
      m5.Lcd.drawRect(85,17,150,30,RED);
      break;
    case 2:
      m5.Lcd.drawRect(85,61,150,30,RED);
      break;
  }
  if(m5.BtnA.isPressed()){
    switch(pos_set)
    {
    case 1:
      ch = 'b';
      clr();
      break;
    case 2:
      ch = 'M';
      clr();
      break;
    }
  }
  if(m5.BtnB.isPressed()){
    pos_set = (pos_set-1)%2;
  }
  else if(m5.BtnC.isPressed()){
    pos_set = (pos_set+1)%2;
  }
  if(pos_set == 0) pos_set = 2;
  delay(20);
  m5.Lcd.drawRect(85,17,150,30,BLACK);
  m5.Lcd.drawRect(85,61,150,30,BLACK);
}

void brightness()
{
  m5.Lcd.setTextDatum(MC_DATUM); 
  m5.Lcd.drawString("BRIGHTNESS",160,120,4); // first we print a brightness text to show the brightness when the user it changing it
  if(m5.BtnB.isPressed() && br>=2500) M5.Axp.SetLcdVoltage(--br); // it reduced the brightness until the value 2500
  if(m5.BtnC.isPressed() && br<=3300) M5.Axp.SetLcdVoltage(++br); // and increases until the value 3300, because the value for changing the brightness should be between these values as referred by the M5Stack documentation
  if(m5.BtnA.wasPressed() ){ // then if button A is pressed
    ch = 'M'; // then it returns to the main menu
    clr(); // like before
  }
}
