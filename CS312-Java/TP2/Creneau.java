import java.util.*;

public class Creneau {
	private int annee;
	private int mois; // 1 e 12
	private int jour; // 1 e 31
	private int heure; // 0 e 23
	private int minute; // 0 e 59
	private int duree; // en minute, maximum 210

	private Salle salle;
	private Activite activite;

	public Creneau(int a, int m, int j, int h, int min, int d, Salle s, Activite ac) {

		annee = a; mois = m; jour = j;
		heure = h; minute = min; duree = d;
		salle = s;
		activite = ac;

		if(!verifCapacite()){
			System.exit(1);
		}
		if(!verifDuree()){
			System.exit(1);
		}
		if(!verifSalle()){
			System.exit(1);
		}
	}

	// Verifie l'adequation de la salle : la salle affectee doit etre une des salles appropriees de l'activite
	private boolean verifSalle()
	{
		for (Salle s : activite.getSalles())
			if (s.equals(salle))
				return true;
		return false;
	}

	// Verifie que la taille de la salle convient à la promo
	private boolean verifCapacite()
	{
		int somme = 0;
		for (Groupe g : activite.getGroupes())
			somme = somme + g.getEffectif();
		if (salle.getCapacite() > somme) return true;
		else return false;
	}

	// Verifie que le debut et la fin du creneau sont dans la meme journee, entre 8h et 19h
	private boolean verifDuree()
	{
		if (this.heure < 8 || this.heure > 19) return false;
		else return true;
	}

	public Salle getSalle(){
		return salle;
	}

	public Activite  getActivite(){
		return activite;
	}

	public int  getDuree(){
		return duree;
	}

	public String toString(){
		return jour + "/" + mois + "/" + annee + " " + heure + ":" + minute +" (" + duree +") : " +
				activite + " " + salle;
	}



/*	public boolean intersection(Creneau c)
	{
	    if ( ( mois == c.mois ) && ( jour == c.jour ) )
		{
	        if ( ( heure * 60 + minute + duree > ( c.heure * 60 + c.minute ) ) || ( c.heure * 60 + c.minute + duree > ( heure * 60 + minute ) ) ) 	// plutôt mettre un &&
				return false;
	    }
	    return true;
	}
*/
	public boolean intersection(Creneau c){
		 if (annee == c.annee && mois == c.mois && jour == c.jour)
		 {
			 if (((this.heure * 60 + this.minute) < (c.heure * 60 + c.minute + c.duree)) && ((c.heure * 60 + c.minute) < (this.heure * 60 + this.minute + this.duree)))
			 {
				 if (this.salle == c.salle) return false;
				 else for (Groupe g1 : this.activite.getGroupes())	for (Groupe g2 : c.activite.getGroupes())	if (g1 == g2) return false;
			 }
		 }
		 return true;
	}

}
