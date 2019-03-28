
public class Groupe{
	private String nom;
	private int effectif;
	
	public Groupe(String n, int e){
		nom = new String(n);
		effectif = e;
	}
	
	public int getEffectif(){
		return effectif;
	}
	
	public String getNom(){
		return nom;
	}
	
	public String toString(){
		return nom + " (" + effectif + " etudiants)";
	}
}
