package tdm999;

import java.rmi.AccessException;
import java.rmi.AlreadyBoundException;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

/**
 * Programme utilisant les services offerts par CalculetteServer
 *
 */
public class CalculetteClient {
	public static void main(String[] args)
			throws AccessException, RemoteException, AlreadyBoundException, NotBoundException {
		// Il y a un registry sur le port 5050 sur votre machine
		Registry registry = LocateRegistry.getRegistry("127.0.0.1", 5050);
		// On récupére un stub qui nous permettra d'accéder au service
		Calculette stub = (Calculette) registry.lookup("calculette");
		// On va maintenant pourvoir s'en servir pour faire un calcul
		System.out.println("Bonjour");
		int a = 5;
		int b = 8;
		int c = stub.somme(a, b);
		System.out.println("Le resultat est " + c);
	}
}