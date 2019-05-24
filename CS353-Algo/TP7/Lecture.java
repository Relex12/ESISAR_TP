import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class Lecture {
	
	private static String cheminTest = "/home/userir/Downloads/test-url.txt";

	
	public static void slow (String chemin) throws IOException { 
		long start = System.currentTimeMillis();
		SeekableByteChannel sbc = Files.newByteChannel(Paths.get(chemin),
		StandardOpenOption.READ);
		int count =0;
		
		// Lecture des 50 premiers octets du fichier
		ByteBuffer buf = ByteBuffer.allocate(50);
		int ret = sbc.read(buf);

		while(ret>0)
		{
			// Conversion des 50 octets en une chaine de caractères
			String str = new String(buf.array());
			// Suppression des espaces en fin de chaine
			str = str.trim();
			// Affichage de la chaine de caractères sur la console
//			System.out.println(str);
			count++;
			// Lecture des 50 octets suivants
			buf.clear();
			ret = sbc.read(buf);
		}

		System.out.println("Nombre d'URL dans le fichier ="+count);
		System.out.println("Elapsed Time="+(System.currentTimeMillis()-start)/1000+"s");
		// Fermeture du fichier
		sbc.close();
	}

	public static void quick (String chemin) throws IOException { 
		
		long start = System.currentTimeMillis();
		SeekableByteChannel sbc = Files.newByteChannel(Paths.get(chemin),
		StandardOpenOption.READ);
		int count =0;
		
		// Lecture des 50 000 premiers octets du fichier
		ByteBuffer buf = ByteBuffer.allocate(50_000);
		int ret = sbc.read(buf);
		
		while(ret>0)
		{
			// Conversion des 50_0000 octets en 1000 chaine de caractères
			for (int i = 0; i < 1000; i++)
			{
				String str = new String(buf.array(),i*50,50);
				// Suppression des espaces en fin de chaine
				str = str.trim();
				// Affichage de la chaine de caractères sur la console
				// System.out.println(str);
				count++;
			}
	
				// Lecture des 50_000 octets suivants
			buf.clear();
			ret = sbc.read(buf);
		}
		
		System.out.println("Nombre d'URL dans le fichier ="+count);
		System.out.println("Elapsed Time="+(System.currentTimeMillis()-start)/1000+"s");
		// Fermeture du fichier
		sbc.close();	
	}
	
/*	TEST DES FONCTIONS DE LECTURE
*/ 	public static void main(String[] args) {
		try {
			slow(cheminTest);
			quick(cheminTest);
		} catch (IOException e) {
			// TODO: handle exception
			e.printStackTrace();
		}
	}

}
