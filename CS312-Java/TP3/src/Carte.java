
import java.util.ArrayList;
import java.lang.Object;
import java.io.Reader;
import java.io.InputStreamReader;
import java.io.FileReader;
import java.io.BufferedReader;

public class Carte {
	private ArrayList<Consommable> entrees;
	private ArrayList<Consommable> platsPrincipaux;
	private ArrayList<Consommable> desserts;
	private ArrayList<Consommable> boissons;

	private ArrayList<Menu> menus;

	public Carte() {
		entrees = new ArrayList<Consommable>();
		platsPrincipaux = new ArrayList<Consommable>();
		desserts = new ArrayList<Consommable>();
		boissons = new ArrayList<Consommable>();
		menus = new ArrayList<Menu>();
	}

/*	public Carte(String nomfichier)
	{
		BufferedReader buf = new BufferedReader( new FileReader(nomfichier) );
	}
*/
	public void addEntree(Entree e){
		if (!verifCarte(e))	this.entrees.add(e);
	}

	public void addPlatPrincipal(PlatPrincipal p){
		if (!verifCarte(p)) this.platsPrincipaux.add(p);
	}

	public void addDessert(Dessert d){
		if (!verifCarte(d)) this.desserts.add(d);
	}

	public void addBoisson(Boisson b){
		if (!verifCarte(b)) this.boissons.add(b);
	}

	public void addMenu(Menu m){
		if (verifMenu(m)){
			this.menus.add(m);
		}
	}

	public ArrayList<Consommable> getEntrees(){
		return this.entrees;
	}

	public ArrayList<Consommable> getPlatsPrincipaux(){
		return this.platsPrincipaux;
	}

	public ArrayList<Consommable> getDesserts(){
		return this.desserts;
	}

	public ArrayList<Consommable> getBoissons(){
		return this.boissons;
	}

	// Verifie que les plats et boissons du menu sont bien dans la carte

	// renvoie VRAI si tous les éléments du menus sont dans la carte
	private boolean verifMenu(Menu m)
	{
		boolean op = true;
		for (Consommable conso : m.items)		 	op = op && this.verifCarte (conso);
		return op;
	}

	// Verifie qu'il n'y a pas d'homonymes dans la carte

	// renvoie VRAI si il y a doublon (i.e si le consommable existe déjà dans la carte)
	private boolean verifCarte(Consommable c)
	{
		for (Consommable conso : entrees)		 	if (conso == c)		return true;
		for (Consommable conso : platsPrincipaux)	if (conso == c) 	return true;
		for (Consommable conso : desserts)			if (conso == c) 	return true;
		for (Consommable conso : boissons)			if (conso == c) 	return true;
		return false;
	}

	/* Calcule le prix de la commande. A priori, ce prix est la somme des prix des items
	 * SAUF si une partie de ces items constituent un menu; dans ce cas, le tarif menu s'applique pour ces items.
	 */
	public int calculerPrixCommande(Commande c)
	{
		int prix = 0;

		int prixDansMenu = 0;			// prix des consommables qui sont dans un menu m donné

		for (Consommable conso : c.getItemsCommandes())
		{
			prix += conso.getPrix();
			for (Menu m : menus)
			{
				prixDansMenu = 0;
				for (Consommable consoMenu : m.getItems())
					if (conso == consoMenu)
						prixDansMenu += consoMenu.getPrix();
				if (prixDansMenu > m.getPrix())		prix = prix - prixDansMenu;
			}
		}
		return prix;
	}

	public void afficherMenu(){
		System.out.println("Liste des entrees:" + entrees);
		System.out.println("Liste des plats principaux:" + platsPrincipaux);
		System.out.println("Liste des desserts:" + desserts);
		System.out.println("Liste des boissons:" + boissons);

		for (Menu m : menus)		System.out.println(m.toString());
	}

	public void proposerMenu(int kcal, int epsilon)
	{
		int kcal_menu = 0;
		for (Menu menu : menus)
		{
			for ( Consommable conso : menu.getItems() )
			{
				if (conso instanceof Plat )
					kcal_menu += ( (Plat)conso ).getKcal();
				if (conso instanceof Boisson)
					kcal_menu += ( (Boisson)conso ).getKcal();
			}
			if ( (kcal_menu > kcal - epsilon) && (kcal_menu < kcal + epsilon) )
				System.out.println( menu.toString() );
			kcal_menu = 0;
		}
	}


}
