import processing.serial.*;
import processing.net.*;

Serial serial;
Logic logic;

MyClient client;
Client rClient;
boolean pause = false;
PVector vec = new PVector();
boolean serialInited = false;
int[] userID;
int serialCheckCounter = 0;
boolean wasRunning = false;

void setup() {
    // print all serial ports
    println(serial.list());

    // open serial port
    while(!serialInited) {
        initSerial();
    }

    // exitHandler();

    client = new MyClient();
    rClient = new Client(this, "localhost", 2323);
    client.setClient(rClient);
    logic = new Logic(client, serial);

    background(200, 0, 0);

    // stroke for drawing lines in skeleton
    stroke(0, 0, 255);
    strokeWeight(3);
    smooth();
}

void draw() {
    boolean tracking_skeleton = false;
    logic.client();
}

void initSerial () {
    System.out.println("lost connection trying to reconnect to buggy");
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