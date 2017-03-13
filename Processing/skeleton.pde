class Skeleton {
    PVector mTorso;
    PVector mRightHand;
    PVector mLeftHand;
    
    Skeleton() {
        reset();
    }
    
    void reset() {
        /* initialise vectors, avoid null pointer exceptions */
        mTorso = new PVector();
        mRightHand = new PVector();
        mLeftHand = new PVector();
    }
 
    PVector getTorso() {
        return mTorso.get();
    }
    
    void setTorso(final PVector vec) {
        mTorso = vec.get();
    }
    
    PVector getRightHand() {
        return mRightHand.get();
    }
    
    void setRightHand(final PVector vec) {
        mRightHand = vec.get();
    }
    
    PVector getLeftHand() {
        return mLeftHand.get();
    }
    
    void setLeftHand(final PVector vec) {
        mLeftHand = vec.get();
    }
}
