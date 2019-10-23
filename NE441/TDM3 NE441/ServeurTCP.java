package tcp;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;

/**
 * Serveur basique TCP
 */
public class ServeurTCP
{

	public static void main(String[] args) throws Exception
	{
		ServeurTCP serveurTCP = new ServeurTCP();
		serveurTCP.execute();
		
	}
		
		

	private void execute() throws IOException
	{
		//
		System.out.println("Demarrage du serveur ...");
		
		// Le serveur se declare aupres de la couche transport
		// sur le port 5099	
		ServerSocket socketEcoute = new ServerSocket();
		socketEcoute.bind(new InetSocketAddress(5099));

		// Permet de compter le nombre de clients servis
		int nbClient = 1;
		
		while(nbClient<4)
		{
			// Attente de la connexion d'un client
			System.out.println("Attente de la connexion du client "+nbClient+"...");
			Socket socketConnexion = socketEcoute.accept();
			
			// Un client s'est connecte, le serveur lit le message envoye par le le client (sans garantie de lire tout le message)
			byte[] bufR = new byte[2048];
			InputStream is = socketConnexion.getInputStream();
			int lenBufR = is.read(bufR);
			String message = new String(bufR, 0 , lenBufR);
			System.out.println("Message recu = "+message);
			if (message.equals("stop")==true)
			{
				break;
			}
			System.out.println("adresse IP " + socketConnexion.getInetAddress() + ", port " + socketConnexion.getPort());
			
			// Emission d'un message en retour
			byte[] bufE = new String("ok").getBytes();
			OutputStream os = socketConnexion.getOutputStream();
			os.write(bufE);
			System.out.println("Message envoye = ok");
			
			// Fermeture de la socket de connexion
			socketConnexion.close();
			
			// On incremente le nombre de clients servis
			nbClient++;
		}
		
		socketEcoute.close();
		System.out.println("Arret du serveur .");
	}
		
}
