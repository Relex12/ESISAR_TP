package Pi;

import java.util.ArrayList;

public class PiMultiT extends Thread
{
	long debut;
	long fin;
	double somme;
	static long N = 50_000_000_000L;
	static int nbThreads = 8;
	
	public PiMultiT (long d, long f)
	{
		this.debut = d;
		this.fin = f;
	}
	
	
	public void run() 
	{
		this.somme = 0;
		double tmp;
		
		for (long i = debut; i < fin; i++)
		{
			tmp = (double) 2*i+1;
			if (i%2 == 0)
				this.somme = this.somme + (1/tmp);
			else
				this.somme = this.somme - (1/tmp);	
		}
	}
	
	public static void main(String[] args) 
	{
		ArrayList<PiMultiT> listTh = new ArrayList<PiMultiT>();
		
		
		listTh.add(new PiMultiT(0, N/nbThreads));
		
		for (int i = 1; i < nbThreads; i++) 
		{
			listTh.add(new PiMultiT(N/nbThreads*i + 1, N/nbThreads*(i+1)));
		}
		
		for (PiMultiT piMultiT : listTh) 
		{
			piMultiT.start();
		}
		
		for (PiMultiT piMultiT : listTh) 
		{
			try {
				piMultiT.join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		double Pi = 0;
		for (PiMultiT piMultiT : listTh) 
		{
			Pi += piMultiT.somme;
		}
		
/*		PiMultiT T1 = new PiMultiT(0, N/nbThreads);
		PiMultiT T2 = new PiMultiT(N/nbThreads + 1, N);
		
		T1.start();		T2.start();
		
		try {	T1.join();	T2.join();	} catch (InterruptedException e) {	e.printStackTrace();	}
		
		double Pi = T1.somme + T2.somme;
		
*/		System.out.print("Pi = " + 4 * Pi);

	}
}
