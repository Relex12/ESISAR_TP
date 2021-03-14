package FSMIO;

import java.util.ArrayList;
import java.util.List;

/**
 * A java implementation of FSMIO
 * @author ioannis.parissis@grenoble-inp.fr
 *
 * @param <T1> type of the inputs
 * @param <T2> type of the outputs
 */
public class FSMIO<T1, T2> {
	private List<State> states;
	private TransitionFunction<T1, T2> tf;
	private State currentState;	
	private State initialState;
	private List<State> finalStates;
	
	/** 
	 * Builds a FSMIO from a list of states and an initial state (supposed in that list)
	 * @param states list of all the FSMIO states
	 * @param init initial state
	 * 
	 */
	public FSMIO(List<State> states, State init) {
		this.states = states;
		this.tf = new TransitionFunction<T1, T2>();
		this.finalStates = new ArrayList<State>();
		this.currentState = this.initialState = init;
	}
	
	/** 
	 * Builds a FSMIO with a single  state
	 * @param init initial state
	 * 
	 */
	public FSMIO(State init){
		this.currentState = this.initialState = init;
		this.states = new ArrayList<State>();
		this.states.add(init);
		this.tf = new TransitionFunction<T1, T2>();
		this.finalStates = new ArrayList<State>();
	}
	
	/** 
	 * Checks if a state is already in the FSMIO
	 * @param s
	 * @return true if a state equal to s is in the FSMIO
	 * 
	 */
	private boolean containsState(State s){
		boolean contains = false;
		for(State cs : this.states) 
			contains = contains || cs.equals(s);
		return contains;
	}
		
	/** 
	 * Adds a new state in the FSMIO
	 * @param s
	 * @return true if s has been added, false if s was already there
	 * 
	 */
	public boolean addState(State s){		
		boolean done = false;
		if(!containsState(s)){
			this.states.add(s);
			done = true;
		}
		return done;
	}
	
	/**
	 *  Adds a new final state
	 *  @param s
	 *  @return true if s has been added, false if s was already there
	 */
	public boolean addFinalState(State s){
		boolean done = addState(s); 
		if (done) this.finalStates.add(s);
		return done;
	}
	
	/**
	 *  Adds a new transition. 
	 *  States must be in the FSMIO. 
	 *  No other transition from the same state and with the same input must be in the FSMIO 
	 *  @param orig starting state
	 *  @param input 
	 *  @param output
	 *  @param dest target state
	 *  @return true if the transition has been added
	 * 
	 */
	public boolean addTransition(State orig, T1 input, T2 output, State dest){
		boolean done = containsState(orig) && containsState(dest) && getTransition(orig, input) == null;
		if(done){
			this.tf.addTransition(orig, input, output, dest);
		}
		return done;
	}
		
	/**
	 * Resets the FSMIO to initial state
	 * 
	 */
	public void reset(){
			this.currentState = this.initialState;
		}
		
	/**
	 *  Fires a transition from current state corresponding to an input.
	 *  Updates the current state.
	 * @param input
	 * @return the corresponding output or null if there is no such transition
	 */
	public T2 doTransition(T1 input){
		T2 res = null;
		Transition<T1, T2> nt = getTransition(currentState, input); 
		if(nt != null){
			this.currentState = nt.getDest();
			res = nt.getTag().getOutput();
		}
		return res;
	}
	
	/**
	 *  Fires a transition sequence from current state corresponding to an input sequence.
	 *  Updates the current state.
	 *  @param inputSequence the input sequence
	 *  @return the produced output sequence

	 */
	public List<T2> doTransitionSequence(List<T1> inputSequence){
		List<T2> outputSequence = new ArrayList<T2>();
		for (T1 input : inputSequence){
			T2 output = doTransition(input);
			outputSequence.add(output);
		}
		return outputSequence;
	}
	
	
	/**
	 * Returns the current state
	 * 
	 */
	public State getCurrentState(){
		return this.currentState;
	}
	
	public String toString(){
		return this.states + this.tf.toString();
	}
	
	/**
	 * Gets a transition from a state
	 * @param orig the starting state
	 * @param input the transition input
	 * @return the associated transition, null if not found. 
	 * 
	 */
	public Transition<T1, T2> getTransition(State orig, T1 input){
		return this.tf.getTransition(orig,  input);
	}
	
	/** 
	 * Checks if inputSequence is a synchronizing sequence for this.
	 * Current state is unchanged.
	 * @param inputSequence the candidate synchronizing sequence
	 * @return true iff inputSequence is synchronizing
	 */
	public boolean isSynchronizing(List<T1> inputSequence){

		return false;
	}
	
	/**
	 *  Checks if inputSequence is a distinguishing sequence for this
	 * @param inputSequence the candidate distinguishing sequence
	 * @return true iff inputSequence is distinguishing
	 */
	public boolean isDistinguishing(List<T1> inputSequence){
        List<List<T2>> liste = new ArrayList<>();
        T2 temp;
        int i = 0;
        for (State etat : this.states) {
            liste.add(new ArrayList<T2>());
            this.currentState = etat;
            for (T1 t1 : inputSequence) {
                temp = this.doTransition(t1);
                liste.get(i).add(temp);
            }
            i++;
        }
        
        for (int j = 0; j < i-1; j++)
            for (int j2 = j+1; j2 < i; j2++)
                if(liste.get(j).equals(liste.get(j2))) return false;
        return true;
    }
	
	 
	/**
	 * Executes inputSequence and then distSequence on both iut and this;
	 * @param iut
	 * @param inputSequence
	 * @param distSequence
	 * @return true iff  on both iut and this, executing inputSequence results in the same output sequence AND executing distSequence (assumed to be a distinguishing sequence) results in the same reached state
	 */
    public boolean testFSMOneSequence(FSMIO<T1, T2> iut, List<T1> inputSequence, List<T1> distSequence){
        State stateinit = this.currentState;
        if (this.doTransitionSequence(inputSequence).equals(iut.doTransitionSequence(inputSequence))) {
            this.currentState = stateinit;
            iut.currentState = stateinit;
            this.doTransitionSequence(distSequence);
            iut.doTransitionSequence(distSequence);
            return this.currentState.equals(iut.currentState);
        }
        return false;
    }

	
}
