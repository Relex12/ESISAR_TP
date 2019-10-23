package tdm_5;

import java.awt.List;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.ArrayList;

public class TailleImage {

	public static void main(String[] args) {
		int taille_image = 0;
		System.out.println("Demarrage du calcul de la taille des images ...");

		// connection

		// Creation de la socket
		Socket socket = new Socket();

		// Connexion au serveur
		InetSocketAddress adrDest = new InetSocketAddress("127.0.0.1", 7000);
		try {
			socket.connect(adrDest);
		} catch (IOException e) {
			e.printStackTrace();
		}

		// Envoi de la requete
		byte[] bufE = new String("Le meilleur binome est le binome 5").getBytes();
		OutputStream os = null;
		try {
			os = socket.getOutputStream();
		} catch (IOException e) {
			e.printStackTrace();
		}
		try {
			os.write(bufE);
		} catch (IOException e) {
			e.printStackTrace();
		}
		//System.out.println("Message envoye");

		int i = 0;
		String reponse = null;
		int lu = 0;
		int a_lire1 = 0;
		int fuzzing = 0;
		int lecture = 0;
		byte[] bufR = new byte[2048];
		InputStream is = null;
		int lenBufR = 0;
		
		ArrayList<byte[]> images = new ArrayList<byte[]>();
		ArrayList<Integer> tailleImages = new ArrayList<Integer>();
		
		// lecture
		while (i < 50) {

			// Attente de la reponse
			try {
				is = socket.getInputStream();
			} catch (IOException e) {
				System.out.println("***********************ERREUR***********************");
			}
			try {
				lenBufR = is.read(bufR);
			} catch (IOException e) {
				System.out.println("***********************ERREUR***********************");
			}

			if (lenBufR != -1) {
				reponse = new String(bufR, 0, 20);
				//System.out.println("nouvelle lecture :" + reponse);
			}

			int decalageUTF8 = 0;
			
			while (reponse != null && i < 50) {
				taille_image = Integer.valueOf(reponse.split(" ")[lecture]);
				decalageUTF8 += conversionUTF8(taille_image) + 1;
				//System.out.println("1*-*-*-*-*-*-" + decalageUTF8);
				//System.out.println("/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/La taille de l'image " + i + " est " + taille_image);
				tailleImages.add(taille_image);
				byte[] temp_im = new byte[taille_image];
				lecture++;

				while (lu < taille_image) {

					/////////////////////////////////// lecture entete fuzzing
					if (reponse.length() == 0) {
						String temp = reponse;
						//System.out.println("***********************0***********************");
						try {
							is = socket.getInputStream();
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}
						try {
							lenBufR = is.read(bufR);
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}

						if (lenBufR != -1) {
							reponse = new String(bufR, 0, 6);
							// //System.out.println("nouvelle lecture :" + reponse);
						}
						fuzzing = Integer.valueOf(reponse.split(" ")[lecture]);
						decalageUTF8 = conversionUTF8(fuzzing);
						//System.out.println("2*-*-*-*-*-*-" + decalageUTF8);
					} else if (reponse.length() == 1) {
						String temp = reponse;
						//System.out.println("************************1**********************");
						try {
							is = socket.getInputStream();
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}
						try {
							lenBufR = is.read(bufR);
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}

						if (lenBufR != -1) {
							reponse = new String(bufR, 0, 6);
							//System.out.println("nouvelle lecture :" + reponse);
						}
						fuzzing = Integer.valueOf(temp + reponse.split(" ")[lecture]);
						decalageUTF8 = 0;
						decalageUTF8 += conversionUTF8(fuzzing) - 1;
						//System.out.println("3*-*-*-*-*-*-" + decalageUTF8);
					}

					else { //normal fuzzing
						fuzzing = Integer.valueOf(reponse.split(" ")[lecture]);
						decalageUTF8 += conversionUTF8(fuzzing);
						//System.out.println("4*-*-*-*-*-*-" + decalageUTF8);
					}

					//System.out.println("fuzzing : " + fuzzing);

					if (reponse.contains(" ")) { //espace
						lecture++;
						decalageUTF8++;
						//System.out.println("5*-*-*-*-*-*-" + decalageUTF8);
					}

					/////////////////////////////////// lecture entete valide

					if (reponse.length() == 0 + conversionUTF8(fuzzing) ) {
						decalageUTF8 = 1;
						lecture = 1; //il y a un espace a lire
						//System.out.println("**********************5************************");
						try {
							is = socket.getInputStream();
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}
						try {
							lenBufR = is.read(bufR);
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}

						if (lenBufR != -1) {
							reponse = new String(bufR, 0, 6);
							//System.out.println("nouvelle lecture :" + reponse);
						}
						a_lire1 = Integer.valueOf(reponse.split(" ")[lecture]);
						decalageUTF8 += conversionUTF8(a_lire1);
						//System.out.println("12*-*-*-*-*-*-" + decalageUTF8);
					} else if (reponse.length() == 1 + conversionUTF8(fuzzing) ) {
						decalageUTF8 = 0;
						lecture = 0;
						//System.out.println("**********************3************************");
						try {
							is = socket.getInputStream();
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}
						try {
							lenBufR = is.read(bufR);
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}

						if (lenBufR != -1) {
							reponse = new String(bufR, 0, 6);
							//System.out.println("nouvelle lecture :" + reponse);
						}
						a_lire1 = Integer.valueOf(reponse.split(" ")[lecture]);
						decalageUTF8 += conversionUTF8(a_lire1);
						//System.out.println("6*-*-*-*-*-*-" + decalageUTF8);
					} else if (reponse.length() == 2 + conversionUTF8(fuzzing)) {
						decalageUTF8 = 0;
						lecture = 0;
						String temp = reponse.split(" ")[1];
						//System.out.println("**************************4********************");
						try {
							is = socket.getInputStream();
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}
						try {
							lenBufR = is.read(bufR);
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}

						if (lenBufR != -1) {
							reponse = new String(bufR, 0, 6);
						}
						//System.out.println("nouvelle lecture :" + reponse + " premier char " + temp);
						
						a_lire1 = Integer.valueOf(temp + reponse.split(" ")[lecture]);
						
						decalageUTF8 += conversionUTF8(a_lire1)-1;
						
						//System.out.println("11*-*-*-*-*-*-" + decalageUTF8);
					} else { //normal valide
						a_lire1 = Integer.valueOf(reponse.split(" ")[lecture]);
						decalageUTF8 += conversionUTF8(a_lire1);
						//System.out.println("7*-*-*-*-*-*-" + decalageUTF8);
					}

					if (reponse.contains(" ")) {//espace
						decalageUTF8++;
						//System.out.println("8*-*-*-*-*-*-" + decalageUTF8);
					}

					//System.out.println("a_lire : " + a_lire1);

					///////////////////////////////////

					decalageUTF8 += fuzzing + a_lire1;
					//System.out.println("9*-*-*-*-*-*-" + decalageUTF8);

					if (decalageUTF8 > 2047) {
						//System.out.println("************************relire  mem**********************");
						decalageUTF8 = decalageUTF8 - lenBufR;
						//System.out.println("10*-*-*-*-*-*-" + decalageUTF8);
						try {
							is = socket.getInputStream();
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}
						try {
							lenBufR = is.read(bufR);
						} catch (IOException e) {
							System.out.println("***********************ERREUR***********************");
						}
						

						if (lenBufR != -1) {
							reponse = new String(bufR, 0, 6);
							//System.out.println("nouvelle lecture sans decalage :" + reponse);
							reponse = new String(bufR, decalageUTF8, lenBufR - decalageUTF8);
							//System.out.println("avec :" + reponse);
						}
					}
					/////////////////////////////////////////////////////
					reponse = new String(bufR, decalageUTF8, lenBufR - decalageUTF8);
					lu += a_lire1;

					//System.out.println("---------------------------- decalage : " + decalageUTF8);
					//System.out.println(".........................................reponse : '" + reponse + "'");

					lecture = 0;
					//System.out.println("taille lu " + lu + " / " + taille_image);
				}
				lu = 0;
				i++;
			}

		}

		// Fermeture de la socket
		try {
			System.out.println("on a fini");
			socket.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		//System.out.println("Fin du programme");
	}

	static int conversionUTF8(int entier) {
		int resultat;

		resultat = (int) (Math.log(entier) / Math.log(10));
		// //System.out.println("resultat conversion de "+entier +" "+(resultat+1));
		return resultat + 1;
	}
}