package tdm.tdm4;

import java.text.SimpleDateFormat;
import java.util.List;

public class Test {
	public static void main(String[] args) 	{
		SimpleDateFormat df = new SimpleDateFormat("dd/MM");
		List<LivraisonElementaire> les = PanierData.getData().getLivraisonElementaires();

		for (LivraisonElementaire l : les) 	{
			System.out.println("Qte : "+l.qte+" Produit : "+l.produit.nom+" Date "+df.format(l.dateLiv)+" Consommateur : "+l.commande.consommateur.nom);
		}
	}
}