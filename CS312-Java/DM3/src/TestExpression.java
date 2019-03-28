import java.util.*;

public class TestExpression
{
	public static void main(String[] args)
	{
		Variable var = new Variable ();

		Constante cst1 = new Constante (2);
		Sin sin = new Sin (var);

		Constante cst2 = new Constante (3);
		Cos cos = new Cos (var);

		Multiplication mult1 = new Multiplication(cst1, sin);
		Multiplication mult2 = new Multiplication(cst2, cos);
		Addition add = new Addition (mult1, mult2);

		System.out.println("f(x) = " + add.toString());
		//f(x) = 2*sin(x) + 3*cos(x)

		ArrayList<Double> listeTest = new ArrayList<Double>();
		listeTest.add(0.0);
		listeTest.add(0.5);
		listeTest.add(1.0);
		listeTest.add(1.5);
		listeTest.add(2.0);
		listeTest.add(2.5);
		listeTest.add(3.0);
		listeTest.add(3.5);

		for (double test : listeTest)
			System.out.println("x = " + test + ": f(x) = " + add.valeur(test));
	}
}
