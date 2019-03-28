
public class Plat implements Consommable, Nutrition{

	private String nom;
	private int prix; // en cents d'euros
	private int kcal;
	private float glucides;

	public Plat(String nom, int prix, int kcal, int glucides)
	{
		this.nom = nom;
		this.prix = prix;
		this.kcal = kcal;
		this.glucides = glucides;
	}

	public String getNom(){
		return this.nom;
	}

	public int getPrix(){
		return this.prix;
	}

	public int getKcal()
	{
		return this.kcal;
	}

	public float getGlucides()
	{
		return this.glucides;
	}

	public String toString(){
		String message = getNom() + "(" + getPrix() + ")";
		return message;
	}
}
