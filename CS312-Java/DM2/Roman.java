public class Roman extends Livre
{
	private int award;			//  1 :   GONCOURT, 2 :   MEDICIS, 3 :   INTERALLIE

	public Roman (int num, String tit, String aut, int nb, int awa)
	{
		super(num, tit, aut, nb)
		this.award = awa;
	}

	public String toString()
	{
		switch(this.award)
		{
			case 1 :
				return super(toString()) + ", prix Goncourt";
			case 2 :
				return super(toString()) + ", prix Medicis";
			case 3 :
				return super(toString()) + ", prix Interallie";
			default :
				return super(toString());
		}
	}

	public void setAward (int awa)
	{
		this.award = awa;
	}

	public int getAward ()
	{
		return this.award;
	}
}
