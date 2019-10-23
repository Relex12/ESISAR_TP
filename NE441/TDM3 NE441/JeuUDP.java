package tcp;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetSocketAddress;

public class JeuUDP {

	public static void main(String[] args) throws Exception
	{
		JeuUDP JeuUDP = new JeuUDP();
		for (int i = 0; i < 1000000; i++)		JeuUDP.execute();				
	}
								
	/**
	 * Le client cree une socket, envoie un message au serveur
	 * et attend la reponse 
	 * 
	 */
	private void execute() throws IOException
	{
		String IPServer = "192.168.130.150";
		int PortServer = 7001;
		

		DatagramSocket socket = new DatagramSocket();
		
		// Creation et envoi du message
		InetSocketAddress adrDest = new InetSocketAddress(IPServer, PortServer);
		byte[] bufJOUER = new String("JOUER\n").getBytes();
		DatagramPacket dpE = new DatagramPacket(bufJOUER, bufJOUER.length, adrDest);
		socket.send(dpE);
//		System.out.println("Message envoye");
		
		// Attente de la reponse 
		byte[] bufRS = new byte[2048];
		DatagramPacket dpR = new DatagramPacket(bufRS, bufRS.length);
		socket.receive(dpR);
		String reponse = new String(bufRS, dpR.getOffset(), dpR.getLength()).replace('+', ':').replace('=', ':');		
//		System.out.println("Reponse recue = "+reponse);
		
		

//		reponse.replace('+', ':');
//		reponse.replace('=', ':');
		
		String[] listeChaine = reponse.split(":");
		
//		System.out.println(listeChaine[0] + " " + listeChaine[1] + " " + listeChaine[2]);
		
		int op1 = Integer.valueOf(listeChaine[1]);
		int op2 = Integer.valueOf(listeChaine[2]);
		int res = op1 + op2;
		String newChaine = listeChaine[0].replace('Q','R');
		
		
		
		
		byte[] bufRC = new String(newChaine + ":" + res).getBytes();
		DatagramPacket dpE2 = new DatagramPacket(bufRC, bufRC.length, adrDest);
		socket.send(dpE2);
//		System.out.println("Message envoye");
		
		
		// Fermeture de la socket
		socket.close();
//		System.out.println("Arret du client .");

		
		
	}
}
