public class Noeud implements java.io.Serializable
{
	public int px;
	public int p999;

	public Noeud (int Px, int P999)
	{
		this.px = Px;
		this.p999 = P999;
	}

	@Override
	public String toString ()
	{
		return (this.px + " -> " + this.p999);
	}
}
