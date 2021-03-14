package tdm.tdm4;

public class Produit
{
	public Long id;
	
	public String nom;
	
	// Prix en centimes d'euros 
	public int prix;
	
	// Numero d'ordre pour l'affichage 
	public int numOrdre;
	
	public Producteur producteur;

	public Produit(Long id, String nom, int prix,int numOrdre,Producteur producteur)
	{
		super();
		this.id = id;
		this.nom = nom;
		this.prix = prix;
		this.numOrdre = numOrdre;
		this.producteur = producteur;
	}
	
	
}
