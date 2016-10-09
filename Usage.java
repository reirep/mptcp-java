import com.mptcp.Mptcp; 
import java.net.Socket; 
public class Usage{
    public static void main(String[] args){
        try{
            Socket s = new Socket("multipath-tcp.org", 80); 
            int[][] res = Mptcp.getSubflowList(s);
            System.out.println("Listing: "); 
            for(int[] line : res){
                System.out.println("-- " + line + " " + line[0] + " " + line[1]); 
            }    
        }
        catch(Exception e){
            System.out.println("Exception"); 
            e.printStackTrace(); 
        }
    }
}
