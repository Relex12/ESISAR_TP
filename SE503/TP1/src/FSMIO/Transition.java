package FSMIO;

/**
 * 
 * @author ioannis.parissis@grenoble-inp.fr
 *
 * @param <T1> the type of the inputs
 * @param <T2> the type of the outputs
 */
public class Transition<T1, T2> {

	private State orig, dest;
	private Tag<T1, T2>	tag;
	
	/**
	 * 
	 * @param eorig
	 * @param t
	 * @param edest
	 */
	public Transition(State eorig, Tag<T1, T2> t, State edest){
	
		this.orig = eorig;
		this.tag = t;
		this.dest = edest;
	}
	
	/**
	 * 
	 * @return
	 */
	public State getOrig(){
		return this.orig;
	}

	/**
	 * 
	 * @return
	 */
	public Tag<T1, T2> getTag(){
		return this.tag;
	}
	
	/**
	 * 
	 * @return
	 */
	public State getDest(){
		return this.dest;
	}
}
