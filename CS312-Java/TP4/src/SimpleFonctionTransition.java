import java.util.ArrayList;

public class SimpleFonctionTransition {
	private ArrayList<String> etatsOrigine;
	private ArrayList<String> etatsArrivee;
	private ArrayList<Character> entrees;
	private ArrayList<Integer> sorties;

	public SimpleFonctionTransition (String nomsEtats[], char entrées[])
	{
		for (char c : entrées)
			this.entrees.add(c);
		for (String s : nomsEtats)
			this.etatsOrigine.add(s);

	}

	public void ajouterTransition(String étatOrig, char entrée,
                                 String étatDest, int sortie){
		this.etatsOrigine.add(étatOrig);
		this.etatsArrivee.add(étatDest);
		this.entrees.add(entrée);
		this.sorties.add(sortie);
	}

	public String getEtatSuivant(String étatOrig, char entrée)
		throws GetEtatSuivantException{
			for ( String etat_orig : etatsOrigine ){
				if ( etat_orig == étatOrig ){
					if ( entrees.get( etatsOrigine.indexOf( etat_orig ) )  == entrée){
						return etatsArrivee.get( etatsOrigine.indexOf( etat_orig ) );
					}
				}
			}
			throw new GetEtatSuivantException();
	}


	public int getSortie(String étatOrig, char entrée){
		return entrée;

	}
}
