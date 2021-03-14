package FSMIO;

/**
 * A class representing a state by its name.
 * @author ioannis.parissis@grenoble-inp.fr
 *
 */
public class State {

	private String name;
	
	/**
	 * 
	 * @param name
	 */
	public State(String name){
		this.name = name;
	}
	
	/**
	 * 
	 * @return the state name
	 */
	public String getName(){
		return this.name;
	}

	/**
	 * 
	 * @param e
	 * @return true if e has the same name as this
	 */
	public boolean equals(State e){
		return this.name.equals(e.name);		
	}
	
	/**
	 * 
	 */
	public String toString(){
		return name;
	}

}
