import java.io.IOException;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.net.Socket;

public class ClientTCP
{
	String serverAddr = "127.0.0.1";
	int serverPort = 7000;
	
	public static void main(String[] args) throws Exception
	{
		ClientTCP clientTCP = new ClientTCP();
		clientTCP.execute();				
	}
	
	
	int log2arg (int a, int b)
	{
		return (int) (Math.log(b)/Math.log(a));
	}
	
	private void execute() throws IOException
	{
//		System.out.println("Demarrage du client ...");
		Socket socket = new Socket();
		
		InetSocketAddress adrDest = new InetSocketAddress(serverAddr, serverPort);
		socket.connect(adrDest);		
		
		byte[] bufR = new byte[2048];
		InputStream is = socket.getInputStream();
		int lenBufR = 0;
		
		int taille_tot;
		int taille_lue;
		int fuzzing;
		int reel;
		int decale;
		
		int nbimage = 0;
		String reponse = "";
		
		while (nbimage < 50)
		{
			lenBufR += is.read(bufR);			
			if (lenBufR!=-1)
			{
				reponse = new String(bufR, 0, lenBufR);
				System.out.println("nouvelle lecture");
//				System.out.println("réponse =" + reponse);
//				System.out.println("taille = "+lenBufR);
			}
			taille_tot = 0;
			taille_lue = -1;
			fuzzing = 0;
			reel = 0;
			
			taille_tot = Integer.valueOf(reponse.split(" ")[0]);
			
			while (taille_lue < taille_tot)
			{
				fuzzing = Integer.valueOf(reponse.split(" ")[1]);
				reel = Integer.valueOf(reponse.split(" ")[2]);
				
				System.out.println("taille totale : " + taille_tot +"\tfuzzing : " + fuzzing + "\treel : " + reel);
				
				decale = fuzzing + reel + 6 + (log2arg (10, taille_tot) + log2arg (10, fuzzing) + log2arg(10, reel));
				System.out.println("decalage : " + decale);
				
				
				String voir = new String(bufR, decale, lenBufR-decale);
				System.out.println(voir);
				
				
			}

			
		}
		
		
		
		
		
		
		
		socket.close();
		System.out.println("Arret du client .");
	}
}
