
public class Dessert extends Plat
{
	public Dessert(String nom,  int prix, int kcal, int glucides)
	{
		super(nom, prix, kcal, glucides);
	}

	public String toString(){
		String message = getNom() + "(" + getPrix() + ")";
		return message;
	}
}
