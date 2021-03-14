package tdm.tdm4;


import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.Random;


public class PanierData
{
	static private PanierData mainInstance;
    
    static public  PanierData getData()
    {
		if (mainInstance==null)
		{
		    mainInstance = new PanierData();
		    mainInstance.initialize();
		}
		return mainInstance;
    }
    
    private List<Producteur> producteurs = new ArrayList<>();
    private List<Produit> produits = new ArrayList<>();
    private List<Consommateur> consommateurs = new ArrayList<>();
    private List<Commande> commandes = new ArrayList<>();
    private List<LivraisonElementaire> livraisonElementaires = new ArrayList<>();
    
    private long idCount = 0;
    
    private PanierData()
    {
    }
    
    private void initialize() 
    {
		loadProducteurAndProduit();
		loadConsommateurAndCommande();
		Collections.shuffle(producteurs, new Random(4));
		Collections.shuffle(produits, new Random(5));
		Collections.shuffle(consommateurs, new Random(6));
		Collections.shuffle(commandes, new Random(7));
		Collections.shuffle(livraisonElementaires, new Random(8));
		
    }
    

	public Long getNextId()
    {
    	idCount++;
    	return idCount;
    }

	private void loadProducteurAndProduit()
	{
		Producteur producteur;
		
		producteur = addProducteur("FERME LEGUMES A ROULETTE");
		addProduit(producteur,3000,"Petit panier",500,0);
		addProduit(producteur,3001,"Grand panier",1300,1);
		
		
		producteur = addProducteur("HAPPY MIEL");
		addProduit(producteur,3010,"Miel ardéche toutes fleurs",650,0);
		addProduit(producteur,3011,"Miel diois",750,1);
		addProduit(producteur,3012,"Pollen",1250,2);
		addProduit(producteur,3013,"Miel lavande",720,3);
		
		producteur = addProducteur("BOULANGER FERME DES LACS");
		addProduit(producteur,3020,"Pain boule",420,0);
		addProduit(producteur,3021,"Brioche",400,1);
		addProduit(producteur,3022,"Pain moulé",450,2);
		addProduit(producteur,3023,"Pain aux graines",510,3);
				
		producteur = addProducteur("FERME AU BON LAIT");
		addProduit(producteur,3030,"Yaourt nature",200,0);
		addProduit(producteur,3031,"Yaourt aux fruits",250,1);
		addProduit(producteur,3032,"Lait",120,2);
		addProduit(producteur,3033,"Faisselle",290,3);
		addProduit(producteur,3034,"Creme fraiche",240,4);

		
	}

	private void addProduit(Producteur producteur, int idProduit, String nomProduit, int prix,int numOrdre)
	{
		produits.add(new Produit(new Long(idProduit), nomProduit, prix,numOrdre,producteur));
		
	}

