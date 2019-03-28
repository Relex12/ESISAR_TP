public class chrono1
{

//      ATTRIBUTS
    private int secondes;

    private int minutes;

    private int heures;

//      CONSTRUCTEUR
    public void chrono ()
    {
        secondes = 0;
        minutes = 0;
        heures = 0;
    }

//      METHODES
    public void afficher()
    {
        System.out.println(heures + ":" + minutes + ":" + secondes);
    }

    public void rebours ()
    {
        if (secondes > 0) secondes = secondes - 1;
        else if (minutes > 0)
        {
            minutes = minutes - 1;
            secondes = 59;
        }
        else if (heures > 0)
        {
            heures = heures - 1;
            minutes = 59;
            secondes = 59;
        }
        else System.out.println("Impossible d'enlever une seconde");
    }

    public int getSecondes ()
    {
        return secondes;
    }

    public int getMinutes ()
    {
        return minutes;
    }

    public int getHeures ()
    {
        return heures;
    }

    public void setSecondes (int sec)
    {
        secondes = sec;
    }

    public void setMinutes (int min)
    {
        minutes = min;
    }

    public void setHeures (int heu)
    {
        heures = heu;
    }
}
