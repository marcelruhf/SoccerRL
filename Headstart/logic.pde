import java.util.ArrayList;
import java.util.List;

class Logic {
    private final MyClient mClient;
    private final Protocol mProtocol;
    private final Vehicle mVehicle;
    private List<Device> devices;
    private final Motor mMotor_a;
    private final Motor mMotor_b;
    // private final Proximity mProximity;
    private float speed;
    // private final int distance_threshold;

    Logic( final MyClient client, final Serial serial) {
        mClient = client;
        final PacketStore packetStore = new PacketStore(100);
        mProtocol = new Protocol(serial, packetStore);

        devices = new ArrayList<Device>();

        // create devices
        mMotor_a = new Motor();
        mMotor_b = new Motor();
        // mProximity = new Proximity();

        /* add devices to list */
        devices.add(new Device(Device.MOTOR, 0, (Protocable) mMotor_a));
        devices.add(new Device(Device.MOTOR, 1, (Protocable) mMotor_b));
        // devices.add(new Device(Device.PROXIMITY, 0, (Protocable) mProximity));

        // create processor for processing packets
        final Processor processor = new Processor(devices, packetStore);

        // create vehicle, consisting from two motors
        mVehicle = new Vehicle(mMotor_a, mMotor_b);

        speed = 255;

        /* higher value, closer to obstacle
         * if too close, it is inverted
         */
         // distance_threshold = 400;
    }

    void setSpeed(float newSpeed) {
        speed = newSpeed;
    }

    /* main loop for keyboard */
    /* TODO two keys pressed at once do not work */
    void client() {
        /*
        mClient.getAction() - return action
        mSkeleton.getRightHand() - return vec(x, y, z)
        mVehicle.stop() - stop vehicle
        */

        switch (mClient.getAction()) {
        case "FORWARD":
            mMotor_a.forward(speed);
            mMotor_b.forward(speed);
        case "LEFT":
            mMotor_a.backward(speed);
            mMotor_b.forward(speed);
            break;
        case "RIGHT":
            mMotor_a.forward(speed);
            mMotor_b.backward(speed);
            break;
        case "BACKWARD":
            mMotor_a.backward(speed);
            mMotor_b.backward(speed);
            break;
        case "SPEEDUP":
            speed += 0.1;
            break;
        case "SLOWDOWN":
            speed -= 0.1;
            break;
        case "STOP":
            mVehicle.stop();
        default:
            mVehicle.stop();
        }
    }

    void stop() {
        mVehicle.stop();
        postExecute();
    }

    private void preExecute() {}

    private void postExecute() {
        /* send devices states to buggy */
        for (int i = 0; i < 2; i++) {
            if (devices.get(i).hasChanged()) {
                mProtocol.send(devices.get(i));
                devices.get(i).clear();
            }
        }

        // 8 ms per frame
        delay(8);
    }
}