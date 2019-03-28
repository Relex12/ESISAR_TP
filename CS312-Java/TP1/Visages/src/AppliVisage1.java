/**
 * J<i>ava</i> U<i>tilities</i> for S<i>tudents</i>
 */

import javax.swing.JFrame;

public class AppliVisage1 {
	public static void main(String[] args) {
		JFrame laFenetre = new JFrame("VISAGE ANIME");
		laFenetre.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		laFenetre.setSize(512, 512);
		Dessin d = new Dessin();
		laFenetre.add(d);
		laFenetre.setVisible(true);
		// creation d'un objet VisageRond
		VisageRond v1 = new VisageRond();
		// on rajoute cet objet la z�ne de dessin
		d.ajouterObjet(v1);
		// la boucle d'animation
		while (true) {
			// le visage a atteint un des bords, il change de direction
			if (v1.bordAtteint())
				v1.inverserDxEtDy();
			// le visage effectue un déplacement élémentaire
			v1.deplacer();
			// la zone de dessin se réaffiche
			d.repaint();
			// un temps de pause pour avoir le temps de voir le nouveau dessin
			d.pause(50);
		}
	}
} // AppliVisage1
