import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.security.*;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class Usage
{

	private static String cheminValide = "/home/userir/Downloads/valides-urls.txt";
	private static String cheminInfect = "/home/userir/Downloads/infected-urls.txt";
	private static String cheminTest = "/home/userir/Downloads/test-url.txt";
	private static String cheminFichier = "/home/userir/Downloads/BigFile.txt";
	private static int urlSize = 50;													// taille d'une URL en caractères
	private static long sizeFile = 1_000_000_000L;							// mettre 100_000_000_000
	private static long nbLinesFile = sizeFile / (2 * urlSize);

	public static boolean searchBigFile (String url) throws IOException
	{
		url = url.trim();
		Scanner scanner = new Scanner(new File(cheminFichier));
		String line;
		while (scanner.hasNextLine())
		{
			line = scanner.nextLine();
			if (url.equals(line.trim()))
			{
				scanner.close();
				return true;
			}
		}
		scanner.close();
		return false;
	}

	public static void addBigFile(String url) throws IOException
	{
		List<String> line = Arrays.asList(url);
		Path fichier = Paths.get(cheminFichier);
		//Pour écrire à la suite du fichier, il faut utiliser la commande suivante
		Files.write(fichier, line, StandardOpenOption.APPEND);
	}

	public static void createBigFile() throws IOException 							// créé le fichier de 100 Giga
	{
		System.out.println("Création du gros fichier");
		long start = System.currentTimeMillis();

		SeekableByteChannel file = Files.newByteChannel(Paths.get(cheminInfect), StandardOpenOption.READ);
		ByteBuffer buf = ByteBuffer.allocate(50_000);
		int ret = file.read(buf);
		String str;

		int count = 0;

		while(ret>0)
		{
			for (int i = 0; i < 1000; i++)
			{
				str = new String(buf.array(),i*50,50);
				str = str.trim();
				addBigFile(str);
				count ++;
				if (count % (200_000_000 / 1000) == 0)
					System.out.println(count / (200_000_000 / 1000) + "%");
			}
			buf.clear();
			ret = file.read(buf);
		}
		file.close();
		System.out.println("Fin de création");
		float time = (System.currentTimeMillis()-start)/1000;
		System.out.println("Temps de création = "+ time +"s");
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////

	public static boolean newSearchBigFile(String url) throws IOException, NoSuchAlgorithmException
	{
		byte[] byteChaine = url.getBytes("UTF-8");
		MessageDigest md = MessageDigest.getInstance("MD5");
		byte[] hash = md.digest(byteChaine);
		//
		long posAbs = 0;
		for (byte value : hash){
		    posAbs <<= 8; 										//On décale de 8 bits vers la gauche
		    posAbs += value;
		}
		if(posAbs < 0)posAbs = - posAbs;
		long pos =  posAbs % nbLinesFile;
		pos = pos * 50;
		//System.out.println("position " + pos);

		SeekableByteChannel sbc = Files.newByteChannel(Paths.get(cheminFichier), StandardOpenOption.READ);
		sbc.position(pos);											// On se déplace à la position 1000 dans le fichier
		ByteBuffer buf = ByteBuffer.allocate(urlSize);				// Lecture de 50 octets
		sbc.read(buf);
		String str = new String(buf.array());						// Conversion des 50 octets en une chaine de caractères
		str = str.trim();											// Suppression des espaces en fin de chaine

		//System.out.println("str " + str);

		while ( !str.equals(url) )
		{
			pos = (pos + urlSize) % sizeFile;						// Décalage d'une URL
			//System.out.println("str = " + str + " url = " + url);
			sbc.position(pos);
			if( sbc.read(buf) == 0) break;
			str = new String(buf.array());								// Conversion des 50 octets en une chaine de caractères
			if (str.trim().equals(""))									// Suppression des espaces en fin de chaine
			{
				sbc.close();
				return false;
			}
		}
		sbc.close();
		if(str.equals(url)) {
			System.out.println("Youpi c'est gagne " + str + " = " + url);
			return true;
		}
		return false;
	}

	public static void newAddBigFile(String url, SeekableByteChannel sbc) throws IOException, NoSuchAlgorithmException
	{
		byte[] byteChaine = url.getBytes("UTF-8");
		MessageDigest md = MessageDigest.getInstance("MD5");
		byte[] hash = md.digest(byteChaine);

		long posAbs = 0;
		for (byte value : hash){
		    posAbs <<= 8; 										//On décale de 8 bits vers la gauche
		    posAbs += value;
		}
		if(posAbs < 0)posAbs = - posAbs;
		long pos =  posAbs % nbLinesFile;
		pos = pos * 50;
		//System.out.println("position = " + pos);

		StringBuffer content = new StringBuffer();
		content.append(url);
		while (content.length() < urlSize)		content.append(' ');			// Ecriture de 50 octets
		url = content.toString();

		//System.out.println("1 coucou " + pos + " url = " + url);

		sbc.position(pos);		// On se déplace à la position calculée dans le fichier
		ByteBuffer buf = ByteBuffer.wrap(url.getBytes());
		ByteBuffer buf1 = ByteBuffer.allocate(50);
		sbc.read(buf1);

		String str = new String(buf1.array());						// Conversion des 50 octets en une chaine de caractères
		while (!str.trim().equals(""))								// Suppression des espaces en fin de chaine
		{
			//System.out.println("test2 " + str + "     " + pos);

			pos = (pos + urlSize) % sizeFile;							// Décalage d'une URL

			sbc.position(pos);

			int nbread = sbc.read(buf1);
			//System.out.println("nb lu " + nbread);
			if(nbread == 0) break;

			str = new String(buf1.array());								// Conversion des 50 octets en une chaine de caractères

			str = str.trim();											// Suppression des espaces en fin de chaine
		}
		//System.out.println("str = '" + str + "' url = " + url);
		sbc.write(buf);
	}

	public static void newCreateBigFile() throws IOException , NoSuchAlgorithmException		// créé le fichier de 100 Giga
	{
		System.out.println("Création du gros fichier");
		long start = System.currentTimeMillis();

		SeekableByteChannel sbc = Files.newByteChannel(Paths.get(cheminFichier), StandardOpenOption.READ, StandardOpenOption.WRITE /*, StandardOpenOption.CREATE_NEW*/);
		byte[] bs = new byte[1000];				// Création d'un byte array de 1000 espaces
		for (int i = 0; i < bs.length; i++)
		{
			bs[i] = ' ';
		}
		for (int i = 0; i < sizeFile/1000; i++)				// Copie de ces 1000 espaces sizeFile/1000 fois
		{
			ByteBuffer buf = ByteBuffer.wrap(bs);
			sbc.write(buf);
		}

		SeekableByteChannel infectFile = Files.newByteChannel(Paths.get(cheminInfect), StandardOpenOption.READ);
		ByteBuffer buf = ByteBuffer.allocate(50_000);
		int ret = infectFile.read(buf);
		String str;

		int count = 0;

		while(ret>0)
		{
			for (int i = 0; i < 1000; i++)
			{
				str = new String(buf.array(),i*50,50);
				str = str.trim();
				newAddBigFile(str, sbc);
				count ++;
				if (count % (200_000_000 / 1000) == 0)
					System.out.println(count / (200_000_000 / 1000) + "%");
			}
			buf.clear();
			ret = infectFile.read(buf);
		}
		//System.out.println("test4");
		sbc.close();
		infectFile.close();



		System.out.println("Fin de création");
		float time = (System.currentTimeMillis()-start)/1000;
		System.out.println("Temps de création = "+ time +"s");
	}


	// renvoit True si l'url est contenue dans infected-urls.txt, et False sinon
	public static boolean reponseRapideCertaine (String element, FiltreBloom filter) throws IOException		// pas complété du tout
	{
		try {
			boolean test1 = filter.research(element);
			//System.out.println("test 1 = " + test1);
			if (test1) {
				boolean test2 = newSearchBigFile(element);
				//System.out.println("test 2 = " + test2);
				return ( test2 );
			}
			return false;
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return false;
		}
	}



	public static void utilisation (int k) throws IOException
	{
		long start = System.currentTimeMillis();


		FiltreBloom infectFilter = new FiltreBloom (k);
		infectFilter.fill(cheminInfect);

		SeekableByteChannel valideFile = Files.newByteChannel(Paths.get(cheminValide),
		StandardOpenOption.READ);
		int count =0;

		int nbFauxPositif = 0;

		ByteBuffer buf2 = ByteBuffer.allocate(50_000);
		int ret = valideFile.read(buf2);
		String str;
		while(ret>0)
		{
			for (int i = 0; i < 1000; i++)
			{
				str = new String(buf2.array(),i*50,50);
				str = str.trim();
//				System.out.println(str);
				if (infectFilter.research(str))		nbFauxPositif ++ ;
				count++;
			}
			buf2.clear();
			ret = valideFile.read(buf2);
		}

		System.out.println("k = " + k + "\tNombre de faux positif : " + nbFauxPositif + "\tPourcentage de faux positifs: " + (nbFauxPositif * 100.0 / count) + "%" + "\tTemps d'exécution = " + (System.currentTimeMillis()-start)/1000.0+" s");

		valideFile.close();

	}

	public static void main(String[] args) throws IOException
	{
/*		System.out.println("Calcul du pourcentage de faux positifs en fonction de k");
		for (int k = 1; k <= 1; k++ )							// 1 à 1 pour exécution rapide, 1 à 20 pour complète
		{
			try {
				utilisation(k);
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}


		System.out.println("Version sans faux positif");

		// à réaliser une seule fois, environ 1 mon 30 d'exécution
		try {
			newCreateBigFile();
		} catch (NoSuchAlgorithmException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
				*/


		FiltreBloom infectFilter = new FiltreBloom (7); 		// le meilleur pourcentage pour m = 200_000_000 est k = 7
		infectFilter.fill(cheminInfect);


		SeekableByteChannel file = Files.newByteChannel(Paths.get(cheminTest), StandardOpenOption.READ);
		ByteBuffer buf = ByteBuffer.allocate(50_000);
		int ret = file.read(buf);
		String str;
		boolean res;
		System.out.println("start ");
		int count = 0;
		while(ret>0)
		{
			for (int i = 0; i < 1000; i++)
			{
				str = new String(buf.array(),i*50,50);
				str = str.trim();
				//System.out.println("url = " + str);
				res = reponseRapideCertaine(str, infectFilter);
				//System.out.println(res + "");
				if(res == true) System.out.println(res + "");
			}
			buf.clear();
			ret = file.read(buf);
			count += 1000;
			//System.out.println("ca avance " + count );
		}
		file.close();
		System.out.println("fini");
	}
}
