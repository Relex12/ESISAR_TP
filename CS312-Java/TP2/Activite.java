import java.util.*;


 public class Activite {
	private String nom;
	private ArrayList<Groupe> groupes;
	private ArrayList<Salle> sallesAppropriees;
	
	public Activite(String nom){
		this.nom = new String(nom);
		groupes = new ArrayList<Groupe>();
		sallesAppropriees = new ArrayList<Salle>();
	}
	
	public void addGroupe(Groupe groupe){
		groupes.add(groupe);
	}
	
	protected void addSalle(Salle s){ 
		sallesAppropriees.add(s); 
	}
	
	public ArrayList<Salle>  getSalles(){
		return sallesAppropriees;
	}
	
	public ArrayList<Groupe> getGroupes(){
		return groupes;
	}
	
	public String toString(){
		return "Activite " + nom + " (" + groupes +")";
	}
}
