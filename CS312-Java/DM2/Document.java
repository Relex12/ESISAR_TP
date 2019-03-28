public class Document
{
	private int numReg;
	private String title;

	public Document (int num, String tit)
	{
		this.numReg = num;
		this.title = tit;
	}

	public String toString()
	{
		return this.title + " n°" + this.numReg;
	}

	public void setNumReg (int num)
	{
		this.numReg = num;
	}

	public void setTitle (String tit)
	{
		this.title = tit;
	}

	public int getNumReg ()
	{
		return this.numReg;
	}

	public String setTitle ()
	{
		return this.title;
	}
}
