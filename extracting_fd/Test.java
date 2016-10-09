import java.net.Socket; 
import java.io.FileInputStream; 
import sun.misc.SharedSecrets; 

class Test{
    public static void main(String[] args){
        try{
        System.out.println("coucou"); 
        Socket s = new Socket("multipath-tcp.org", 80); 
        System.out.println(
            SharedSecrets.getJavaIOFileDescriptorAccess().get(
                ((FileInputStream)s.getInputStream()).getFD()
            )); 
        }
        catch(Exception e){
            System.err.println("error"); 
        }
    }
}
