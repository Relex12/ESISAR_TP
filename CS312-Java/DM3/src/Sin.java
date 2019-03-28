public class Sin extends OperationUnaire implements Expression
	{
	public Sin (Expression a)
	{
		super(a);
	}

	public double valeur(double x)
	{
		return Math.sin(this.argument.valeur(x));
	}

	public String toString ()
	{
		return "sin(" + this.argument + ")";
	}
}
