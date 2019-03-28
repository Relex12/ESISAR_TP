public class Constante implements Expression
{
	protected double permanent;

	public Constante (double p)
	{
		this.permanent = p;
	}

	public double valeur (double x)
	{
		return this.permanent;
	}

	public String toString ()
	{
		return this.permanent + "";			// ici, this.permanent.toString() ne marche pas, alors on cast comme on peut
	}
}
