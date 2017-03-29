
import java.io.ByteArrayOutputStream;

class Device extends Observable implements Protocable, Observer {
    /* TODO create enum class for this */
    static final int MOTOR = 0;
    static final int DEBUG = 1;
    static final int PROXIMITY = 2;

    private final int mIndex;
    private final int mType;
    private final Protocable mDevice;

    Device(final int type, final int index, final Protocable device) {
        mType = type;
        mIndex = index;
        mDevice = device;

        Observable o = (Observable) mDevice;
        o.addObserver(this);
    }
    int getType() {
        return mType;
    }

    int getIndex() {
       return mIndex;
    }

    Protocable get() {
        return mDevice;
    }

    byte[] bytes() {
        ByteArrayOutputStream data = new ByteArrayOutputStream();

        data.write(byte(mType));
        data.write(byte(mIndex));
        byte[] buf = mDevice.bytes();
        data.write(buf, 0, buf.length);
        return data.toByteArray();
    }

    public void update(final Observable o, final Object arg) {
        setChanged();
    }

    public void clear() {
        clearChanged();
    }
}
