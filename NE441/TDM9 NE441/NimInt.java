package Nim;

import java.rmi.Remote;
import java.rmi.RemoteException;

public interface NimInt extends Remote {

		public String joue (int idjoueur, int del, Tas tas) throws RemoteException;
		public boolean tour (int joueur) throws RemoteException;
		public int takeId () throws RemoteException;
		public String status () throws RemoteException; 
}
