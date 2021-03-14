package tdm.tdm3.exercice1;

import tdm.tdm1.model.Client;

public class Facture
{
	public Client client;
	
	public int montant;

	public Facture(Client client, int montant)
	{
		this.client = client;
		this.montant = montant;
	}
	
	
	
}
