package tdm1.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class exo1 {
	
	public static void main(String[] args) {
//		List<Appel> lAppel = DataSource.getDataSource().getAppels();
		HashMap<String,Integer> lMontant = new HashMap<String,Integer>();
//		List<Map.Entry<Client, Integer>> list;
//		
//		for (Appel a : lAppel) lMontant.merge(a.client.nom, a.cout, (a1,a2)->a1+a2);
//		System.out.println(lMontant);
//
//		list = new ArrayList<>(lMontant.entrySet());
//		list.sort((e1, e2) -> e2.getValue() - e1.getValue());
//
//		for (Map.Entry e : list) {
//		System.out.println(((Client)e.getKey()).numTel + ": " + e.getValue());

		List<Appel> lapp = DataSource.getDataSource().getAppels();
//		HashMap<Client, Integer> lMontant = new HashMap<>();
		Integer tmp;

		// On récupere le total pour chaque client
//		for (Appel app : lapp) {
//		tmp = lMontant.containsKey(app.client) ? lMontant.get(app.client) : 0;
//		lMontant.put(app.client, tmp + app.cout);
//		}

		for (Appel a : lapp) lMontant.merge(a.client.nom, a.cout, (a1,a2)->a1+a2);

		// On trie les entries de la map
//		HashMap<String,Integer> lMontant = new HashMap<String,Integer>();
		List<Integer> values = new ArrayList<>(lMontant.values());
		Collections.sort(values);
		
// abandon
		
		for (Integer i : values) {
			for (Integer i : values)
		}
	}
	
}



