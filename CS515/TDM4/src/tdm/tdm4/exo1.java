package tdm.tdm4;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;
import java.util.function.Function;
import java.util.stream.Collectors;

public class exo1 {

	@SuppressWarnings("rawtypes")
	private static final Function LivraisonElementaire = null;

	public static void main(String[] args) throws ParseException {
		Date d = new SimpleDateFormat("dd/MM/YYYY").parse("11/01/2018");

		Long id = PanierData.getData().getProducteurs().stream()
				.filter(e->e.nom.compareTo("HAPPY MIEL")==0).findFirst().get().id;
		
		List<LivraisonElementaire> liste = sortDateProducteur(d, id);
		
		StringBuilder sb = new StringBuilder();
		sb.append("<html><body><table cellspacing=\"0\" border=\"0\">");
		sb.append("<tr>");
		sb.append("<td td style=\"border: 1px solid #000000;\">Consommateur</td>");
		sb.append("<td td style=\"border: 1px solid #000000;\">Produits commandés</td>");
		sb.append("</tr>");
		
		for (LivraisonElementaire le : liste) {
			sb.append("<tr>");
			sb.append("<td td style=\"border: 1px solid #000000;\">"+le.commande.consommateur.nom+" "+le.commande.consommateur.prenom+"</td>");
			sb.append("<td td style=\"border: 1px solid #000000;\">"+le.qte+" "+le.produit.nom+"</td>");
			sb.append("</tr>");
		}
		
		sb.append("</table></body></html>");
		System.out.println(sb.toString());
	}
	
	@SuppressWarnings("unchecked")
	static List<LivraisonElementaire> sortDateProducteur(Date d, Long id) {
		return (List<LivraisonElementaire>) (PanierData.getData().getLivraisonElementaires().stream()
				.filter(e->e.dateLiv.compareTo(d)==0).filter((e->e.produit.producteur.id==id))
				.sorted((e1, e2)-> -e1.produit.numOrdre + e2.produit.numOrdre))
				.sorted((e1,e2)->e1.commande.consommateur.nom.compareTo(e2.commande.consommateur.nom))
				.map(LivraisonElementaire).collect(Collectors.toList());
	}
}
