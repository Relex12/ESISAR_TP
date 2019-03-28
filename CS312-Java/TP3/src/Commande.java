import java.util.ArrayList;

public class Commande {
	private ArrayList<Consommable> itemsCommandes;

	public Commande() {
		this.itemsCommandes = new ArrayList<Consommable>();
	}

	public void addItem(Consommable c){
		this.itemsCommandes.add(c);
	}

	public ArrayList<Consommable> getItemsCommandes(){
		return this.itemsCommandes;
	}

}
