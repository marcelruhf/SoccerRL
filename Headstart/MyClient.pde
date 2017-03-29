import processing.net.*;

class MyClient {
    private String mAction;
    private Client mClient;

    public void setClient(Client client) {
        mClient = client;
    }
   
    public String getAction() {
        String message = mClient.readString();
        if (message != null) {
            System.out.printf("message: %s\n", message);
            Double value = Double.parseDouble(message);
            int intValue = value.intValue();
            if (intValue > 0) {
                mAction = "RIGHT";
            } else if (intValue < 0) {
                mAction = "LEFT";
            } else {
                mAction = "PAUSE";
            }
            return mAction;
        } else {
            return "STOP";
        }
    }
}