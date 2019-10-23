package Nim;

import java.rmi.AccessException;
import java.rmi.AlreadyBoundException;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class CreateRegistry {
	public static void main(String[] args)
			throws AccessException, RemoteException, AlreadyBoundException, InterruptedException {
// Il y a un registry sur le port 5050
		@SuppressWarnings("unused")
		Registry registry = LocateRegistry.createRegistry(5050);
		System.out.println("Le registry est prêt ...");
// Indispensable pour que le registry continue
		while (true) {
			Thread.sleep(100000);
		}
	}
}