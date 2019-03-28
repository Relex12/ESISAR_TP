public class Manuel extends Livre
{
	private int level;

	public Manuel (int num, String tit, String aut, int nb, int lvl)
	{
		super(num, tit, aut, nb)
		this.level = lvl;
	}

	public String toString()
	{
		return super(toString()) + " niveau " + this.level;
	}

	public void setLevel (int lvl)
	{
		this.level = lvl;
	}

	public int getLevel ()
	{
		return this.level;
	}
}
