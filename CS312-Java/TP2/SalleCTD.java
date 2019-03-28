
public class SalleCTD extends Salle{
	public SalleCTD(int capacite, String nom){
		super(capacite, nom);
	}
	
	public String toString(){
		return "Salle cours-TD "+ super.toString();
	}
}
