public class SimpleFSMIO {
	private SimpleFonctionTransition t;
	private String étatInit;
	private String étatCourant;
	private String états[];
	private char entrées[];


	public SimpleFSMIO(String états[], String étatInit, char entrées[]) {
		t = new SimpleFonctionTransition(états, entrées);
		this.états = états;
		this.entrées = entrées;
		this.étatCourant = this.étatInit = étatInit;
	}

	public void ajouterTransition(String étatOrig, char valEntrée,
                                  String étatDest, int sortie){
		boolean étatOrigValide = false;
		boolean étatDestValide = false;
		boolean entréeValide = false;

		for(int ie = 0; ie < this.états.length &&
                             (!étatOrigValide || !étatDestValide); ie++){
			if(étatOrig.equals(this.états[ie])) étatOrigValide = true;
			if(étatDest.equals(this.états[ie])) étatDestValide = true;
		}

		for(int i = 0; i < this.entrées.length && !entréeValide; i++){
				entréeValide = (valEntrée == this.entrées[i]);
		}

		if (étatOrigValide && étatDestValide && entréeValide){
			this.t.ajouterTransition(étatOrig, valEntrée, étatDest, sortie);
		}
	}

	public int faireTransition(char val)
		throws FaireTransitionException{
			if ( entreeValide(val) == 0){
				throw new FaireTransitionException();
			}
			int sortie = this.t.getSortie(étatCourant, val);
			try {
				this.étatCourant = this.t.getEtatSuivant(étatCourant, val);
			} catch (GetEtatSuivantException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			return sortie;
	}

	public void reset(){
		this.étatCourant = this.étatInit;
	}

	public String getEtatCourant(){
		return this.étatCourant;
	}

	public String getEtatSuivant(String s, char e){
		String es = "";
		try{
			es = t.getEtatSuivant(s, e);
		}
		catch (Exception ex){
			System.out.println("Exception " + ex);
			System.exit(0);
		}
		return(es);
	}

	public int getSortie(String s, char e){
		int es = 0;
		try{
			es = t.getSortie(s, e);
		}
		catch (Exception ex){
			System.out.println("Exception " + ex);
			System.exit(0);		}
		return es;
	}


  public int entreeValide(char val){
		int valide = 0;
		for ( char entree : entrées){
			if (entree == val) valide = 1;
		}
		return valide;
	}


  public static void main(String args[]){
	  String nomEtats[] = new String[3];
	  char entrées[] = new char[2];
	  nomEtats[0] = "s1";
	  nomEtats[1] = "s2";
	  nomEtats[2] = "s3";
	  entrées[0] = 'a';
	  entrées[1] = 'b';
	  SimpleFSMIO auto = new SimpleFSMIO(nomEtats, "s1", entrées);
	  auto.ajouterTransition("s1", 'a', "s1", 0);
	  auto.ajouterTransition ("s1", 'b', "s3", 0);
	  auto.ajouterTransition ("s2", 'a', "s1", 0);
	  auto.ajouterTransition ("s2", 'b', "s2", 1);
	  auto.ajouterTransition ("s3", 'a', "s2", 1);
	  auto.ajouterTransition ("s3", 'b', "s3", 1);
	  System.out.println(auto.getEtatSuivant("s1", 'a'));
	  System.out.println(auto.getSortie("s3", 'b'));
	  }
}