	private Producteur addProducteur(String nom)
	{
		Long idProd = getNextId();
		Producteur p = new Producteur(idProd, nom);
		producteurs.add(p);
		return p;
	}

	
	private void loadConsommateurAndCommande()
	{
		
		addConsommateur("Leclerc","WILLIAM", new int[][][] {   	{ { 1 , 0 } , { 0 , 0, 0 , 0 } , { 1 , 0 , 0 , 0 } , { 0 , 1 , 0 , 0 , 0 }  } ,
																{ { 1 , 0 } , { 0 , 0, 0 , 0 } , { 1 , 0 , 0 , 0 } , { 0 , 1 , 0 , 0 , 0 }  } ,
																{ { 1 , 0 } , { 0 , 0, 0 , 0 } , { 1 , 0 , 0 , 0 } , { 0 , 1 , 0 , 0 , 0 }  } ,
															});
						

		addConsommateur("Poulin","OLIVIA", new int[][][] {   	{ { 0 , 1 } , { 1 , 0, 0 , 0 } , { 0 , 0 , 2 , 0 } , { 1 , 1 , 0 , 0 , 0 }  } ,
																{ { 0 , 1 } , { 0 , 1, 0 , 0 } , { 0 , 0 , 2 , 0 } , { 1 , 1 , 0 , 0 , 0 }  } ,
																{ { 0 , 0 } , { 0 , 0, 0 , 0 } , { 0 , 0 , 0 , 0 } , { 0 , 0 , 0 , 0 , 0 }  } ,
															});


		addConsommateur("Landry","CHARLOTTE", new int[][][] {   	{ { 1 , 0 } , { 0 , 0, 1 , 0 } , { 0 , 0 , 0 , 3 } , { 0 , 1 , 0 , 0 , 1 }  } ,
																	{ { 1 , 0 } , { 0 , 1, 0 , 0 } , { 0 , 0 , 0 , 3 } , { 0 , 1 , 0 , 0 , 0 }  } ,
																	{ { 1 , 0 } , { 1 , 0, 0 , 0 } , { 0 , 0 , 0 , 3 } , { 0 , 1 , 0 , 0 , 1 }  } ,
																});


		
		addConsommateur("Landry","RAPHAEL", new int[][][] {   	{ { 1 , 0 } , { 0 , 0, 1 , 0 } , { 0 , 0 , 0 , 0 } , { 0 , 0 , 0 , 0 , 0 }  } ,
																{ { 0 , 0 } , { 0 , 1, 1 , 0 } , { 0 , 0 , 0 , 0 } , { 0 , 0 , 0 , 0 , 0 }  } ,
																{ { 0 , 0 } , { 0 , 0, 1 , 0 } , { 0 , 0 , 0 , 0 } , { 0 , 0 , 0 , 0 , 0 }  } ,
															});

		
		addConsommateur("Grenier","BEATRICE", new int[][][] {   	{ { 0 , 2 } , { 0 , 0, 0 , 0 } , { 1 , 2 , 0 , 0 } , { 0 , 2 , 0 , 0 , 0 }  } ,
																	{ { 0 , 2 } , { 0 , 0, 0 , 0 } , { 1 , 2 , 0 , 0 } , { 0 , 3 , 0 , 0 , 0 }  } ,
																	{ { 0 , 3 } , { 0 , 0, 0 , 0 } , { 1 , 2 , 0 , 0 } , { 0 , 2 , 0 , 0 , 0 }  } ,
																});

		
		addConsommateur("Bernier","ALEXIS", new int[][][] {   	{ { 1 , 0 } , { 2 , 1, 0 , 0 } , { 1 , 2 , 0 , 0 } , { 0 , 1 , 0 , 0 , 3 }  } ,
																{ { 1 , 0 } , { 0 , 2, 1 , 0 } , { 1 , 2 , 0 , 0 } , { 0 , 1 , 0 , 2 , 0 }  } ,
																{ { 1 , 0 } , { 0 , 0, 2 , 1 } , { 1 , 2 , 0 , 0 } , { 0 , 1 , 0 , 0 , 3 }  } ,
															});

		
		addConsommateur("Michaud","ZOE", new int[][][] {   	{ { 1 , 0 } , { 0 , 2, 0 , 0 } , { 1 , 0 , 0 , 0 } , { 0 , 1 , 0 , 0 , 0 }  } ,
															{ { 0 , 2 } , { 2 , 1, 0 , 0 } , { 1 , 0 , 0 , 2 } , { 0 , 1 , 0 , 2 , 0 }  } ,
															{ { 0 , 2 } , { 0 , 0, 2 , 1 } , { 1 , 0 , 0 , 2 } , { 0 , 1 , 0 , 10 , 0 }  } ,
														});

		
		addConsommateur("Lachance","NOAH", new int[][][] {   	{ { 0 , 5 } , { 7 , 4, 0 , 0 } , { 1 , 0 , 0 , 0 } , { 0 , 1 , 0 , 10 , 0 }  } ,
																{ { 0 , 6 } , { 0 , 4, 8 , 0 } , { 1 , 11 , 0 , 0 } , { 0 , 1 , 0 , 12 , 0 }  } ,
																{ { 0 , 7 } , { 1 , 2, 5 , 4 } , { 1 , 0 , 5 , 0 } , { 0 , 1 , 0 , 15 , 0 }  } ,
															});

		
		addConsommateur("Gosselin","ALICE", new int[][][] {   	{ { 1 , 0 } , { 0 , 2, 0 , 0 } , { 1 , 0 , 0 , 0 } , { 0 , 1 , 0 , 8 , 0 }  } ,
																{ { 1 , 0 } , { 0 , 0, 4 , 0 } , { 1 , 0 , 7 , 0 } , { 0 , 1 , 0 , 0 , 0 }  } ,
																{ { 1 , 0 } , { 0 , 0, 0 , 6 } , { 1 , 9 , 0 , 0 } , { 0 , 1 , 0 , 7 , 0 }  } ,
															});

		
		addConsommateur("Savard","NATHAN", new int[][][] {   	{ { 1 , 0 } , { 2 , 0, 0 , 0 } , { 1 , 2 , 0 , 0 } , { 1 , 0 , 0 , 0 , 5 }  } ,
																{ { 1 , 0 } , { 0 , 0, 6 , 0 } , { 1 , 0 , 0 , 0 } , { 5 , 0 , 0 , 0 , 0 }  } ,
																{ { 1 , 0 } , { 0 , 0, 0 , 1 } , { 1 , 0 , 0 , 4 } , { 3 , 0 , 0 , 0 , 2 }  } ,
															});


		addConsommateur("Boudreau","EMMA", new int[][][] {   	{ { 1 , 0 } , { 0 , 3, 0 , 0 } , { 0 , 0 , 0 , 0 } , { 0 , 0 , 1 , 0 , 0 }  } ,
																{ { 1 , 0 } , { 4 , 0, 1 , 0 } , { 0 , 0 , 10 , 0 } , { 0 , 2 , 0 , 0 , 0 }  } ,
																{ { 1 , 0 } , { 0 , 0, 0 , 10 } , { 0 , 0 , 0 , 10 } , { 3 , 0 , 0 , 0 , 0 }  } ,
															});


		addConsommateur("Demers","THOMAS", new int[][][] {   	{ { 1 , 0 } , { 0 , 0, 0 , 0 } , { 1 , 0 , 4 , 0 } , { 0 , 1 , 0 , 0 , 5 }  } ,
																{ { 1 , 0 } , { 0 , 0, 1 , 4 } , { 1 , 0 , 0 , 0 } , { 0 , 1 , 0 , 7 , 6 }  } ,
																{ { 1 , 0 } , { 1 , 5, 0 , 0 } , { 1 , 2 , 3 , 0 } , { 0 , 1 , 0 , 0 , 0 }  } ,
															});
				
		
	}

