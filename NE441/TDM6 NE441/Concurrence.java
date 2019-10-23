public class Concurrence extends Thread
{
	private Somme somme;

	public Concurrence(Somme somme)
	{
		this.somme = somme;
	}

	@Override
	public void run()
	{
		int res = 0;
		for (int i = 0; i < 1000; i++)
		{
			res= somme.somme(res, i);
		}
		System.out.println("La somme est 1 et 99 est :"+res);
	}
	public static void main(String[] args) throws InterruptedException
	{
/*
 		Somme somme1 = new Somme();
		Concurrence c1 = new Concurrence(somme1);
		Somme somme2 = new Somme();
		Concurrence c2 = new Concurrence(somme2);
		c1.start();
		c2.start();

 */
		Somme somme = new Somme();
		Concurrence c1 = new Concurrence(somme);
		Concurrence c2 = new Concurrence(somme);
		c1.start();
		c2.start();

	}

	static class Somme
	{
		int c;
		private Object mutex = new Object();
		public int somme(int a, int b)
		{
			synchronized (mutex) 
			{
				c=a+b;
				System.out.println("c="+c);
				return c;
			}
		}
	}
}