package tdm1.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.stream.Collectors;

public class DataSource 
{
    
    static private DataSource mainInstance;
    
    static public  DataSource getDataSource()
    {
	if (mainInstance==null)
	{
	    mainInstance = new DataSource();
	    mainInstance.initialize();
	}
	return mainInstance;
    }
    
    List<Operateur> operateurs = new ArrayList<>();
    List<Departement> departements = new ArrayList<>();
    List<Region> regions = new ArrayList<>();
    List<Client> clients = new ArrayList<>();
    List<Appel> appels = new ArrayList<>();
    
    Map<String, Client> mapNumtelClient = new HashMap<>();
    
    private DataSource()
    {
	
    }
   
    private static int NB_APPEL = 2_000_000;
    
    private static int NB_CLIENT = 20_000;
    
    private static String[] prenomHomme = { "Acton","Erasmus","Guy","Tyrone","Caldwell","Gregory","Quinlan","Leroy","Brody","Ulysses","Branden","Kermit","Daquan","Richard","Graiden","Armando","Gannon","Armando","Basil","Declan","Harding","Rafael","Conan","Lyle","Phillip","Christopher","Malcolm","Aristotle","Christian","Dane","Kaseem","Jackson","Neil","Leo","Channing","Gage","Lev","Tarik","Amery","Randall","Timon","Bruce","Uriah","Coby","Hilel","Valentine","Kareem","Leonard","Brady","Branden","Duncan","Jordan","Dylan","Ryan","Isaac","Wayne","Eaton","Orlando","Cadman","Abraham","Bert","Alexander","Troy","Alden","Kibo","Palmer","Oscar","Ian","Dalton","Shad","Tobias","Kirk","Quamar","Kermit","Dexter","Dale","Gavin","Abel","Emery","Armand","Garth","Porter","Kane","Jarrod","Odysseus","Norman","Amos","Geoffrey","Rogan","Justin","Stephen","Branden","Malcolm","Derek","Blake","Laith","Denton","Carson","Brenden","Cruz" };
	
    private static String[] prenomFemme = { "Xaviera","Vivien","Shoshana","Marny","Evelyn","Kaden","Nyssa","Victoria","Karleigh","Petra","Riley","Tashya","Ingrid","Courtney","Danielle","Tanya","Basia","Daria","Eleanor","Winifred","Ifeoma","Teegan","Stephanie","Summer","Shelby","Melodie","Alexa","Mercedes","Xena","Pamela","Maisie","Nichole","Brynne","Shea","Hillary","Mikayla","Lana","Karen","Jayme","Kai","Kameko","Mechelle","Evangeline","Gwendolyn","Suki","Fleur","Jamalia","Fleur","Shoshana","Amity","Debra","Guinevere","Marah","Gemma","Quincy","Fallon","Halla","Nerea","Diana","Amaya","Maite","Bryar","Raven","Maisie","Meredith","Xyla","Avye","Lysandra","Chanda","Cassandra","Stephanie","Jessamine","Cherokee","Whoopi","Molly","Maryam","Stacey","Venus","Wanda","Ria","Maryam","Jillian","Fay","Rhea","Nayda","Diana","Whilemina","Camilla","Portia","Laurel","Neve","Olympia","Emi","Echo","Madison","Yuri","Winter","Pamela","Claudia","Maya" };
	
    private static String[] nomFamille = { "DUNLAP","JUAREZ","WILKERSON","STEIN","LEON","BUCKLEY","BLAIR","REESE","WHITAKER","HARRINGTON","BOYLE","HALE","HARPER","NUNEZ","HANSEN","DANIEL","WEBB","PITTMAN","RHODES","ROSE","ROBERTSON","RUSSO","MCCLAIN","KERR","BURRIS","BARTLETT","FREDERICK","AYERS","GOODMAN","NIXON","FITZPATRICK","RIVERA","STONE","BOND","WHITLEY","HOOPER","HARMON","KELLY","HOFFMAN","TERRY","PRINCE","FULLER","DELEON","SULLIVAN","MONROE","GRANT","SANDOVAL","LAWSON","GARRISON","SANDERS","CONRAD","PRUITT","DRAKE","MCCALL","HANSEN","PITTMAN","CUMMINGS","TERRELL","REYES","OCONNOR","HUBER","CROSBY","DICKERSON","COX","SALAZAR","KELLEY","SUMMERS","PATTERSON","HOLMES","BURRIS","CUMMINGS","SLOAN","WOLF","OSBORN","MOONEY","HARMON","MCBRIDE","MCCARTY","MCKAY","MARTIN","HOUSTON","CARVER","GORDON","HERMAN","WALL","FITZPATRICK","OCONNOR","HUBBARD","GILL","RUIZ","CHAN","SHERMAN","ROBERTS","HUBBARD","WATTS","NUNEZ","MACIAS","AGUILAR","BLAIR","GROSS" };
    
