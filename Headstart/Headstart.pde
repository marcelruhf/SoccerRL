import processing.serial.*;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;
import java.net.UnknownHostException;

Serial serial;
Logic logic;
Socket socket;
BufferedReader socketReader;

Keyboard keyboard;
boolean pause = false;
PVector vec = new PVector();
boolean serialInited = false;
int[] userID;
int serialCheckCounter = 0;
boolean wasRunning = false;
char prevAct = 'y';

void setup() {  
  println(serial.list());

  /* open serial port */
  //serial = new Serial(this, serial.list()[0], 115200);    
  //serial = new Serial(this, Serial.list()[0], 115200);
  while(!serialInited) {
    initSerial();
  }
   
  // exitHandler();  
  keyboard = new Keyboard();
  logic = new Logic( keyboard, serial);
  background(200, 0, 0);
  
  try {
    socket = new Socket("localhost", 2323);
    socketReader = new BufferedReader(new InputStreamReader(
          socket.getInputStream()));
  } catch(Exception e) {
    println(e.getMessage());
    System.exit(1);
  }
  
  /* stroke for draing lines in skeleton */
  stroke(0, 0, 255);
  strokeWeight(3);
  smooth();
}

void act() throws IOException {
  int command = socketReader.read();
  //if (message == null && prevAct == 'y')
  //{
    //println("Message is null, action: stop");
    //prevAct = 'z';
    //logic.keyboard('z');
  //} else if (message == null && prevAct != 'y') {
    //println("Message is null, action: " + prevAct);
    //logic.keyboard(prevAct);
  //} else if (prevAct == 'z' && !message.equals('z')) {
    //logic.keyboard('x');
    prevAct = (char)command;
    logic.keyboard((char)command);
  //}
}

void draw() { 
  boolean tracking_skeleton = false;
   if (pause) {
      logic.stop();
   } 
   else {
     try {
       act();
     } catch(Exception e) {
       println("IOException while calling act(): " + e.getMessage());
       System.exit(1);
     }
   }
}

void keyPressed() {
    keyboard.setKey(key);
    if (key == 'p') {
        pause = !pause;
    }
}

void keyReleased() {
    keyboard.setKey(0);
}

void initSerial () {
  System.out.println("lost connection trying to reconnect to bugggy");
  try {
    serial = new Serial(this, Serial.list()[1], 115200);
    serialInited = true;
  } catch (RuntimeException e) {
    if (e.getMessage().contains("<init>")) {
      System.out.println("port in use, trying again later...");
      serialInited = false;
    }
  }
}