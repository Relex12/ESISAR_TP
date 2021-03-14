// Exo3

package tdm1;

import java.util.Comparator;

public class SortClient2 implements Comparator<Client>{

    @Override
    public int compare (Client o1, Client o2) {
    	// il y a des modifications à faire, on va supposer qu'elles sont faites
    	// nom croissant, puis age décroissant, puis prénom croissant
        if ( (o1.nom.compareTo(o2.nom) < 0) || (o1.age > o2.age && o1.nom.compareTo(o2.nom) == 0) || (o1.age == o2.age && o1.nom.compareTo(o2.nom) == 0 && o1.prenom.compareTo(o2.prenom) < 0 ) ) return -1;
        if ( (o1.nom.compareTo(o2.nom) > 0) || (o1.age < o2.age && o1.nom.compareTo(o2.nom) == 0) || (o1.age == o2.age && o1.nom.compareTo(o2.nom) == 0 && o1.prenom.compareTo(o2.prenom) > 0 ) ) return 1;
        return 0;
    }
}