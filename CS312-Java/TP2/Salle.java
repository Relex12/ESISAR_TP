
abstract public class Salle {
	private int capacite;
	private String nom;
	
	public Salle(int c, String n){
		capacite = c;
		nom = new String(n);
	}
	
	public String toString(){
		return nom + " (" + capacite + " places)";
	}
	
	public int getCapacite(){
		return capacite;
	}
	
	public String getNom(){
		return nom;
	}
}
