import java.util.ArrayList;
import java.util.List;

public class FSMIO <T1, T2> {
	private List<State> states;
	private TransitionFunction<T1, T2> tf ;
	private State currentState;	
	private State initialState;

	// Constructors
	public FSMIO(List<State> states, State init) {
		this.states = states;
		this.tf = new TransitionFunction<T1, T2>();
		this.currentState = this.initialState = init;
	}

	public FSMIO(State init){
		this.currentState = this.initialState = init;
		this.states = new ArrayList<State>();
		this.states.add(init);
		this.tf = new TransitionFunction<T1, T2>();
	}	

	public void addTransition(State orig, T1 input, T2 output, State dest){
		if (/* Compléter */true){
			tf.addTransition(orig, input, output, dest);
		}
	}
	public boolean addState(State s){		
		boolean done = false;
		if(!this.states.contains(s)){
			this.states.add(s);
			done = true;
		}
		return done;
	}

	public void reset(){
		currentState = initialState;
	}

	public T2 doTransition(T1 input) throws FaireTransitionException {		
		try {
			Transition<T1, T2> nt = tf.getTransition(currentState, input); 
			currentState = nt.getDest();
			return nt.getTag().getOutput();
		}
		catch(NoTransitionException e) {
			throw new FaireTransitionException();
		}
	}

	public String toString(){
		return tf.toString();
	}
	
	public static void main(String args[]){
		ArrayList<State> nomEtats = new ArrayList<State>();
		char entrées[] = new char[2];
		State s1 = new State("s1");
		State s2 = new State("s2");
		State s3 = new State("s3");
		nomEtats.add(s1);
		nomEtats.add(s2);
		nomEtats.add(s3);
		entrées[0] = 'a';
		entrées[1] = 'b';

		FSMIO<Character, Integer> auto = new FSMIO <Character, Integer> (nomEtats, s1);
		
		
		auto.addTransition (s1, 'a', 0, s1);
		auto.addTransition (s1, 'b', 0, s3);
		auto.addTransition (s2, 'a', 0, s1);
		auto.addTransition (s2, 'b', 1, s2);
		auto.addTransition (s3, 'a', 1, s2);
		auto.addTransition (s3, 'b', 1, s3);
//		System.out.println(auto.getEtatSuivant(s1, 'a'));
//		System.out.println(auto.getSortie(s3, 'b'));
		
	}
}