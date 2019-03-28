public class division
{
	public static void main(String[] args) {
        System.out.println("TESTS DE L'EXACTITUDE DES OPERATIONS");
        System.out.println("int   : 6 / 5 = "+ (int)(6/5));
        System.out.println("float : 6 / 5 = "+ (float)(6/5));

        System.out.println("TESTS DE LA CLASSE FRACTION");
        System.out.println("resolution de (123/456+789/10 +11)*12 ");

        fraction f1 = new fraction();
        fraction f2 = new fraction();
        f1.setNumerateur(123);
        f1.setDenominateur(456);
        f2.setNumerateur(789);
        f2.setDenominateur(10);

/* nous avons testé d'écrire la définition des fractions : new fraction (123, 456);
mais ceci nous renvoie l'erreur :  error: constructor fraction in class fraction cannot be applied to given types;
nous n'avons pas réussi à resoudre ce problème. */

        f1.addFraction(f2);
        System.out.println("addition de f2 à f1");
        f1.afficher();

        f1.add(11);
        System.out.println("addition de 11 à f1");
        f1.afficher();

        f1.mult(12);
        System.out.println("multiplication de f1 par 12");
        f1.afficher();

        f1.reduire();
        System.out.println("réduction de f1");
        f1.afficher();

    }
}
