public class OperationBinaire
{
	protected Expression gauche;
	protected Expression droite;

	public OperationBinaire (Expression g, Expression d)
	{
		this.gauche = g;
		this.droite = d;
	}
/*
	private Expression getGauche()
	{
		return this.gauche;
	}

	private Expression getDroite()
	{
		return this.droite;
	}

	private void setGauche(Expression g)
	{
		this.gauche = g;
	}

	private void setDroite(Expression d)
	{
		this.droite = d;
	}
*/
}
