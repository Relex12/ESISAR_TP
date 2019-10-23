import tdm.tdm07.exo3.checker.CodeChecker;

public class Philo2 extends Thread {
	static int nbThreads = 50;
	int numPhi;
	int attenteLiberation = 1000; 	// en millisecondes
	static Arbitre Arbitre = new Arbitre();

	public Philo2(int numPhi, Arbitre a) {
		this.numPhi = numPhi;
	}

	@Override
	public void run() {
		int rand;
		while (true) {
			rand = (int) (10000 * Math.random());
			System.out.println("Le philosophe " + this.numPhi + " commence à discuter");
			try {
				Thread.sleep(rand);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			
			while (!Arbitre.autorisation(this.numPhi)) {
//				System.out.println("Le philosophe " + this.numPhi + " attend les baguettes");
				try {
					Thread.sleep(attenteLiberation);
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
			rand = (int) (10000 * Math.random());
			System.out.println("Le philosophe " + this.numPhi + " commence à manger");
			CodeChecker.startEating(numPhi);
			try {
				Thread.sleep(rand);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			System.out.println("Le philosophe " + this.numPhi + " a fini de manger");
			Arbitre.liberation(this.numPhi);
			CodeChecker.stopEating(numPhi);
		}
	}

	public static void main(String[] args) {
		Arbitre.initializeTable();
		
		for (int i = 0; i < nbThreads; i++) {
			Philo2 philosophe = new Philo2(i, Arbitre);
			philosophe.start();
		}
	}

	static class Arbitre {
		int c;
// private Object mutex = new Object();
		static boolean table[] = new boolean[nbThreads];

		void initializeTable() {
			for (int i = 0; i < nbThreads; i++)
				table[i] = true;
		}

		synchronized boolean autorisation(int numPhilo) {
			
				if (table[numPhilo] && table[(numPhilo-1+nbThreads) % nbThreads]) {
					table[numPhilo] = false;
					table[(numPhilo-1+nbThreads) % nbThreads] = false;
					return true;
				}
				else 	return false;
		}

		synchronized void liberation(int numPhilo) {
//				if ( !table[numPhilo] && !table[(numPhilo+1) % nbThreads]) {		// on vérifie qu'il manque bien les deux baguettes sur la table
				table[numPhilo] = true;
				table[(numPhilo-1+nbThreads) % nbThreads] = true;
//				}
			
		}

	}

}
