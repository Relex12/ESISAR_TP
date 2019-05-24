public class State {
	private String name;
	
	public State(String name){
		this.name = name;
	}
	
	public String getName(){
		return this.name;
	}

	public boolean equals(State e){
		return this.name.equals(e.name);		
	}
	
	public String toString(){
		return this.name;
	}
}
