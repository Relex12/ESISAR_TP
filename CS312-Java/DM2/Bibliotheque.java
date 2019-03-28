public class Bibliotheque
{
	private int volume;
	private List<Document> stock;

	public Bibliotheque (int vol)
	{
		this.volume = vol;
		this.stock = new ArrayList<Document>();
	}

	public Bool add(Document doc)
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
		for (Document doc : stock)		System.out.println(doc.toString());
	}

	public void printAuthors ()
	{
		for (Document doc : stock)		if (doc instanceof Livre) 		System.out.println((Livre)doc.getAuthor());
	}

	public int addLivres (List<Document> bookList)
	{
		int occ = 0;
		for(Document doc : bookList)	if(doc instanceof Livre)
		{
			this.add(doc);
			occ ++;
		}
		return occ;
	}
}
