
import java.io.FileInputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class ViewerImage
{
	String Address = "127.0.0.1";
	int port = 8000;

	public static void main(String[] args) throws Exception
	{
		ViewerImage ViewerImage = new ViewerImage();
		ViewerImage.execute(true);
	}
		
		

	private void execute(boolean bv) throws IOException, InterruptedException
	{
		if (bv)		System.out.println("Demarrage du serveur ...");
		ServerSocket socketEcoute = new ServerSocket();
		socketEcoute.bind(new InetSocketAddress(port));
		if (bv)		System.out.println("Attente de la connexion du client ...");
		Socket socketConnexion = socketEcoute.accept();
		
		if (bv)		System.out.println("Un client est connecté\tIP:"+socketConnexion.getInetAddress()+"\tPort:"+socketConnexion.getPort());
		
		
		byte[] bufR = new byte[2048];
		java.io.InputStream is = socketConnexion.getInputStream();
		int lenBufR = is.read(bufR);
		if (lenBufR!=-1)
		{
			String message = new String(bufR, 0 , lenBufR);
			if (bv)		System.out.println("Message recu \n-------\n"+message + "-------");
		}
		
		String status = new String ("HTTP/1.1 200 OK\r\n"
				+ "Connection: close\\r\n"
				+ "Content-Type: multipart/x-mixed-replace;boundary=ipcamera"); //\r\n\r\n
				
		byte[] bufE = status.getBytes();
		OutputStream os = socketConnexion.getOutputStream();
		os.write(bufE);
		if (bv)		System.out.println("Message envoye\n-------\n" + status + "-------");
		
		int[] taille = {94969, 37800, 704356, 109381, 121218, 4096};
		String[] nom = {"image1.jpg", "image2.jpg", "image3.jpg", "image4.jpg", "image5.jpg"};
		

		for (int i = 0; i < 5; i++)
		{
			
			String header = new String("\r\n\r\n--ipcamera\r\n" 
					+	"Content-Type: image/jpeg\r\n" 
					+ 	"Content-Length: " + taille[i] + "\r\n\r\n");
			
			byte[] bufE2 = header.getBytes();
			os.write(bufE2);

//			FileInputStream fis = new FileInputStream("image" + i + ".jpg");
			FileInputStream fis = new FileInputStream(nom[i]);
			byte[] bufE3 = new byte[taille[i]];
			int len = fis.read(bufE3);
			os.write(bufE3);
			fis.close();			
			Thread.sleep(1000);
			if (bv)		System.out.println("Message envoye\n-------\n" + header + "-------\n taille lue : " + len);
		}
		
		
		
		
		socketConnexion.close();
		socketEcoute.close();
		if (bv)		System.out.println("Arret du serveur");
	}
		
}
