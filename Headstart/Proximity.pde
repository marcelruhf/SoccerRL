class Proximity extends Observable implements Protocable {
    private int mDistance;
       
    synchronized int getDistance() {
        return mDistance;
    }
    
    synchronized void setDistance(final int distance) {
        mDistance = distance;
    }
    
    byte[] bytes() {
        return null;
    }
}
