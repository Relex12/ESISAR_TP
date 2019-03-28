public class TestRestaurant
{
	public static void main (String [] args)
	{
		Entree SaladeVerte = new Entree("salade verte", 400, 5, 0);
		Entree SaladeBis = new Entree("salade verte", 400, 5, 0);
		Entree SaladeComposée = new Entree("salade composée", 600, 20, 5);
		PlatPrincipal PizzaReine = new PlatPrincipal ("pizza Reine", 900, 830, 100);
		PlatPrincipal PizzaMargarita = new PlatPrincipal ("pizza Margarita", 800, 700, 60);
		PlatPrincipal SpaghettiBolo = new PlatPrincipal ("spaghettis bolognaise", 1500, 700, 50);
		Dessert Tiramisu = new Dessert ("tiramisu", 600, 400, 50);
		Boisson Bière = new Boisson ("bière", 800, 1000, 600, 20);
		Boisson Eau = new Boisson ("eau", 0, 1000, 0, 0);

		Carte resto = new Carte();
		resto.addEntree(SaladeVerte);
		resto.addEntree(SaladeVerte);
		resto.addEntree(SaladeComposée);
		resto.addPlatPrincipal(PizzaReine);
		resto.addPlatPrincipal(PizzaMargarita);
		resto.addPlatPrincipal(SpaghettiBolo);
		resto.addDessert(Tiramisu);
		resto.addBoisson(Bière);
		resto.addBoisson(Eau);

		try {
			Menu Economique = new Menu (1500, SaladeVerte, PizzaReine, Tiramisu, Eau);
			resto.addMenu(Economique);
		}
		catch (Exception e) {	System.out.println(e);	}

		try {
			Menu Découverte = new Menu (2500, SaladeComposée, SpaghettiBolo, Tiramisu, Bière);
			resto.addMenu(Découverte);
		}
		catch (Exception e) {	System.out.println(e);	}

		resto.proposerMenu(2000,1000);
		
//		Carte resto2 = new Carte("carte.txt");
//		resto2.proposerMenu(2000,1000);
	}
}
