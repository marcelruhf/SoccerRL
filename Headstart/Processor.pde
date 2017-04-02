import java.util.Arrays;
import java.util.Observer;

/* process packets and update devices states */
class Processor implements Observer {
    private final List<Device> mDevices;
    private final PacketStore mPacketStore;

    Processor(final List<Device> devices, final PacketStore packetStore) {
        mDevices = devices;
        mPacketStore = packetStore;
        packetStore.addObserver(this);
    }

    /* new packet arrived, process it */ 
    public void update(final Observable o, final Object arg) {
        process();
    }

    private void process() {
        final Packet packet = mPacketStore.get();
        final int size = packet.getSize();
        final byte[] data = packet.getData();
        
        /* empty packet */
        if (size == 0) {
          println("lost connection");
            return;
        }

        /* get device */
        switch (data[0]) {
           /* case Device.PROXIMITY:
                Device device = findDevice(data[0], data[1]);
                if (device != null) {
                    Proximity proximity = (Proximity) device.get();
                    proximity.setDistance((data[2] & 0xFF) << 8 | (data[3] & 0xFF));
                }
                break;
                */
            case Device.DEBUG:
                println("DEBUG: " + new String(Arrays.copyOfRange(data, 2, size)));
                break;
            }
    }

    /* TODO use hashmap for better scalability */
    private Device findDevice(final int type, final int index) {
        for (Device device : mDevices) {
            if (device.getType() == type && device.getIndex() == index) {
                return device;
            }
        }
        return null;
    }
}