
public class Tag<T1, T2> implements Input<T1>, Output<T2>{
	
	T1 input;
	T2 output;

	public Tag(T1 i, T2 o) {
		this.input = i;
		this.output = o;
	}
	
	public T1 getInput(){
		return this.input;
	}
	
	public T2 getOutput(){
		return this.output;
	}
	
	public String toString(){
		return this.input + "/" + this.output;
	}
}