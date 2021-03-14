// Exo5

package tdm2;

import tdm1.*;

import java.util.*;

public class GenericSorter2 <T> implements Comparator <T>{

	public List<Critere<? super T, ? extends Comparable>> listeCriteres = new ArrayList<>();
	private List<Client> listeClients;

    public List<T> doIt() {
    	listeClients.sort((Comparator<? super Client>) this);
        return (List<T>) listeClients;
    }

    // note : il faudrait renommer init en sort, ça devrait marcher
    public <A extends Comparable<A>> GenericSorter2<T> init(List<Client> listeClients) { //sort
		this.listeClients = listeClients;
		return this;
	}

	public <A extends Comparable<A>> GenericSorter2<T> by(GetField<T, A> crit, boolean ASC) {
		Critere<T, A> new_crit = new Critere<>();
		new_crit.field = crit;
		new_crit.ASC = ASC;
		listeCriteres.add(new_crit);
		return this;
	}

	
	public <A extends Comparable<A>> int doCompare(T t1, T t2, Critere<? super T, A> crit) {
		A op1 = crit.field.getField(t1);
		A op2 = crit.field.getField(t2);
		return op1.compareTo(op2);
	}
	
	@Override
	public int compare(T op1, T op2) {
		int res = 0;
		for (Critere<? super T, ? extends Comparable> crit : listeCriteres) {
			res = doCompare(op1, op2, crit);
			if (!crit.ASC)	res *= -1;
			if (res!=0)	return res;
		}
		return 0;
	}
}