    private void initialize() 
    {
	loadOperateurs();
	loadDepartementAndRegion();
	loadAppelAndClient();
    }

    private void loadOperateurs() 
    {
	operateurs.add(new Operateur("Cdiscount Mobile"));
	operateurs.add(new Operateur("Afone Mobile"));
	operateurs.add(new Operateur("Alice"));
	operateurs.add(new Operateur("Bouygues"));
	operateurs.add(new Operateur("Free"));
	operateurs.add(new Operateur("La Poste Mobile"));
	operateurs.add(new Operateur("Lycamobile "));
	operateurs.add(new Operateur("NRJ Mobile"));
	operateurs.add(new Operateur("Orange"));
	operateurs.add(new Operateur("SFR"));
	operateurs.add(new Operateur("Réglo Mobile"));
    }

    private void loadAppelAndClient() 
    {
	Random r = new Random(14);
	
	for (int i = 0; i < NB_APPEL; i++) 
	{	
	    String numTel = "0"+(6_00_00_00_00+r.nextInt(NB_CLIENT));
	    
	    Client client = findOrCreate(numTel,r);
	    
	    int duree = r.nextInt(3600);
	    int cout = r.nextInt(400);
	    String numDestinataire = "0"+(6_00_00_00_00+r.nextInt(99_99_99_99));
	    Operateur operateurDestinataire = operateurs.get(r.nextInt(operateurs.size()));
	    
	    Appel appel = new Appel(client, duree, cout, numDestinataire, operateurDestinataire);
	    appels.add(appel);
	}
    }

    private Client findOrCreate(String numTel, Random r) 
    {
	Client client = mapNumtelClient.get(numTel);
	if (client==null)
	{
	    String nom = nomFamille[r.nextInt(nomFamille.length)];
	    String prenom;
	    Genre genre;
	    
	    if (r.nextInt(1)==0)
	    {
		prenom = prenomHomme[r.nextInt(prenomHomme.length)];
		genre = Genre.HOMME;
	    }
	    else
	    {
		prenom = prenomFemme[r.nextInt(prenomFemme.length)];
		genre = Genre.FEMME;
	    }
	    
	    int age = r.nextInt(100);
	    
	    Departement departement = departements.get(r.nextInt(departements.size()));
	    
	    client = new Client(nom, prenom, numTel, age, departement, genre);
	    clients.add(client);
	    mapNumtelClient.put(numTel, client);
	}
	
	return client;
    }

