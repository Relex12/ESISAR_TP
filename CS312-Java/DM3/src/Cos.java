public class Cos extends OperationUnaire implements Expression
	{
	public Cos (Expression a)
	{
		super(a);
	}

	public double valeur(double x)
	{
		return Math.cos(this.argument.valeur(x));
	}

	public String toString ()
	{
		return "cos(" + this.argument + ")";
	}
}
