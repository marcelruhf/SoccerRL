import java.util.concurrent.ArrayBlockingQueue;
import java.util.Observable;
import java.util.Queue;

/* store packets in queue, thread-safe */
class PacketStore extends Observable {
    final int mCapacity;
    Queue<Packet> mPackets;

    PacketStore(final int capacity) {
        mCapacity = capacity;
        mPackets = new ArrayBlockingQueue<Packet>(mCapacity);
    }

    synchronized void add(final Packet packet) {
        mPackets.add(packet);
        changed();
    }

    synchronized Packet get() {
        return mPackets.poll();
    }

    private void changed() {
        setChanged();
        notifyObservers();
    }
}