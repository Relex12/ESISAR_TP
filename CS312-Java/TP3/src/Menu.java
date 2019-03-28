import java.util.ArrayList;

public class Menu {
	ArrayList<Consommable> items;
	int prix; // en cents

	public Menu(int prix, Entree e, PlatPrincipal p, Dessert d, Boisson b)  throws Exception
	{
		items = new ArrayList<Consommable>();
		this.prix = prix;
		this.items.add(e);
		this.items.add(p);
		this.items.add(d);
		this.items.add(b);
		if (! verifPrixMenu())		throw new Exception ("Prix du menu trop élevé");
	}

	public ArrayList<Consommable> getItems()
	{
		return this.items;
	}

	public int getPrix()
	{
		return this.prix;
	}

	public String toString(){
		String message = "Menu compose de ";

		for (Consommable c : this.items)	message += c.toString() + " ";

		message += "au prix de " + this.prix/100 + " euros";
		return message;
	}

	private boolean verifPrixMenu(){
		int sommePrix = 0;
		for(Consommable c: this.items){
			sommePrix += c.getPrix();
		}
		return (sommePrix >= this.prix && sommePrix > 0);
	}
}
