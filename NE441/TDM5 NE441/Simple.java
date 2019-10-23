package Seq;

public class Simple extends Thread
{
	int numTh;
	
	public Simple (int numTh) 
	{
		this.numTh = numTh;
	}
	
	public void run() 
	{
		System.out.println("la tache " + this.numTh + " est commencee\n");
		try {
			Thread.sleep(500);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("la tache " + this.numTh + " est terminee\n");
	}
	
	public static void main(String[] args) throws InterruptedException 
	{
		Simple s1 = new Simple(1);
		Simple s2 = new Simple(2);
		Simple s3 = new Simple(3);
		Simple s4 = new Simple(4);
		Simple s5 = new Simple(5);
		Simple s6 = new Simple(6);
		
		s1.start();
		s1.join();
		
		s2.start();	s3.start(); s4.start();
		s2.join(); s3.join();
		
		s5.start();
		s5.join();
		
		s4.join();
		
		s6.start(); s6.join();
	}
}
