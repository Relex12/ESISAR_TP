public class chrono
{
    public static void main(String[] args)
    {
        chrono1 c1 = new chrono1 ();
        c1.setHeures(1);
        c1.setMinutes(30);
        System.out.println("utilisation du chrono 1");
        c1.afficher();
        while (c1.getHeures() != 0 && c1.getMinutes() != 0 && c1.getSecondes() != 0)
        {
            c1.rebours();
        }
        System.out.println("FIN du TD !");

        chrono2 c2 = new chrono2 ();
        c2.setHeures(1);
        c2.setMinutes(30);
        System.out.println();
        System.out.println("utilisation du chrono 2");
        c2.afficher();
        while (c2.getHeures() != 0 && c2.getMinutes() != 0 && c2.getSecondes() != 0)
        {
            c2.rebours();
        }
        System.out.println("FIN du TD !");
    }
}
