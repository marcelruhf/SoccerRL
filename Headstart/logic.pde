import java.util.ArrayList;
import java.util.List;
import processing.net.*;

class Logic {
  
    int counter = 0;
 
    private final Protocol mProtocol;
    private final Vehicle mVehicle;
    private List<Device> devices;
    private final Motor mMotor_a;
    private final Motor mMotor_b;
    private final Keyboard mKeyboard;
    private float speed;
 
    Logic( final Keyboard keyboard, final Serial serial) {
      
        mKeyboard = keyboard;
        final PacketStore packetStore = new PacketStore(100); 
        mProtocol = new Protocol(serial, packetStore);

        devices = new ArrayList<Device>();

        /* create devices */
        mMotor_a = new Motor();
        mMotor_b = new Motor();
      
        /* add devices to list */
        devices.add(new Device(Device.MOTOR, 0, (Protocable) mMotor_a));
        devices.add(new Device(Device.MOTOR, 1, (Protocable) mMotor_b));
  
        /* create processor for processing packets */
        final Processor processor = new Processor(devices, packetStore);

        /* create vehicle, consisting from two motors */
        mVehicle = new Vehicle(mMotor_a, mMotor_b);
        
        speed = 20;
    }
      

    /* main loop for keyboard */
    /* TODO two keys pressed at once do not work */
    void keyboard(char takeAction) {
        /* mKeyboard.getKey() - return pressed key */
        /* mSkeleton.getRightHand() - return vec(x, y, z) */
        /* mVehicle.stop() - stop vehicle */
        
        switch (takeAction) {
        case 'w':
            mMotor_a.forward(speed);
            mMotor_b.forward(speed);
            break;
        case 'a':
            mMotor_a.backward(speed);
            mMotor_b.forward(speed);
            break;
        case 'd':
            mMotor_a.forward(speed);
            mMotor_b.backward(speed);
            break;
        case 's':
            speed = 50;
            mMotor_a.backward(speed);
            mMotor_b.backward(speed);
            break;
        case 'r':
            speed += 0.1;
            break;
        case 'f':
            speed -= 0.1;
            break;
        case 'z':
            mVehicle.stop();
        case 'x':
            mVehicle.setSpeed(0);
        default:
            mVehicle.stop();
        }
        
        postExecute();
    }
    
  

    void stop() {
        mVehicle.stop();
        postExecute();
    }

    private void preExecute() {
    }

    private void postExecute() {
        /* send devices states to buggy */
        for (int i = 0; i < 2; i++) {
            if (devices.get(i).hasChanged()) {
                mProtocol.send(devices.get(i));
                devices.get(i).clear();
            }
            
        }

        /* 8 ms per frame */
        delay(8);

    }
}