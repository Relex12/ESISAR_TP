package Nim;

import java.rmi.AccessException;
import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;

public class NimServeur {
	public static void main(String[] args) throws AccessException, RemoteException, AlreadyBoundException {
		
		// METTRE ICI L'ADRESSE IP DE VOTRE SERVEUR
				System.setProperty("java.rmi.server.hostname", "192.168.130.15");
				
		// Crée un objet réel capable de faire des calculs
				NimImpl NimImpl = new NimImpl();
				
		// Crée un serveur ecoutant sur le port 7070, permettant d'accéder à cet objet réel
				NimInt skeleton = (NimInt) UnicastRemoteObject.exportObject(NimImpl, 7070);
				
		// Il y a un registry sur votre machine sur le port 5050
				Registry registry = LocateRegistry.getRegistry("192.168.130.15", 5050);
				
		// On indique au registry qu'un service est présent sur notre machine, avec le nom
				registry.bind("Nim", skeleton);
				System.out.println("Le serveur est prêt ...");
				
			}
}