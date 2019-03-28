

public class Entree extends Plat
{
	public Entree(String nom, int prix, int kcal, int glucides)
	{
		super(nom, prix, kcal, glucides);
	}

	public String toString(){
		String message = getNom() + "(" + getPrix() + ")";
		return message;
	}
}
