package tdm1.model;

import java.util.List;

public class Tdm03Exo0
{
	/**
	 * Solution OK
	 */
	public static void main(String[] args)
	{
		List<Appel> appels = DataSource.getDataSource().getAppels();

		// Version sans stream	
		int cout=0;
		for (Appel appel : appels)
		{
			if (appel.client.departement.numero==26)
			{
				cout=cout+appel.cout;
			}
		}
		
		System.out.println("Montant total (sans stream) = "+cout+" centimes");;
		
		
		// Version avec stream
		int cout2 = appels.stream().filter(e->e.client.departement.numero==26).mapToInt(e->e.cout).sum();
		System.out.println("Montant total (avec stream) = "+cout2+" centimes");
				

	}
}