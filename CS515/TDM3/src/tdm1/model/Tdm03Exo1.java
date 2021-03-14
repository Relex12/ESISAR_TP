package tdm1.model;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Tdm03Exo1
{
	/**
	 * 
	 */
	public static void main(String[] args)
	{
		List<Appel> appels = DataSource.getDataSource().getAppels();

		// 	
		Map<Client,Facture> mapFactures = new HashMap<>();
		
		
		for (Appel appel : appels)
		{
			Facture f = mapFactures.get(appel.client);
			if (f==null)
			{
				f = new Facture(appel.client, 0);
				mapFactures.put(appel.client, f);
			}
			f.montant+=appel.cout;
		}
		
		List<Facture> factures = new ArrayList<>();
		factures.addAll(mapFactures.values());
		factures.sort((f1, f2) -> -f1.montant + f2.montant);
		
		for (Facture facture : factures)
		{
			System.out.println("Facture client = "+facture.client.nom+" "+facture.client.prenom+" montant ="+facture.montant+" centimes");;	
		}


	}
}