import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class FileServer 
{
	int ServerPort = 5099;
	static int buf_size = 2048;

	public static void main(String[] args) throws Exception
	{
		FileServer FileServer = new FileServer();
		FileServer.execute();
		
	}

	private void execute() throws IOException, InterruptedException
	{
		ServerSocket socketEcoute = new ServerSocket();
		socketEcoute.bind(new InetSocketAddress(ServerPort));

		Socket socketConnexion = socketEcoute.accept();
		
/*		System.out.println("Un client est connecté");
		System.out.println("IP:"+socketConnexion.getInetAddress());
		System.out.println("Port:"+socketConnexion.getPort());
*/		
		byte[] bufR = new byte[buf_size];
		InputStream is = socketConnexion.getInputStream();
		int lenBufR = is.read(bufR);
		String inputName = null;
		if (lenBufR!=-1)
		{
			inputName = new String(bufR, 0 , lenBufR);
		}
		
		FileInputStream fi = new FileInputStream(inputName);
		byte[] bufE = new byte[buf_size];
		int size;
		OutputStream os = socketConnexion.getOutputStream();
		while ((size = fi.read(bufE)) != -1)		
		{
			os.write(bufE, 0, size);			
			Thread.sleep(20);
		}
			
		fi.close();
		socketConnexion.close();
		socketEcoute.close();
		System.out.println("Arret du serveur .");
	}
		
}
