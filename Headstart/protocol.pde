import java.util.Arrays;


class Protocol {
    private static final int MOTOR = 0;
    private static final int DEBUG = 1;
    private final Serial mSerial;
    private final Reader mReader;
    private final PacketStore mPacketStore;
    private static final int MAXWAIT = 10000;  
    
    static final int version = 0;
    private int mCounter;
  
    Protocol (final Serial serial, PacketStore packetStore) {
        mCounter = 0;
        mSerial = serial;
        mPacketStore = packetStore;
        
        mReader = new Reader();
        mReader.start();     
    }

    void send(final Protocable device) {
        ByteArrayOutputStream data = new ByteArrayOutputStream();
                
        /* construct header */
        for (int i = 0; i < 2; i++) {
            data.write(255);
        }
        data.write(version);
        
        /* counter, <0, 255> */
        data.write(mCounter);
        mCounter = ++mCounter % 255;
        
        /* Data size */
        final byte[] buf = device.bytes(); 
        data.write(buf.length);
        
        /* Device */
        data.write(buf, 0, buf.length);
     
        serial.write(data.toByteArray());
         
    }

    
    Packet receive() {
      
      int version = 0;
      int counter = 0;
      int size = 0;
      byte[] data = new byte[1];
      
     
        /* wait for beginning marker */
        int c = 0;
        while (c < 2) {
            _wait(1);
           
            if (mSerial.read() == 255) {
              c++;
            }
             
        }
                                          
        /* wait for header */
        _wait(3);
        
        /* read header */
        
       
    
          version = mSerial.read();
          counter = mSerial.read();
          size = mSerial.read();
     
        
        if(size <=0 ) {
            serialInited = false;
            println("size = 0");
            return new Packet(0, 0, 0, new byte[1]);
        }
         /* wait for rest of packet */
         
          data = new byte[size];
        
          for (int i = 0; i < size; i++) {
          
         /*   int waitCounter = 0;
            while (mSerial.available() < 1 & waitCounter < MAXWAIT) {
              waitCounter++;
            }
            println("1: waited: ", waitCounter);
            if(waitCounter >= MAXWAIT) {
             
              println("max counter");
          //     serialInited = false;
              break;
            }
            */
          int waitCounter = 0;
          while (mSerial.available() < 1 && waitCounter < MAXWAIT) { 
         //  while (mSerial.available() < 1);
             waitCounter++;
           }
          // println("1: waited: ", waitCounter);
          if(waitCounter >= MAXWAIT) {
             println("can't wait any longer : No response");
          return new Packet(0, 0, 0, new byte[1]);
           
          }
         
                 data[i] = byte(mSerial.read());  
          
        
        }
      
        final Packet packet = new Packet(version, counter, size, data);
        wasRunning = true;
        
        return packet;
    }
    
    private void _wait(final int count) {
       
        while (mSerial.available() < count) {
            //  println("Waiting for serial");
              try {
                Thread.sleep(1);
              } catch (InterruptedException e) {
                  println("interupt");
                  Thread.currentThread().interrupt();
              }
            
         
            
        }
    }
    
    private class Reader extends Thread {        
        void run() {
            while (true) {
                mPacketStore.add(receive());
            }
        }        
    }
    
   
}


