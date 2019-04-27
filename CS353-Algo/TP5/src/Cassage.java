public class Cassage
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

	public static void main(String[] args)
	{
		int hashToFind = args[1];

		try
		{
			ObjectIntputStream objInt = new ObjectIntputStream(new FileIntputStream("table.txt"));
			table = (Noeud[]) objInt.readObject();
			objInt.close();
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}


/*
	Après ça, on va pouvoir craquer le mot de passe.

Bon, je suis pas sûr de comment faut faire pour craquer le mot de passe, alors voilà ce que j'ai en tête avant de l'implémenter :
-	On cherche le hashToFind parmi les P999 des table[i]
-	Si on ne le trouve pas, on applique reduction(999) sur hashToFind, puis on hache le résultat et on cherche parmi les P999 des table[i]
- 	Si on ne le trouve pas, on fait : reduction(998) -> hash -> reduction(999) -> hash (hashToFind), et on cherche
-	Une fois trouvé, on hache et on réduit le mot de passe initial de la ligne i trouvée dans la table, autant de fois qu'il faut pour trouver hashToFind et son MDP

Mais je sais pas trop comment l'implémenter
*/

		int i, j;
		for (j = NB_REMPL-1; j >= 0 ; j--)
		{

			for (i = 0; i < TAB_SIZE;  i++)
			{

				if (hashToFind == 0 )
					return 0;

			}
		}

	}
}
