import com.mptcp.Mptcp; 
import java.net.*;
import java.io.*;
public class Usage{
    public static void main(String[] args){
        try{
            Socket s = new Socket("10.0.0.2", 80); 
            int[][] res = Mptcp.getSubflowList(s);
            System.out.println("Listing: ");
          for(int[] line : res){
                System.out.println("-- id:" + line[0] + " slave_sk:" + line[1] + " fully established:" + line[2] +
		" attached: "+ line[3]+" low_prio: "+line[4]+" pre_established: "+line[5]);
            }

	PrintWriter pred = new PrintWriter(new BufferedWriter(new OutputStreamWriter(s.getOutputStream())),true);    
	pred.println("Hello World");
	Mptcp.HostTuple h = new Mptcp.HostTuple("10.1.0.1", 80);
	Mptcp.HostTuple d = new Mptcp.HostTuple("10.1.0.2", 80);
	int id= Mptcp.openSubflow(s, h, d, 1);
	pred.println("Hello World1");
	int[][] res1 = Mptcp.getSubflowList(s);
        System.out.println("Listing: ");
        for(int[] line : res1){
                System.out.println("-- id:" + line[0] + " slave_sk:" + line[1] + " fully established:" + line[2] +
                " attached: "+ line[3]+" low_prio: "+line[4]+" pre_established: "+line[5]);
            }
	Mptcp.HostTuple res2[] = Mptcp.getSubflowTuple(s, id);
        System.out.println(res2[0] + ":::: " + res2[1]);  

	Mptcp.closeSubflow(s, id, 1);
	for (int i = 0; i < 10; i++) {
		pred.println("Hello World2 "+"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Proin posuere tellus tortor, in convallis magna convallis nec. Morbi ac diam urna. Fusce ut risus tincidunt, faucibus ante et, rutrum velit. Nam rutrum, mi et commodo dictum, mi lacus varius nulla, et porta purus augue at justo. Integer sollicitudin enim sit amet commodo varius. Mauris eleifend finibus velit, id elementum lectus eleifend vitae. Nunc hendrerit, felis et dignissim dapibus, justo felis ultrices sem, in imperdiet massa elit pellentesque lacus. Maecenas faucibus hendrerit felis, ac porttitor enim tempus a. Ut id rhoncus lectus, aliquam blandit urna. Donec condimentum dictum gravida. Mauris vitae neque vel eros sollicitudin vulputate sit amet facilisis dui. Fusce vulputate quis sapien at hendrerit. Proin maximus consectetur imperdiet. Duis nulla nibh, auctor a pellentesque eu, pulvinar vel elit. Donec dui felis, ultricies quis sollicitudin eget, facilisis et mi. Morbi ut dui at erat imperdiet sollicitudin. ");
	}
	System.out.println("Listing: ");
	res1 = Mptcp.getSubflowList(s);
        for(int[] line : res1){
                System.out.println("-- id:" + line[0] + " slave_sk:" + line[1] + " fully established:" + line[2] +
                " attached: "+ line[3]+" low_prio: "+line[4]+" pre_established: "+line[5]);
            }

	//dest '10.1.0.2' sourc '10.1.0.1'
        }
        catch(Exception e){
            System.out.println("Exception"); 
            e.printStackTrace(); 
        }
    }
}
