package FSMIO;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * An implementation of a transition function as a list of transitions.
 * @author ioannis.parissis@grenoble-inp.fr
 *
 * @param <T1> the type of FSMIO inputs
 * @param <T2> the type of FSMIO outputs
 */
public class TransitionFunction <T1, T2>{
	private List<Transition<T1, T2>> transitions;

	/**
	 * Creates an empty function
	 */
	public TransitionFunction( ) {
		this.transitions = new ArrayList<Transition<T1, T2>>();
	}

	/**
	 * Adds a new transition in the function defined by the parameters
	 * @param orig
	 * @param input
	 * @param output
	 * @param dest
	 */
	public void addTransition(State orig, T1 input, T2 output, State dest){
		this.transitions.add(new Transition<T1, T2>(orig, new Tag<T1, T2>(input, output), dest));
	}
	
	/**
	 * Gets a transition from a state
	 * @param orig
	 * @param input
	 * @return the transition starting from state orig for input, null if there's not such transition
	 */
	public Transition<T1, T2> getTransition(State orig, T1 input){
		Iterator<Transition<T1, T2>> iter = this.transitions.iterator();
		Transition<T1, T2> t = null;
		boolean found = false;
		while(iter.hasNext() && !found){
			t = iter.next();
			found = t.getOrig().equals(orig) && t.getTag().getInput().equals(input);
		}
		return found?t:null;
	}
	
	/**
	 *  Get all transitions from a state
	 * @param s
	 * @return list of all the transitions stating from state s
	 */
	public List<Transition<T1, T2>> getTransitions(State s){
		ArrayList<Transition<T1, T2>> lt = new ArrayList<Transition<T1, T2>>();
		for(Transition<T1, T2> t : this.transitions){
			if (t.getOrig().equals(s)) lt.add(t);
		}
		return lt;
	}
	
	/**
	 * 
	 */
	public String toString(){
		String res = "";;
		Iterator<Transition<T1, T2>> iter = this.transitions.iterator();
		while(iter.hasNext()){
			Transition<T1, T2> t = iter.next();
			res = res + ("\t"+t.getOrig().getName()+" -> "
			+t.getDest().getName()
			+" Tag= "+t.getTag() +"\n");
		}
		return res;
	}

}
