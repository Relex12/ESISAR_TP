/**
 * J<i>ava</i> U<i>tilities</i> for S<i>tudents</i>
 */
import java.awt.Graphics;

/**
 * Cette classe permet de modéliser un visage de forme ovale.
 * <p>Le repère graphique est défini avec son origine en haut
 * à gauche de la zone de dessin, l'axe des x horizontal et l'axe
 * des y vertical vers le bas.
 * <p>Un visage est défini par :
 * <ul>
 * <li>
 * les coordonnées xhg, yhg du coin supérieur gauche du rectangle
 * englobant,</li>
 * <li>
 * une largeur et une hauteur,</li>
 * <li>
 * un déplacement élémentaire horizontal (dx) et un déplacement
 * élémentaire vertical (dy).</li>
 * </ul>
 *
 * <center><img SRC="figurevisage.gif" NOSAVE height=266 width=300 align=ABSCENTER></center>
 *
 */
public class VisageRond  {
   //---------------------------------------------------------
   // Les constantes de la classe VisageRond
   //---------------------------------------------------------
   /**
    * Largeur minimale pour un VisageRond.
    */
   public static final int LARGEUR_MIN = 15;
   /**
    * Hauteur minimale pour un VisageRond.
    */
   public static final int HAUTEUR_MIN = 15;
   //-------------------------------------------------------------
   // Les attributs (variables d'instance) de la classe VisageRond
   //-------------------------------------------------------------
   /**
    * La zone de dessin dans laquelle se trouve le VisageRond.
    */
   private Dessin d;
   /**
    * abscisse coin supérieur gauche du rectangle englobant le visage.
    */
   private int xhg = 0;
   /**
    * ordonnée coin supérieur gauche du rectangle englobant le visage.
    */
   private int yhg = 0;
   /**
    * largeur du visage.
    * Par défaut 50 pixels.
    */
   private int largeur = 50;

   /**
    * hauteur du visage.
    * Par défaut 50 pixels.
    */
   private int hauteur = 50;

   /**
    * déplacement élémentaire horizontal du visage.
    * Par défaut 5 pixels.
    */
   private int dx = 5;

   /**
    * deplacement élémentaire vertical du visage.
    * Par défaut 5 pixels.
    */
   private int dy = 5;

   //---------------------------------------------------------
   // Les constructeurs de la classe VisageRond
   //---------------------------------------------------------

   /**
    * Constructeur avec valeurs par défaut.
    * Crée un visage de taille 50x50 dont le coin supérieur gauche du rectangle
    * englobant est situé au point (0,0) de la zone de dessin. Ce visage est 
    * également doté d'un déplacement élémentaire horizontal et vertical de
    * +5 pixels.
    */
   public VisageRond(){}

