import java.util.*;

public class Evaluer {
	public static void main(String[] args)
	{
		Expression monexp = Strings2Exp(args);
		System.out.println("valeur de x ?");
		Scanner in = new Scanner(System.in);
		double x = in.nextDouble();
		System.out.println("expression" + monexp.toString());
		System.out.println("resultat" + monexp.valeur(x));
	}

	public static Expression Strings2Exp(String[] s)
	{
		int i = 0;
		int nbparenthese = 0;
		int j = 0;
		if(s.length > 1) {
			i = prioMin(s);
			j = i+1;
			if("(".equals(s[i])) {
				nbparenthese = 1;
				while(nbparenthese != 0) {
					if(s[j].equals(")")){
						nbparenthese -= 1;
					}
					if(s[j].equals("(")) {
						nbparenthese += 1;
					}
					j++;
				}
				return Strings2Exp(Arrays.copyOfRange(s,i+1,j-1));
			}
			if(s[i].equals("+")) {
				return new Addition(Strings2Exp(Arrays.copyOfRange(s,0,i)),Strings2Exp(Arrays.copyOfRange(s,i+1,s.length)));
			}
			if(s[i].equals("-")) {
				return new Soustraction(Strings2Exp(Arrays.copyOfRange(s,0,i)),Strings2Exp(Arrays.copyOfRange(s,i+1,s.length)));
			}
			if(s[i].equals("*")) {
				return new Multiplication(Strings2Exp(Arrays.copyOfRange(s,0,i)),Strings2Exp(Arrays.copyOfRange(s,i+1,s.length)));
			}
			if(s[i].equals("/")) {
				return new Division(Strings2Exp(Arrays.copyOfRange(s,0,i)),Strings2Exp(Arrays.copyOfRange(s,i+1,s.length)));
			}
			if(s[i].equals("sin")) {
				return new Sin(Strings2Exp(Arrays.copyOfRange(s,i+1,s.length)));
			}
			if(s[i].equals("cos")) {
				return new Cos(Strings2Exp(Arrays.copyOfRange(s,i+1,s.length)));
			}
			if(s[i].equals("log")) {
				return new Log(Strings2Exp(Arrays.copyOfRange(s,i+1,s.length)));
			}
			if(s[i].equals("exp")) {
				return new Exp(Strings2Exp(Arrays.copyOfRange(s,i+1,s.length)));
			}
		}
		if(s.length == 1) {
			if(s[0].equals("x")) {
				return new Variable();
			}
			return new Constante(Double.valueOf(s[0]));
		}
		return null;

	}

	public static int prioMin(String[] s) {
		int i = 0;
		int indice = 0;
		int indiceprio = 10;
		while(i < s.length) {
			if(s[i].equals("(") && indiceprio > 4) {
				indice = i;
				indiceprio = 5;
			}
			if(s[i].equals("+") && indiceprio > 0) {
				indice = i;
				indiceprio = 0;
			}
			if(s[i].equals("-") && indiceprio > 1) {
				indiceprio = 1;
				indice = i;
			}
			if(s[i].equals("*") && indiceprio > 2) {
				indiceprio = 2;
				indice = i;
			}
			if(s[i].equals("/") && indiceprio > 3) {
				indiceprio = 3;
				indice = i;
			}
			if(s[i].equals("sin") && indiceprio > 4) {
				indiceprio = 4;
				indice = i;
			}
			if(s[i].equals("cos") && indiceprio > 4) {
				indiceprio = 4;
				indice = i;
			}
			if(s[i].equals("log") && indiceprio > 4) {
				indiceprio = 4;
				indice = i;
			}
			if(s[i].equals("exp") && indiceprio > 4) {
				indiceprio = 4;
				indice = i;
			}
			i++;
		}
		return indice;
	}
}




/*public class Evaluer
{
	public static Expression String2Exp (String s)
	{
		ArrayList<String> phrase = new ArrayList<String>();

		int lastSpacePos = 0;
		for(int i = 0; i < s.length(); i++)
			if (s.charAt(i) == ' ')
			{
				phrase.add(s.substring(lastSpacePos, i));
				lastSpacePos = i+1;
			}

		// ici, phrase contient la liste de tous les mots qui étaient séparés par des espaces dans s (où s = args)

		Variable var = new Variable ();
		Constante cst1 = new Constante (2);
		Addition add = new Addition (var, cst1);

		return add;
	}

	public static void main(String[] args)
	{
		double inconnu;
		Scanner lectureClavier = new Scanner(System.in);
		System.out.print("Que vaut x ? ");
		inconnu = Double.parseDouble(lectureClavier.nextLine());					// demande à l'utilisateur la saisie de la valeur de x

		System.out.println("f(x) = " + String2Exp(args[0]).valeur(inconnu));
	}


}
*/
