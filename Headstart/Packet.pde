class Packet {
    private final int mVersion;
    private final int mCounter;
    private final int mSize;
    private final byte[] mData;
 
    Packet(final int version, final int counter, final int size, final byte[] data) {
        mVersion = version;
        mCounter = counter;
        mSize = size;
        mData = data;
    }
    
    int getCounter() {
        return mCounter;
    }
    
    int getSize() {
        return mSize;
    }
    
    byte[] getData() {
        return mData;
    }
}
