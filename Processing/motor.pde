class Motor extends Observable implements Protocable {
    /* TODO enum */
    static final int FORWARD = 0;
    static final int BACKWARD = 1;
    
    private int mDirection;
    private int mSpeed;
    private final int mMaxSpeed = 255;
    private int mTime;
    
    Motor() {
        mSpeed = 0;
        mDirection = FORWARD;
        mTime = millis();
    }
    
    int speed() {
        return mSpeed;
    }
    
    int direction() {
        return mDirection;
    }
  
    /* speed is in range <0.0, 1.0> */
    void forward(final float speed) {    
        speed(FORWARD, (int)((mMaxSpeed - 10) * min(max(speed, 0.0), 1.0)));
    }
 
    /* speed is in range <0.0, 1.0> */
    void backward(final float speed) {
        speed(BACKWARD, (int)(mMaxSpeed * min(max(speed, 0.0), 1.0)));
    }
  
    void stop() {
        forward(0);
    }
   
    byte[] bytes() {
        byte[] data = new byte[2];
        data[0] = byte(mDirection);
        data[1] = byte(mSpeed);
        return data;
    }
  
    private void speed(final int direction, int speed) {
        if (speed == mSpeed && direction == mDirection) {
            return;
        }
        
        if (mDirection != direction) {
            speed = 0;
            
            if (mSpeed < 10) {
                mDirection = direction;
            }
        }
        
        int new_speed = mSpeed;
            
        /* 2 steps per millisecond */
        final int new_time = millis();
     //   println("diff " + (new_time - mTime));
        if (speed > mSpeed) {
            new_speed = min(speed, mSpeed + min(new_time - mTime, 32));
        } else if (speed < mSpeed) {
            new_speed = max(speed, mSpeed - min(new_time - mTime, 32));
        }
        
        mTime = new_time;
        mSpeed = new_speed;
        changed();
    }
    
    private void changed() {
        setChanged();
        notifyObservers();
    }
}

