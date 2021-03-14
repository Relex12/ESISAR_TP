// Exo0

package tdm1;

import java.util.*;
import java.util.Collections;

public class BubbleSort {

    public static void main(String[] args)  {
        List<Departement> ldep = DataSource.getDataSource().getDepartements();
        for (int i = ldep.size()-1 ; i >= 0 ; i--) 
        	for (int j = 0 ; j < i ; j++) 
                if(ldep.get(j+1).numero < ldep.get(j).numero)
                    Collections.swap(ldep, j+1, j);
        
        for (Departement dep : ldep)  
        	System.out.println("Numero "+dep.numero+" Departement "+dep.nom);
    }
    
}