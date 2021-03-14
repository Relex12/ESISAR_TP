package tdm.tdm4;

import java.util.Date;

public class LivraisonElementaire
{
	public Long id;
	
	// Quantité commandé
	public int qte;
	
	// Produit commandé 
	public Produit produit;
	
	// Date de livraison 
	public Date dateLiv;
	
	// Commande 
	public Commande commande;

	public LivraisonElementaire(Long id, int qte, Produit produit, Date dateLiv,Commande commande)
	{
		super();
		this.id = id;
		this.qte = qte;
		this.produit = produit;
		this.dateLiv = dateLiv;
		this.commande = commande;
	}
	
	
}
