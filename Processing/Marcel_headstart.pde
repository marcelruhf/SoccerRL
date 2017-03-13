import processing.serial.*;
import processing.net.*;

Serial serial;
Logic logic;

Keyboard keyboard;
boolean pause = false;
PVector vec = new PVector();
boolean serialInited = false;
int[] userID;
int serialCheckCounter = 0;
boolean wasRunning = false;

void setup() {
    /* print all serial ports */
    println(serial.list());

    /* open serial port */
    //serial = new Serial(this, serial.list()[0], 115200);
    //serial = new Serial(this, Serial.list()[0], 115200);
    while(!serialInited) {
        initSerial();
    }

   // exitHandler();\

   keyboard = new Keyboard();
   logic = new Logic( keyboard, serial);

   background(200, 0, 0);

   /* stroke for drawing lines in skeleton */
   stroke(0, 0, 255);
   strokeWeight(3);
   smooth();
}

void draw() {

    // if(wasRunning && serial.available() <= 0) {
    //   System.out.println("lost");
    // }

    boolean tracking_skeleton = false;

    /* to pause vehicle press key 'P' */
    if (pause) {
        logic.stop();
    }
    else {
        logic.keyboard();
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
