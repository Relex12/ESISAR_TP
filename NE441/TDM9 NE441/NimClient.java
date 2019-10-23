package Nim;

import java.rmi.AccessException;
import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class NimClient {

	public static void main(String[] args)
			throws AccessException, RemoteException, AlreadyBoundException, NotBoundException, InterruptedException {
		// Il y a un registry sur le port 5050 sur votre machine
		Registry registry = LocateRegistry.getRegistry("192.168.130.15", 5050);
		// On récupére un stub qui nous permettra d'accéder au service
		NimInt stub = (NimInt) registry.lookup("Nim");

		// On va maintenant pourvoir s'en servir pour faire un calcul


		int myId = stub.takeId();
		System.out.println("Mon ID est " + myId);
		if (myId == -1) 		System.out.println("il y a trop de joueur");

		else {
			String str= new String ("");
			int Inttas;
			int aEnlever;
			Tas tas;
			Scanner sc = new Scanner(System.in);

			while (!str.equals("Gagne")) {
				
				if (stub.tour(myId)) {
//					System.out.println("test");
					str = new String(stub.status());
					System.out.println(str);
					Inttas = 0;
					aEnlever = 0;
					while (Inttas < 1 || Inttas > 3) {
						System.out.println("Entrez votre tas (entre 1 et 3)");
						Inttas = sc.nextInt();
					}
					while (aEnlever < 1 || aEnlever > 3) {
						System.out.println("Entrez votre nombre a enlever (entre 1 et 3)");
						aEnlever = sc.nextInt();
					}
					switch (Inttas) {
					case 1:
						tas = Tas.Pion;
						break;
					case 2:
						tas = Tas.Allumette;
						break;
					case 3:
						tas = Tas.Jeton;
						break;
					default:
						tas = Tas.Jeton;
						break;
					}
					str = new String(stub.joue(myId, aEnlever, tas));
					System.out.println(str);
				}
				
				Thread.sleep(1000);
			}
			sc.close();
		}
		
	}

}
