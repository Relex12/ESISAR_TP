
public class Boisson implements Consommable, Nutrition
{

	private String nom;
	private int prix; // en cents d'euros
	private int volume; // en centilitres
	private int kcal;
	private float glucides;

	public Boisson(String nom, int prix, int volume, int kcal, int glucides)
	{
		this.nom = nom;
		this.prix = prix;
		this.volume = volume;
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

	public int getVolume(){
		return this.volume;
	}

	public String toString(){
		String message = getNom() + "(" + getPrix() + ")";
		return message;
	}
}
