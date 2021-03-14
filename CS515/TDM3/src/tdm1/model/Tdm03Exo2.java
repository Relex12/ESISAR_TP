package tdm1.model;

import java.util.List;
import java.util.stream.Collectors;

public class Tdm03Exo2
{
	/**
	 * Solution OK
	 */
	public static void main(String[] args)
	{
		List<Appel> appels = DataSource.getDataSource().getAppels();

		List<Facture> factures = appels.stream()
				.collect(Collectors.toMap(a -> a.client, a -> new Facture(a.client, a.cout), (f1, f2) -> new Facture(f1.client, f1.montant + f2.montant)))
				.values().stream().sorted((f1, f2) -> -f1.montant + f2.montant).collect(Collectors.toList());
		
		for (Facture facture : factures)
		{
			System.out.println("Facture client = "+facture.client.nom+" "+facture.client.prenom+" montant ="+facture.montant+" centimes");;	
		}

	}
}