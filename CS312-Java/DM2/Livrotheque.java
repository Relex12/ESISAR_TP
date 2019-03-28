public class Livrotheque
{
	private int volume;
	private List<Livre> stock;

	public Livrotheque (int vol)
	{
		this.volume = vol;
		this.stock = new ArrayList<Livre>();
	}

	public Bool add(Livre doc)
	{
		Bool ret = false;
		if(stock.size() < volume)
		{
			stock.add(doc);
			ret = true;
		}
		return ret;
	}

	public void printFiles ()
	{
		for (Livre doc : stock)		System.out.println(doc.toString());
	}

	public void printAuthors ()
	{
		for (Livre doc : stock)		System.out.println(doc.getAuthor());
	}

	public int addLivres (List<Livre> bookList)
	{
		for(Livre doc : bookList)	this.add(doc);
		return bookList.size();
	}
}
