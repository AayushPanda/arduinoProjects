import processing.serial.*; // imports library for serial communication
import java.awt.event.KeyEvent; // imports library for reading the data from the serial port
import java.io.IOException;

Serial srial;                            //intitiates Serial as srial (couldn't come up with a better name)

String output = "";
String data = "";
String angle = "";
String dist = "";
String conStat;

Integer iAngle;
Integer iDist;
Integer delim = 0;
Integer delim2 = 0;

Float pixDist;



void Setup(){
  size (1920,1080);
  smooth();
  srial = new Serial(this, "COM5", 9600); //intitializing serial port at COM5 and 9600
  srial.bufferUntil('\n');                //Waits until newline
//  orcFont = loadFont("OCRAExtended-30.vlw");
}
//--------------------------------------------------------------------------------------------------------------//Drawing everything//--------------------------------------------------------------------------------------------------------------------------------
void draw() {
  
  fill(98,245,31);
//  textFont(orcFont);
  // simulating motion blur and slow fade of the moving line
  noStroke();
  fill(0,4); 
  rect(0, 0, width, 1010); 
  
  fill(98,245,31); // green color
  // calls the functions for drawing the radar
  drawRadar(); 
  drawLine();
  drawObject();
  drawText();
}
//-----------------------------------------------------------------------------------------------------------//Processing information from COM5//---------------------------------------------------------------------------------------------------------------------
void serialEvent (Serial srial){
  output = srial.readStringUntil('\n');   //reads output from COM5 until newline and assigns to string output
  data = output.substring(0,output.length()-1);    
  delim = data.indexOf(",");              //finds string , and assigns to delim
  angle = data.substring(0, delim);       //reads output from position 0 to delim and assigns it as a separate string to angle
  dist = data.substring(delim+1, data.length());    //reads output from position delim+1 to end of data and assigns it as a separate string to dist
  iAngle = int (angle);
  iDist = int (dist);
}
//-----------------------------------------------------------------------------------------------------------//Drawing text on screen//-------------------------------------------------------------------------------------------------------------------------------

void drawText() { // draws the texts on the screen
  
  pushMatrix();
  if(iDist>40) {
  conStat = "Out of Range";
  }
  else {
  conStat = "In Range";
  }
  fill(0,0,0);
  noStroke();
  rect(0, 1010, width, 1080);
  fill(98,245,31);
  textSize(25);
  text("10cm",1180,990);
  text("20cm",1380,990);
  text("30cm",1580,990);
  text("40cm",1780,990);
  textSize(40);
  text("Object: " + conStat, 240, 1050);
  text("Angle: " + iAngle +" °", 1050, 1050);
  text("Distance: ", 1380, 1050);
  if(iDist<40) {
  text("        " + iDist +" cm", 1400, 1050);
  }
  textSize(25);
  fill(98,245,60);
  translate(961+960*cos(radians(30)),982-960*sin(radians(30)));
  rotate(-radians(-60));
  text("30°",0,0);
  resetMatrix();
  translate(954+960*cos(radians(60)),984-960*sin(radians(60)));
  rotate(-radians(-30));
  text("60°",0,0);
  resetMatrix();
  translate(945+960*cos(radians(90)),990-960*sin(radians(90)));
  rotate(radians(0));
  text("90°",0,0);
  resetMatrix();
  translate(935+960*cos(radians(120)),1003-960*sin(radians(120)));
  rotate(radians(-30));
  text("120°",0,0);
  resetMatrix();
  translate(940+960*cos(radians(150)),1018-960*sin(radians(150)));
  rotate(radians(-60));
  text("150°",0,0);
  popMatrix(); 
}
//----------------------------------------------------------------------------------------------------------------------------//Drawing lines//-----------------------------------------------------------------------------------------------------------------------------

void drawLine() {
  pushMatrix();
  strokeWeight(9);
  stroke(30,250,60);
  translate(960,1000); // moves the starting coordinats to new location
  line(0,0,950*cos(radians(iAngle)),-950*sin(radians(iAngle))); // draws the line according to the angle
  popMatrix();
}
//----------------------------------------------------------------------------------------------------------------------------//Draws distance marker arcs//----------------------------------------------------------------------------------------------------------------------

void drawRadar() {
  pushMatrix();
  translate(960,1000); // moves the starting coordinats to new location
  noFill();
  strokeWeight(2);
  stroke(98,245,31);
  // draws the arc lines
  arc(0,0,1800,1800,PI,TWO_PI);
  arc(0,0,1400,1400,PI,TWO_PI);
  arc(0,0,1000,1000,PI,TWO_PI);
  arc(0,0,600,600,PI,TWO_PI);
  // draws the angle lines
  line(-960,0,960,0);
  line(0,0,-960*cos(radians(30)),-960*sin(radians(30)));
  line(0,0,-960*cos(radians(60)),-960*sin(radians(60)));
  line(0,0,-960*cos(radians(90)),-960*sin(radians(90)));
  line(0,0,-960*cos(radians(120)),-960*sin(radians(120)));
  line(0,0,-960*cos(radians(150)),-960*sin(radians(150)));
  line(-960*cos(radians(30)),0,960,0);
  popMatrix();
}
//---------------------------------------------------------------------------------------------------------------------//Draws object and radar shadow//---------------------------------------------------------------------------------------------------------------

void drawObject() {
  pushMatrix();
  translate(960,1000); // moves the starting coordinats to new location
  strokeWeight(9);
  stroke(255,10,10); // red color
  pixDist = iDist*22.5; // covers the distance from the sensor from cm to pixels
  // limiting the range to 40 cms
  if(iDist<40){
    // draws the object according to the angle and the distance
  line(pixDist*cos(radians(iAngle)),-pixDist*sin(radians(iAngle)),950*cos(radians(iAngle)),-950*sin(radians(iAngle)));
  }
  popMatrix();
}