    private void loadDepartementAndRegion() 
    {
	departements.add(new Departement("Bas-Rhin",67,getOrCreateRegion("Alsace")));
	departements.add(new Departement("Haut-Rhin",68,getOrCreateRegion("Alsace")));
	departements.add(new Departement("Dordogne",24,getOrCreateRegion("Aquitaine")));
	departements.add(new Departement("Gironde",33,getOrCreateRegion("Aquitaine")));
	departements.add(new Departement("Landes",40,getOrCreateRegion("Aquitaine")));
	departements.add(new Departement("Lot-et-Garonne",47,getOrCreateRegion("Aquitaine")));
	departements.add(new Departement("Pyrénées-Atlantiques",64,getOrCreateRegion("Aquitaine")));
	departements.add(new Departement("Allier",3,getOrCreateRegion("Auvergne")));
	departements.add(new Departement("Cantal",15,getOrCreateRegion("Auvergne")));
	departements.add(new Departement("Haute-Loire",43,getOrCreateRegion("Auvergne")));
	departements.add(new Departement("Puy-de-Dôme",63,getOrCreateRegion("Auvergne")));
	departements.add(new Departement("Calvados",14,getOrCreateRegion("Basse-Normandie")));
	departements.add(new Departement("Orne",61,getOrCreateRegion("Basse-Normandie")));
	departements.add(new Departement("Côte d'Or",21,getOrCreateRegion("Bourgogne")));
	departements.add(new Departement("Nièvre",58,getOrCreateRegion("Bourgogne")));
	departements.add(new Departement("Saône-et-Loire",71,getOrCreateRegion("Bourgogne")));
	departements.add(new Departement("Yonne",89,getOrCreateRegion("Bourgogne")));
	departements.add(new Departement("Côtes d'Armor",22,getOrCreateRegion("Bretagne")));
	departements.add(new Departement("Finistère",29,getOrCreateRegion("Bretagne")));
	departements.add(new Departement("Ille-et-Vilaine",35,getOrCreateRegion("Bretagne")));
	departements.add(new Departement("Morbihan",56,getOrCreateRegion("Bretagne")));
	departements.add(new Departement("Cher",18,getOrCreateRegion("Centre")));
	departements.add(new Departement("Eure-et-Loir",28,getOrCreateRegion("Centre")));
	departements.add(new Departement("Indre",36,getOrCreateRegion("Centre")));
	departements.add(new Departement("Indre-et-Loire",37,getOrCreateRegion("Centre")));
	departements.add(new Departement("Loiret",45,getOrCreateRegion("Centre")));
	departements.add(new Departement("Loir-et-Cher",41,getOrCreateRegion("Centre")));
	departements.add(new Departement("Ardennes",8,getOrCreateRegion("Champagne")));
	departements.add(new Departement("Aube",10,getOrCreateRegion("Champagne")));
	departements.add(new Departement("Haute-Marne",52,getOrCreateRegion("Champagne")));
	departements.add(new Departement("Marne",51,getOrCreateRegion("Champagne")));
	departements.add(new Departement("Corse du Sud",20,getOrCreateRegion("Corse")));
	departements.add(new Departement("Haute-Corse",99,getOrCreateRegion("Corse")));
	departements.add(new Departement("Doubs",25,getOrCreateRegion("Franche-Comté")));
	departements.add(new Departement("Haute-Saône",70,getOrCreateRegion("Franche-Comté")));
	departements.add(new Departement("Jura",39,getOrCreateRegion("Franche-Comté")));
	departements.add(new Departement("Territoire-de-Belfort",90,getOrCreateRegion("Franche-Comté")));
	departements.add(new Departement("Eure",27,getOrCreateRegion("Haute-Normandie")));
	departements.add(new Departement("Seine-Maritime",76,getOrCreateRegion("Haute-Normandie")));
	departements.add(new Departement("Essonne",91,getOrCreateRegion("Ile-de-France")));
	departements.add(new Departement("Hauts-de-Seine",92,getOrCreateRegion("Ile-de-France")));
	departements.add(new Departement("Paris",75,getOrCreateRegion("Ile-de-France")));
	departements.add(new Departement("Seine-et-Marne",77,getOrCreateRegion("Ile-de-France")));
	departements.add(new Departement("Seine-St-Denis",93,getOrCreateRegion("Ile-de-France")));
	departements.add(new Departement("Val-de-Marne",94,getOrCreateRegion("Ile-de-France")));
	departements.add(new Departement("Val-d'Oise",95,getOrCreateRegion("Ile-de-France")));
	departements.add(new Departement("Yvelines",78,getOrCreateRegion("Ile-de-France")));
	departements.add(new Departement("Aude",11,getOrCreateRegion("Languedoc")));
	departements.add(new Departement("Gard",30,getOrCreateRegion("Languedoc")));
	departements.add(new Departement("Hérault",34,getOrCreateRegion("Languedoc")));
	departements.add(new Departement("Lozère",48,getOrCreateRegion("Languedoc")));
	departements.add(new Departement("Pyrénées-Orientales",66,getOrCreateRegion("Languedoc")));
	departements.add(new Departement("Corrèze",19,getOrCreateRegion("Limousin")));
	departements.add(new Departement("Creuse",23,getOrCreateRegion("Limousin")));
	departements.add(new Departement("Haute-Vienne",87,getOrCreateRegion("Limousin")));
	departements.add(new Departement("Meurthe-et-Moselle",54,getOrCreateRegion("Lorraine")));
	departements.add(new Departement("Meuse",55,getOrCreateRegion("Lorraine")));
	departements.add(new Departement("Moselle",57,getOrCreateRegion("Lorraine")));
	departements.add(new Departement("Vosges",88,getOrCreateRegion("Lorraine")));
	departements.add(new Departement("Ariège",9,getOrCreateRegion("Midi-Pyrénées")));
	departements.add(new Departement("Aveyron",12,getOrCreateRegion("Midi-Pyrénées")));
	departements.add(new Departement("Gers",32,getOrCreateRegion("Midi-Pyrénées")));
	departements.add(new Departement("Haute-Garonne",31,getOrCreateRegion("Midi-Pyrénées")));
	departements.add(new Departement("Hautes-Pyrénées",65,getOrCreateRegion("Midi-Pyrénées")));
	departements.add(new Departement("Lot",46,getOrCreateRegion("Midi-Pyrénées")));
	departements.add(new Departement("Tarn",81,getOrCreateRegion("Midi-Pyrénées")));
	departements.add(new Departement("Tarn-et-Garonne",82,getOrCreateRegion("Midi-Pyrénées")));
	departements.add(new Departement("Nord",59,getOrCreateRegion("Nord")));
	departements.add(new Departement("Pas-de-Calais",62,getOrCreateRegion("Nord")));
	departements.add(new Departement("Manche",50,getOrCreateRegion("Normandie")));
	departements.add(new Departement("Loire-Atlantique",44,getOrCreateRegion("Pays-de-la-Loire")));
	departements.add(new Departement("Maine-et-Loire",49,getOrCreateRegion("Pays-de-la-Loire")));
	departements.add(new Departement("Mayenne",53,getOrCreateRegion("Pays-de-la-Loire")));
	departements.add(new Departement("Sarthe",72,getOrCreateRegion("Pays-de-la-Loire")));
	departements.add(new Departement("Vendée",85,getOrCreateRegion("Pays-de-la-Loire")));
	departements.add(new Departement("Aisne",2,getOrCreateRegion("Picardie")));
	departements.add(new Departement("Oise",60,getOrCreateRegion("Picardie")));
	departements.add(new Departement("Somme",80,getOrCreateRegion("Picardie")));
	departements.add(new Departement("Charente",16,getOrCreateRegion("Poitou-Charente")));
	departements.add(new Departement("Charente Maritime",17,getOrCreateRegion("Poitou-Charente")));
	departements.add(new Departement("Deux-Sèvres",79,getOrCreateRegion("Poitou-Charente")));
	departements.add(new Departement("Vienne",86,getOrCreateRegion("Poitou-Charente")));
	departements.add(new Departement("Alpes de Haute-Provence",4,getOrCreateRegion("Provence-Alpes-Côte d'Azur")));
	departements.add(new Departement("Alpes-Maritimes",6,getOrCreateRegion("Provence-Alpes-Côte d'Azur")));
	departements.add(new Departement("Bouches du Rhône",13,getOrCreateRegion("Provence-Alpes-Côte d'Azur")));
	departements.add(new Departement("Hautes-Alpes",5,getOrCreateRegion("Provence-Alpes-Côte d'Azur")));
	departements.add(new Departement("Var",83,getOrCreateRegion("Provence-Alpes-Côte d'Azur")));
	departements.add(new Departement("Vaucluse",84,getOrCreateRegion("Provence-Alpes-Côte d'Azur")));
	departements.add(new Departement("Ain",1,getOrCreateRegion("Rhône-Alpes")));
	departements.add(new Departement("Ardèche",7,getOrCreateRegion("Rhône-Alpes")));
	departements.add(new Departement("Drôme",26,getOrCreateRegion("Rhône-Alpes")));
	departements.add(new Departement("Haute-Savoie",74,getOrCreateRegion("Rhône-Alpes")));
	departements.add(new Departement("Isère",38,getOrCreateRegion("Rhône-Alpes")));
	departements.add(new Departement("Loire",42,getOrCreateRegion("Rhône-Alpes")));
	departements.add(new Departement("Rhône",69,getOrCreateRegion("Rhône-Alpes")));
	departements.add(new Departement("Savoie",73,getOrCreateRegion("Rhône-Alpes")));	
    }

