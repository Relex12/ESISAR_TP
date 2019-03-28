public class Livre extends Document
{
	private String author;

	private int nbPages;

	public Livre (int num, String tit, String aut, int nb)
	{
		super(num, tit);
		this.author = aut;
		this.nbPages = nb;
	}

	public String toString()
	{
		return super(toString()) + this.author + ", " + this.nbPages + " pages";
	}

	public void setAuthor (String aut)
	{
		this.author = aut;
	}

	public void setNbPages (int nb)
	{
		this.nbPages = nb;
	}

	public String getAuthor ()
	{
		return this.author;
	}

	public int getNbPages ()
	{
		return this.nbPages;
	}
}
