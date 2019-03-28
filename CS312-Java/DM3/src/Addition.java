public class Addition extends OperationBinaire implements Expression
{
	public Addition (Expression g, Expression d)
	{
		super(g, d);
	}

	public double valeur (double x)
	{
		return this.gauche.valeur(x) + this.droite.valeur(x);
	}

	public String toString ()
	{
		return this.gauche + " + " + this.droite;
	}
}
