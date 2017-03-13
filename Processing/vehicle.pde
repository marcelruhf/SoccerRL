class Vehicle {
  final Motor mMotorLeft;
  final Motor mMotorRight;
  float mSpeed = 1.0;
  
  Vehicle(final Motor motorLeft, final Motor motorRight) {
    mMotorLeft = motorLeft;
    mMotorRight = motorRight;
  }
  
  void setSpeed(final float speed) {
    mSpeed = speed;
  }
  
  void left() {
    mMotorLeft.backward(mSpeed);
    mMotorRight.forward(mSpeed);
  }
 
  void right() {
    mMotorRight.backward(mSpeed);
    mMotorLeft.forward(mSpeed);
  }
  
  void forward() {
    mMotorRight.forward(mSpeed);
    mMotorLeft.forward(mSpeed);
  }
  
  void backward() {
    mMotorRight.backward(mSpeed);
    mMotorLeft.backward(mSpeed);
  }
  
  void stop() {
    mMotorRight.stop();
    mMotorLeft.stop(); 
  }
}
