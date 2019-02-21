public class chrono2
{
//      ATTRIBUT
    private int nbSecondes;

//      CONSTRUCTEUR
    public void chrono ()
    {
        nbSecondes = 0;
    }

//      METHODES

    public void afficher()
    {
		System.out.println(this.getHeures() + ":" + this.getMinutes() + ":" + this.getSecondes());
	}

    public void rebours ()
    {
        if (nbSecondes > 0) nbSecondes = nbSecondes - 1;
        else System.out.println("Impossible d'enlever une seconde");
    }

    public int getSecondes ()
    {
        return (nbSecondes % 60);
    }

    public int getMinutes ()
    {
        return ((nbSecondes %3600) / 60);
    }

    public int getHeures ()
    {
        return (nbSecondes / 3600);
    }

    public void setSecondes (int sec)
    {
        nbSecondes = nbSecondes - nbSecondes % 60  + sec;
    }

    public void setMinutes (int min)
    {
        nbSecondes = nbSecondes % 60 + 3600 * (nbSecondes / 3600) + 60 * min;
    }

    public void setHeures (int heu)
    {
        nbSecondes = nbSecondes % 3600 + 3600 * heu;
    }
}
