package Pi;

public class PiMono 
{
	static long N = 5_000_000_000L;
	static int court = 500_000;
	static double pi = 0.0D;
	
	public static void main(String[] args) 
	{
		double tmp = 0.0D;
		for (long i = 0; i <= N; i++)
		{
			tmp = (double) 2*i+1;
			if (i%2 == 0)
				pi = pi + (1/tmp);
			else
				pi = pi - (1/tmp);	
			
			if ((i % (N/100)) == 0)	System.out.print(i/(N/100) + "%\n");
		}
		System.out.print("Pi = " + 4 * pi);
	}
}
