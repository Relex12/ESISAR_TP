package FSMIO;

/**
 * Represents a transition "tag" in a FSMIO. 
 * A tag is made of an input (that activates the transition) and of an output (issued after the transition is executed).
 * @author ioannis.parissis@grenoble-inp.fr
 *
 * @param <T1> the type of the inputs
 * @param <T2> the type of the outputs
 */
public class Tag<T1, T2> implements Input<T1>, Output<T2>{
	
	private T1 input;
	private T2 output;

	/**
	 * 
	 * @param i
	 * @param o
	 */
	public Tag(T1 i, T2 o) {
		this.input = i;
		this.output = o;
	}
	
	/**
	 * 
	 */
	public T1 getInput(){
		return this.input;
	}
	
	/**
	 * 
	 */
	public T2 getOutput(){
		return this.output;
	}
	
	/**
	 * 
	 */
	public String toString(){
		return this.input + "/" + this.output;
	}
}

