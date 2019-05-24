
public class Transition<T1, T2> {
	private State orig, dest;
	private Tag<T1, T2>	tag;
	
	public Transition(State eorig, Tag<T1, T2> t, State edest){
		this.orig = eorig;
		this.tag = t;
		this.dest = edest;
	}
	
	public State getOrig(){
		return this.orig;
	}

	public Tag<T1, T2> getTag(){
		return this.tag;
	}
	
	public State getDest(){
		return this.dest;
	}

	public void setOrig(State o){
		this.orig = o;
	}
	
	public void setDest(State d){
		this.dest = d;
	}
}