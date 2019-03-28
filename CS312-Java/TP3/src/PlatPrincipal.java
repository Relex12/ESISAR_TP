
public class PlatPrincipal extends Plat
{
	public PlatPrincipal(String nom, int prix, int kcal, int glucides)
	{
		super(nom, prix, kcal, glucides);
	}

	public String toString(){
		String message = getNom() + "(" + getPrix() + ")";
		return message;
	}

}
