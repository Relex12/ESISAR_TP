package tdm1.model;

import java.util.List;

public class exo0 {

	public static void main(String[] args) {
		List<Appel> la = DataSource.getDataSource().getAppels();
		int somme = 0;
		for (Appel a : la) if (a.client.departement.numero == 26) somme += a.cout;
		System.out.println("tot1 : "+ somme + "€");

		System.out.println("tot2 : " + DataSource.getDataSource().getAppels().stream().filter(e->e.client.departement.numero == 26).mapToInt(e->e.cout).sum() + "€");
	}
	
}
