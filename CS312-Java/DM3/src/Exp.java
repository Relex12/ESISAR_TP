public class Exp extends OperationUnaire implements Expression
	{
	public Exp (Expression a)
	{
		super(a);
	}

	public double valeur(double x)
	{
		return Math.exp(this.argument.valeur(x));
	}

	public String toString ()
	{
		return "exp(" + this.argument + ")";
	}
}