    private Region getOrCreateRegion(String nom) 
    {
	List<Region> rs = regions.stream().filter(e->e.nom.equals(nom)).collect(Collectors.toList());
	if (rs.size()==0)
	{
	    Region r = new Region(nom);
	    regions.add(r);
	    return r;
	}
	else
	{
	    return rs.get(0);
	}
    }
    
    
    
    
    
    // Requeteurs 
    public List<Departement> getDepartements() {
        return new ArrayList<Departement>(departements);
    }

    

    public List<Region> getRegions() {
        return new ArrayList<Region>(regions);
    }

    

    public List<Client> getClients() {
        return new ArrayList<Client>(clients);
    }

  

    public List<Appel> getAppels() {
        return new ArrayList<Appel>(appels);
    }
    
    public List<Operateur> getOperateurs() {
        return new ArrayList<Operateur>(operateurs);
    }
    
    
    /**
     * Retourne le nombre total d'appel pour le departement avec le numero indiqué 
     */
    public int getDepartementNbAppel(int numDepartement)
    {
	int res = 0;
	for (Appel appel : appels) 
	{
	    if (appel.client.departement.numero==numDepartement)
	    {
		res++;
	    }
	}
	
	// On ajouter une petite tempo pour simuler un accés base de données ...  
	try 
	{
	    Thread.sleep(100);
	} 
	catch (InterruptedException e) {
	   // Nothing to do ... 
	}
	
	return res;
    }
    

    public static void main(String[] args) 
    {
	/*
	List<Client> clis = DataSource.getDataSource().getClients();
	for (Client client : clis) 
	{
	    System.out.println("cli "+client.nom+" "+client.prenom+" "+client.numTel+" ("+client.departement.numero+","+client.departement.nom+")");
	}
	*/
	
	 List<Departement> depts = DataSource.getDataSource().getDepartements();
	
	 long start = System.currentTimeMillis();
	 for (Departement departement : depts) 
	 {
	     System.out.println("dept = "+departement.nom+" nb Appel = "+DataSource.getDataSource().getDepartementNbAppel(departement.numero));
	}
	 
	 System.out.println("Elapsed Time = "+(System.currentTimeMillis()-start)/1000+" secondes");
	
    }
    
}
