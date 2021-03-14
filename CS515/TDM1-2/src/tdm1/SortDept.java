// Exo1

package tdm1;

import java.util.Comparator;

public class SortDept implements Comparator<Departement>{

    @Override
    public int compare(Departement o1, Departement o2) {
        if(o1.numero < o2.numero) return -1;
        if (o1.numero > o2.numero) return 1;
        return 0;
    }
}