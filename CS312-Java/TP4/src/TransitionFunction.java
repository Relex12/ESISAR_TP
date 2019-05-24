import java.util.ArrayList;
import java.util.List;

import javax.swing.text.html.HTMLDocument.Iterator;

public class TransitionFunction <T1, T2>{
	private List<Transition<T1, T2>> transitions;

	public TransitionFunction( ) {
		this.transitions = new ArrayList<Transition<T1, T2>>();
	}

	public void addTransition(State orig, T1 input, T2 output, State dest){
		this.transitions.add(new Transition<T1, T2>(orig,
                        new Tag<T1, T2>(input, output), dest));
	}
	
	// Retourne la transition correspondant à l'état orig et à l'entrée input
	public Transition<T1, T2> getTransition(State orig, T1 input) throws NoTransitionException {
		Iterator<Transition<T1, T2>> iter = this.transitions.iterator();
		// Compléter	
	}
}
