import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class CopieFichier 
{
	static int buf_size = 4096;
	// files must be in the project directory in eclipse-workspace
	// filenames must be given as argument
	public static void main(String[] args) throws IOException 
	{
		long n = System.currentTimeMillis();
		String inputName = args[0];
		String outputName = args[1];
		FileInputStream fi = new FileInputStream(inputName);
		FileOutputStream fo = new FileOutputStream(outputName);
		byte[] b = new byte[buf_size];
		int size;
		while ((size = fi.read(b)) != -1)	fo.write(b, 0, size);
		fi.close();
		fo.close();
		System.out.println((System.currentTimeMillis() - n) / 1000);;
	}
}
