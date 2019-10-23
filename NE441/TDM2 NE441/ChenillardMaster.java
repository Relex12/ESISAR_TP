import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.util.ArrayList;

public class ChenillardMaster {

	public static void main(String[] args) throws Exception
	{
		ChenillardMaster ChenillardMaster = new ChenillardMaster();
		ChenillardMaster.execute();
		
	}
		
		

	private void execute() throws IOException, InterruptedException
	{
		
//		System.out.println("Demarrage du serveur ...");
				
		int myPort = 5099;
		
		@SuppressWarnings("resource")
		DatagramSocket socket = new DatagramSocket(null);
		socket.bind(new InetSocketAddress(myPort));

		
		boolean last = false;
		
		byte[] bufR = new byte[2048];
		DatagramPacket dpR = new DatagramPacket(bufR, bufR.length);
		String message = new String();
		ArrayList<SocketAddress> listeAddrClient = new ArrayList<SocketAddress>();
		ArrayList<Integer> listePortClient = new ArrayList<Integer>();


		while (!last)
		{
			socket.receive(dpR);
			listeAddrClient.add(socket.getRemoteSocketAddress());
			listePortClient.add(socket.getPort());
			message = new String(bufR, dpR.getOffset(), dpR.getLength());
			if (message.equals("last") ) 	last = true;			
		}
		
		int nbClient = listeAddrClient.size();
		
		byte[] bufGo= new String("go").getBytes();
		byte[] bufStop= new String("stop").getBytes();

		int n = 0;
		
		while (true)
		{
			DatagramPacket dpGo = new DatagramPacket(bufGo, bufGo.length, listePortClient.get(n%nbClient),listeAddrClient.get(n%nbClient));
			socket.send(dpGo);
			Thread.sleep(1000);
			
			DatagramPacket dpStop = new DatagramPacket(bufStop, bufStop.length, listePortClient.get(n%nbClient),listeAddrClient.get(n%nbClient));
			socket.send(dpStop);
			n++;
		}
				
//		socket.close();		// never reached
	}
	
	
}