   /**
    * Constructeur avec positionnement du visage.
    * Crée un visage de taille 50x50 mais dont la position du coin supérieur
    * gauche du rectangle englobant est fixée à la création. 
    * Ce visage est doté d'un déplacement élémentaire horizontal et vertical de
    * +5 pixels.
    * @param xg abscisse du coin supérieur gauche du rectangle englobant.
    * @param yg abscisse du coin supérieur gauche du rectangle englobant.
    */
   public VisageRond(int xg, int yg){
         xhg = xg;
         yhg = yg;
   }
   /**
    * Constructeur avec positionnement du visage et définition de sa taille.
    * Crée un visage dont les diemensions et la position du coin supérieur
    * gauche du rectangle englobant sont fixées à la création. 
    * Ce visage est doté d'un déplacement élémentaire horizontal et vertical de
    * +5 pixels.
    * @param xg abscisse du coin supérieur gauche du rectangle englobant.
    * @param yg abscisse du coin supérieur gauche du rectangle englobant.
    * @param larg largeur du visage. La largeur doit être supérieure à LARGEUR_MIN
    * @param larg hauteur du visage. La hauteur doit être supérieure à HAUTEUR_MIN
    *
    * @see VisageRond#LARGEUR_MIN
    * @see VisageRond#HAUTEUR_MIN
    */
  public VisageRond(int xg, int yg, int larg, int haut){
         xhg = xg;
         yhg = yg;

         largeur = Math.max(larg,LARGEUR_MIN);
         hauteur = Math.max(haut,HAUTEUR_MIN);
	}
  /**
   * Donne la valeur du déplacement élémentaire horizontal.
   * @return valeur de dx, déplacement élémentaire horizontal.
   */
	public int  getDx() {return dx;}
  /**
   * Fixe du déplacement élémentaire horizontal.
      * @param v  Valeur à affecter à dx, déplacement élémentaire horizontal.
      */
	public void setDx(int  v) {this.dx = v;}
   /**
      * Donne la valeur du déplacement élémentaire vertical.
      * @return Valeur de dy, déplacement élémentaire vertical.
      */
	public int getDy() {return dy;}
  /**
   * Fixe la valeur du déplacement élémentaire vertical.
   * @param v  Valeur de dy, déplacement élémentaire vertical.
   */
	public void setDy(int  v) {this.dy = v;}
  /**
   * Inverse sens du déplacement horizontal.
   */
	public void inverserDx(){dx = -dx;}
  /**
   * Inverse sens du déplacement vertical.
   */
	public void inverserDy(){dy = -dy;}  
  /**
   * Inverse sens des déplacements horizontal et vertical.
   */
	public void inverserDxEtDy(){dx = -dx;dy = -dy;}
  /**
   * Fait effectuer au visage un déplacement élémentaire.
   * La position du coin supérieur gauche du visage est modifiée en lui ajoutant
   * le déplacement élémentaire défini par dx et dy.
   */
	public void deplacer(){xhg += dx;yhg += dy;}
  /** 
   * Evalue si le visage atteint le bord gauche de la zone de dessin.
   * @return <code>true</code> si le rectangle englobant le visage 
   *         intersecte le coté gauche de la zone de dessin, <code>
   *         false</code> sinon.
   */
  public boolean bordGaucheAtteint(){return (xhg < 0);}
  /** 
   * Evalue si le visage atteint le bord droit de la zone de dessin.
   * @return <code>true</code> si le rectangle englobant le visage 
   *         intersecte le coté droit de la zone de dessin, <code>
   *         false</code> sinon.
   */
  public boolean bordDroitAtteint(){return ((xhg + largeur) > d.getLargeur());}
  /** 
   * Evalue si le visage atteint le bord haut de la zone de dessin.
   * @return <code>true</code> si le rectangle englobant le visage 
   *         intersecte le cot� haut de la zone de dessin, <code>
   *         false</code> sinon.
   */
  public boolean bordHautAtteint(){return (yhg < 0);}
  /** 
   * Evalue si le visage atteint le bord bas de la zone de dessin.
   * @return <code>true</code> si le rectangle englobant le visage 
   *         intersecte le coté bas de la zone de dessin, <code>
   *         false</code> sinon.
   */
  public boolean bordBasAtteint(){return ((yhg + hauteur) >= d.getHauteur());}
  /** 
   * Evalue si le visage atteint l'un des bords  de la zone de dessin.
   * @return <code>true</code> si le rectangle englobant le visage 
   *         intersecte l'un des cotés de la zone de dessin, <code>
   *         false</code> sinon.
   */
	public boolean bordAtteint(){return  bordDroitAtteint() || bordGaucheAtteint() || bordHautAtteint() || bordBasAtteint();}
  /**
   * fixe la zone de dessin dans laquelle le visage est affiché.
   * @param d référence de la zone de dessin associée au Visage
   * @see Dessin
   * @see Dessinable
   */
  public void setDessin(Dessin d){this.d = d;}
  /**
   * affiche le visage.
   * @param g le contexte graphique de la zone de dessin en charge de l'affichage.
   * @see java.awt.Graphics
   * @see Dessinable
   */
  public void dessiner(Graphics g){
  	// dessiner le contour du visage
  	g.drawOval(xhg , yhg, largeur ,hauteur);
  	// dessiner la bouche
  	g.drawLine(xhg + largeur / 4, yhg + (2*hauteur)/3, xhg + (3*largeur)/4, yhg + (2*hauteur)/3);
  	// dessiner les yeux
  	int largeurOeil = largeur /5;
  	int hauteurOeil =hauteur/5;
  	g.drawOval(xhg + largeurOeil, yhg + hauteurOeil, largeurOeil, hauteurOeil);
  	g.drawOval(xhg + 3 * largeurOeil, yhg + hauteurOeil, largeurOeil, hauteurOeil);      
	}  
} // VisageRond


















