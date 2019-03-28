public class Log extends OperationUnaire implements Expression
	{
	public Log (Expression a)
	{
		super(a);
	}

	public double valeur(double x)
	{
		return Math.log(this.argument.valeur(x));
	}

	public String toString ()
	{
		return "log(" + this.argument + ")";
	}
}
