
public class Hash 
{
//	AJOUTÉ PAR MOI
	private static int m = 200_000_000; 
	
//	PRÉSENT DE BASE
	
	
	public Hash()		// semble inutile, mais ne marche pas sans
	{
		
	}
	
	public static int hachage(String value, int numFonction)
	{
		int h1 = h1(value);
		int h2 = h2(value);
		int h = ( (h1+numFonction*h2) % m);
		h = (h+m) % m;
		return h;
	}

	private static int h1(String value)
	{
		char val[] = value.toCharArray();
		int h=0;
		for (int i = 0; i < val.length; i++)
		{
			h = 31 * h + val[i];
		}
		 return h;
	}

	private static int h2(String value)
	{
		char val[] = value.toCharArray();
		int h=0;
		for (int i = 0; i < val.length; i++)
		{
			h = 57 * (h <<2) + val[i];
		}
		return h;
	}
}
