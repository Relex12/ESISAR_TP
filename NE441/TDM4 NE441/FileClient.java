import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;

public class FileClient 
{
	String ServerAddress = "127.0.0.1";
	int ServerPort = 5099;
	static int buf_size = 2048;

	public static void main(String[] args) throws Exception
	{
		FileClient FileClient = new FileClient();
		FileClient.execute(args);				
	}

	private void execute(String[] args) throws IOException
	{
		String inputName = args[0];
		String outputName = args[1];
		FileOutputStream fo = new FileOutputStream(outputName);

		Socket socket = new Socket();
		
		InetSocketAddress adrDest = new InetSocketAddress(ServerAddress, ServerPort);
		socket.connect(adrDest);
		
		byte[] bufE = new String(inputName).getBytes();
		OutputStream os = socket.getOutputStream();
		os.write(bufE);
		
		byte[] bufR = new byte[buf_size];
		InputStream is = socket.getInputStream();
		int lenBufR;
		while ((lenBufR= is.read(bufR)) != -1)			fo.write(bufR, 0, lenBufR);

		fo.close();
		socket.close();
		System.out.println("Arret du client .");
	}
}
