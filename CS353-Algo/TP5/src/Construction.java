import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.io.*;



public class Construction
{


	/*
	private final static int TAB_SIZE = 1_000_003;
	private final static int RAND_MAX = 100_000_000;
	private final static int NB_REMPL = 1_000_000;
	*/
	private final static int TAB_SIZE = 101;
	private final static int RAND_MAX = 100000000;
	private final static int NB_REMPL = 1000;

	private static Noeud[] table = new Noeud[TAB_SIZE];

	private static int reduction(byte[] bs, int num)
	{
		int res = num;
		int mult = 1;
		for (int i = 0; i < 8; i++)
		{
			res = res + mult * ((bs[i] + 256) % 10);
			mult = mult * 10;
		}
		return res % RAND_MAX;
	}

	public static int calculChaine (int px) throws NoSuchAlgorithmException
	{
		String str = String.format("%08d", px);

		byte[] hash = null;

		MessageDigest digest = MessageDigest.getInstance("MD5");

		int red = 0;

		for (int i = 0; i < 1000; i++)
		{
			hash = digest.digest(str.getBytes());
			red = reduction(hash, i);
			str = String.format("%08d", red);
		}

		return red;
	}

	public static void main(String[] args) throws NoSuchAlgorithmException
	{
		Random rand = new Random(0);
		int Px, P999;



		long start = System.currentTimeMillis();


		for (int i = 0; i < NB_REMPL; i++)
		{
			Px = rand.nextInt(RAND_MAX);
			P999 = calculChaine(Px);

			if (table[P999 % TAB_SIZE] == null)
				table[P999 % TAB_SIZE] = new Noeud(Px, P999);

			if (i % (NB_REMPL/100) == 0)	System.out.println((i / (NB_REMPL/100)) + " %");
		}




		//	AFFICHAGE DU TEMPS D'EXÉCUTION
		long stop = System.currentTimeMillis();
		int time = (int) (stop-start) / 1000;
		System.out.println("temps d'exécution : " + time + " s");


		//	TENTATIVE D'ECRITURE DANS UN FICHIER
		try
		{
			ObjectOutputStream objOut = new ObjectOutputStream(new FileOutputStream("table.txt"));
			objOut.writeObject(table);
			objOut.close();
   		}
	    catch (Exception e)
		{
			e.printStackTrace();
		}


//		for (int i = 0; i < TAB_SIZE; i++)
//			System.out.println(table[i]);

		System.out.println("Fichier écrit\n");

	}
}
