// Exo2

package tdm1;

import java.util.Comparator;

public class SortClient1 implements Comparator<Client>{

    @Override
    public int compare (Client o1, Client o2) {
        if ( (o1.nom.compareTo(o2.nom) < 0) || (o1.age > o2.age && o1.nom.compareTo(o2.nom) == 0) || (o1.age == o2.age && o1.nom.compareTo(o2.nom) == 0 && o1.prenom.compareTo(o2.prenom) < 0 ) ) return -1;
        if ( (o1.nom.compareTo(o2.nom) > 0) || (o1.age < o2.age && o1.nom.compareTo(o2.nom) == 0) || (o1.age == o2.age && o1.nom.compareTo(o2.nom) == 0 && o1.prenom.compareTo(o2.prenom) > 0 ) ) return 1;
        return 0;
    }
}