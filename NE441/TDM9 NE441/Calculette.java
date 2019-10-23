package tdm999;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Calculette extends Remote {
	public int somme(int a, int b) throws RemoteException;
}