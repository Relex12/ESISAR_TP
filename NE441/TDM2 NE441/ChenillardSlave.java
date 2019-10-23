import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;

public class ChenillardSlave {

	public static void main(String[] args) throws Exception
	{
		ChenillardSlave ChenillardSlave = new ChenillardSlave();
		ChenillardSlave.execute();
				
	}

	private void execute() throws IOException
	{
		DatagramSocket socket = new DatagramSocket();
		
		InetSocketAddress adrDest = new InetSocketAddress("192.168.130.162", 5099);
		byte[] bufF = new String("first").getBytes();
		byte[] bufL = new String("last").getBytes();
		DatagramPacket dpF = new DatagramPacket(bufF, bufF.length, adrDest);
		DatagramPacket dpL = new DatagramPacket(bufL, bufL.length, adrDest);
		socket.send(dpF);

		byte[] bufR = new byte[2048];
		DatagramPacket dpR = new DatagramPacket(bufR, bufR.length);
		String reponse = new String();

		while (true)
		{
			socket.receive(dpR);
			reponse = new String(bufR, dpR.getOffset(), dpR.getLength());
			if (reponse.equals("go"))
				//lancer
			socket.receive(dpR);
			reponse = new String(bufR, dpR.getOffset(), dpR.getLength());
			if (reponse.equals("stop"))
				//arreter				
		}
		
		socket.close();
		System.out.println("Arret du client .");
	}

}
