package tdm.tdm4;

import java.util.Date;

public class Commande
{
	public Long id;
	public Date saisieCommande;
	public Consommateur consommateur;
	
	public Commande(Long id, Date saisieCommande, Consommateur consommateur)
	{
		super();
		this.id = id;
		this.saisieCommande = saisieCommande;
		this.consommateur = consommateur;
	}
	
	
	
	
	
	
}
