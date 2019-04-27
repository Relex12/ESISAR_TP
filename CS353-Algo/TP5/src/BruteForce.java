import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

public class BruteForce 
{

	public static void main(String[] args) throws NoSuchAlgorithmException
	{
		String Alice =	"8FC92036B2963C604DC38B2DDB305148";
		String Bob =	"367F3AC1129CC92DCBB8C4B9EA4EE55A";
		String Clara =	"38251B4C8C210841C60CDE0B7E4C7A87";
		
		byte[] Alice_hash = new byte[Alice.length() / 2];
		for (int i = 0; i < Alice.length(); i += 2)
		{
			Alice_hash[i/2] = (byte) ((Character.digit(Alice.charAt(i), 16) << 4) + Character.digit(Alice.charAt(i+1), 16));
		}
		
		byte[] Bob_hash = new byte[Bob.length() / 2];
		for (int i = 0; i < Bob.length(); i += 2)
		{
			Bob_hash[i/2] = (byte) ((Character.digit(Bob.charAt(i), 16) << 4) + Character.digit(Bob.charAt(i+1), 16));
		}
		
		byte[] Clara_hash = new byte[Clara.length() / 2];		
		for (int i = 0; i < Clara.length(); i += 2)
		{
			Clara_hash[i/2] = (byte) ((Character.digit(Clara.charAt(i), 16) << 4) + Character.digit(Clara.charAt(i+1), 16));
		}

		
		long start = System.currentTimeMillis();
		
		int nbPasswd = 0;
		int i = 0;
		
		MessageDigest digest = MessageDigest.getInstance("MD5");
		byte[] hash;
		
		while (nbPasswd < 3 && i < 100_000_000)
		{
			String str = String.format("%08d", i);
			
			hash = digest.digest(str.getBytes());
						
			if (i % 1000000 == 0)		System.out.println((i / 1_000_000) + " %");

			
			if (Arrays.equals(hash, Alice_hash))	
			{
				System.out.println("le mot de passe de Alice est " + str);
				nbPasswd ++;
			}
			if (Arrays.equals(hash, Bob_hash))	
			{
				System.out.println("le mot de passe de Bob est " + str);
				nbPasswd ++;
			}
			if (Arrays.equals(hash,Clara_hash))	
			{
				System.out.println("le mot de passe de Clara est " + str);
				nbPasswd ++;
			}
			
			i++;

			
		}
		
		long stop = System.currentTimeMillis();
		
		int time = (int) (stop-start) / 1000;

		System.out.println("temps d'exécution : " + time + " s");
		
	}
}