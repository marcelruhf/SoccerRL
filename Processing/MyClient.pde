import processing.net.*;

class Keyboard {
    private bool initialCommandSent;
    private String mAction;
    private Client mClient;

    public void startServer() {
        mClient = new Client(this, "localhost", 2323);
    }
   
    public String getAction() {
        if (!initialCommandSent) {
            mClient.write("READY");
            initialCommandSent = !initialCommandSent;
        }
        mAction = mClient.readString();
        return mAction;
    }
}
