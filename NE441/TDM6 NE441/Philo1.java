
public class Philo1 extends Thread
{
	static int nbThreads = 50;
	int numPhi;
	
	public Philo1(int numPhi) 
	{
		this.numPhi = numPhi;
	}
	
	@Override
	public void run() 
	{
		int rand;
		while (true)
		{
			rand = (int) (10000 * Math.random());
			System.out.println("Le philosophe " + this.numPhi + " commence à discuter");
			try {	Thread.sleep(rand);	} 
			catch (InterruptedException e) { e.printStackTrace();}
			
			rand = (int) (10000 * Math.random());
			System.out.println("Le philosophe " + this.numPhi + " commence à manger");
			try {	Thread.sleep(rand);	} 
			catch (InterruptedException e) { e.printStackTrace();}
		}
	}
	
	public static void main(String[] args) 
	{
		for (int i = 1; i < nbThreads; i++) 
		{
			Philo1 philosophe = new Philo1 (i);
			philosophe.start();
		}
	}
}