	private Long addConsommateur(String nom, String prenom, int[][][] cdes)
	{
		Consommateur consommateur = new Consommateur(getNextId(), nom.toUpperCase(), prenom.toLowerCase(), "0612121212");
		
		Commande commande = new Commande(getNextId(), null, consommateur);
		
		Date d1 = toDate("11/01/2018");
		Date d2 = toDate("18/01/2018");
		Date d3 = toDate("25/01/2018");
		
		
		addLivraison(d1,cdes[0],commande);
		addLivraison(d2,cdes[1],commande);
		addLivraison(d3,cdes[1],commande);
		
		consommateurs.add(consommateur);
		commandes.add(commande);
		
		return consommateur.id;
	}
	
	
	private void addLivraison(Date d1, int[][] is, Commande commande)
	{
		addLivraisonElem(d1,3000,is[0],commande);
		addLivraisonElem(d1,3010,is[1],commande);
		addLivraisonElem(d1,3020,is[2],commande);
		addLivraisonElem(d1,3030,is[3],commande);
		
	}

	private void addLivraisonElem(Date d1, int prefix, int[] qtes, Commande commande)
	{
		for (int i = 0; i < qtes.length; i++)
		{
			int qte = qtes[i];
			
			if (qte!=0)
			{
			
				Long idProduit = new Long(prefix+i);
				
				Produit produit = findProduitById(idProduit);
				LivraisonElementaire le = new LivraisonElementaire(getNextId(), qte, produit, d1,commande);
				livraisonElementaires.add(le);
			}
		}
		
	}

	private Produit findProduitById(Long id)
	{
		return produits.stream().filter(e->e.id.equals(id)).findAny().get();
	}

	private Date toDate(String txt)
	{
		String pattern = "dd/MM/yyyy";
		
		SimpleDateFormat df = new SimpleDateFormat(pattern);
		try
		{
			return df.parse(txt);
		} 
		catch (ParseException e)
		{
			throw new RuntimeException("Erreur sur le parsing de "+txt);
		}
	}
	
	
	public List<Producteur> getProducteurs()
	{
		return producteurs;
	}

	public List<Produit> getProduits()
	{
		return produits;
	}

	public List<Consommateur> getConsommateurs()
	{
		return consommateurs;
	}

	public List<Commande> getCommandes()
	{
		return commandes;
	}

	public List<LivraisonElementaire> getLivraisonElementaires()
	{
		return livraisonElementaires;
	}

	public static void main(String[] args)
	{
		List<Produit> prods = PanierData.getData().getProduits();
		for (Produit produit : prods)
		{
			System.out.println("Produit : "+produit.nom+" de "+produit.producteur.nom);
		}
		
		
		SimpleDateFormat df = new SimpleDateFormat("dd/MM");
		List<LivraisonElementaire> les = PanierData.getData().getLivraisonElementaires();
		
		for (LivraisonElementaire l : les)
		{
			System.out.println("Qte : "+l.qte+" Produit : "+l.produit.nom+" Date "+df.format(l.dateLiv)+" Consommateur : "+l.commande.consommateur.nom);
		}
	}
	
}
