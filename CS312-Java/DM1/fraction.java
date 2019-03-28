public class fraction
{

//      ATTRIBUTS
    private int numerateur;

    private int denominateur;

//      CONSTRUCTEUR
    public void fraction (int a, int b)
    {
        numerateur = a;
        denominateur = b;
    }

//      METHODES
    public void afficher()
    {
        System.out.println(numerateur + " / " + denominateur);
    }

    public void add (int x)
    {
        numerateur = numerateur + x * denominateur;
    }

    public void sub (int x)
    {
        numerateur = numerateur - x * denominateur;
    }

    public void mult (int x)
    {
        numerateur = numerateur * x;
    }

    private int pgcd (int a, int b)
    {
        while (( a * b ) != 0)
        {
            if (a > b )     a = a-b;
            else            b = b-a;
        }
        if (a == 0)    return b ;
        else        return a ;
    }

    public void reduire ()
    {
        int diviseur = pgcd (numerateur, denominateur);
        denominateur = denominateur / diviseur;
        numerateur = numerateur / diviseur;
    }

    public void addFraction (fraction f)
    {
        numerateur = numerateur * f.getDenominateur()+ f.getNumerateur() * denominateur;
        denominateur = denominateur * f.getDenominateur();
    }

    public void multFraction (fraction f)
    {
        numerateur = numerateur * f.getNumerateur();
        denominateur = denominateur * f.getDenominateur();
    }

    public int getNumerateur ()
    {
        return numerateur;
    }

    public int getDenominateur ()
    {
        return denominateur;
    }

    public void setNumerateur (int num)
    {
        numerateur = num;
    }

    public void setDenominateur (int den)
    {
        denominateur = den;
    }
}
