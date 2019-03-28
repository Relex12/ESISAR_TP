public class Revue extends Document
{
	private int year;

	private int month;

	public Revue (int num, String tit, int yea, int mon)
	{
		super(num, tit);
		this.year = yea;
		this.month = mon;
	}

	public String toString()
	{
		return super(toString()) + "année " + this.year + ", mois" + this.month;
	}

	public void setYear (int yea)
	{
		this.year = yea;
	}

	public void setMonth (int mon)
	{
		this.month = mon;
	}

	public String getYear ()
	{
		return this.year;
	}

	public int getMonth ()
	{
		return this.month;
	}
}
