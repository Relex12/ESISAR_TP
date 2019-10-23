package Nim;

import java.rmi.RemoteException;

public class NimImpl implements NimInt  {
	int nbpion = 100;
	int nbjeton = 100;
	int nballumette = 100;
	
	boolean[] tourJ = {false,false};
	
	int id = 0;
	
	public String joue(int idjoueur, int del, Tas tas) throws RemoteException{
		if( del < 1 || del > 3) return "Impossible d'enlever " + del;
		
		if(tourJ[idjoueur]) {
			switch (tas) {
			case Allumette:
					if(nballumette - del < 0) return "Vous ne pouvez pas enlever autant d'allumettes";
					else {
						nballumette -= del;
						if(nbpion == 0 && nbjeton == 0 && nballumette == 0 ) return "Gagne";
						else {
							tourJ[0] = !tourJ[0];
							tourJ[1] = !tourJ[1];
							return "Partie toujours en cours";
						}
					}
			case Jeton: 
				if(nballumette - del < 0) return "Vous ne pouvez pas enlever autant de jeton";
				else {
					nbjeton -= del;
					if(nbpion == 0 && nbjeton == 0 && nballumette == 0 ) return "Gagne";
					else {
						tourJ[0] = !tourJ[0];
						tourJ[1] = !tourJ[1];
						return "Partie toujours en cours";
					}
				}
			case Pion: 
				if(nbpion - del < 0) return "Vous ne pouvez pas enlever autant de pion";
				else {
					nbpion -= del;
					if(nbpion == 0 && nbjeton == 0 && nballumette == 0 ) return "Gagne";
					else {
						tourJ[0] = !tourJ[0];
						tourJ[1] = !tourJ[1];
						return "Partie toujours en cours";
					}
				}
				
			default:
				return "Erreur";
			}
		}
		
		else return "Vous n'avez pas le droit de jouer";
	}
	
	public boolean tour(int idjoueur) throws RemoteException{
		
		if(idjoueur < 2 && idjoueur >= 0)	{
			return tourJ[idjoueur];
		}
		
		else return false;
		
	}
	
	public String status() throws RemoteException{
		String str =  "il reste " + nbpion + " pions , " + nballumette + " allumettes , " + nbjeton + " jetons.";
		return str;
	}
	
	public int takeId() throws RemoteException{
		if(id == 0) {
			id++;
			return 0;
		}
		if(id == 1) {
			id++;
			tourJ[0] = true;
			return 1;
		}
		else {
			return -1;
		}
	}

}