// Exo1

package tdm1;

import java.util.Comparator;
import java.util.List;

public class DeptSortStandard{
    public static void main(String[] args)  {
        List<Departement> ldep = DataSource.getDataSource().getDepartements();
        Comparator<? super Departement> SortTp = new SortDept();
        ldep.sort(SortTp);
        for (Departement departement : ldep) {
            System.out.println(departement.nom + " " + departement.numero);
        }
    }
}