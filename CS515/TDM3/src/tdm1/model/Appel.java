package tdm1.model;

public class Appel {

    // Client qui a appelé 
    public Client client;
    
    // Duree de l'appel en secondes
    public int duree;
    
    // Cout de l'appel en centimes
    public int cout;
    
    // Numero de tel du destinataire 
    public String numDestinataire;
    
    // Operateur du destinataire
    public Operateur operateurDestinataire;

    public Appel(Client client, int duree, int cout, String numDestinataire,
	    Operateur operateurDestinataire) {
	super();
	this.client = client;
	this.duree = duree;
	this.cout = cout;
	this.numDestinataire = numDestinataire;
	this.operateurDestinataire = operateurDestinataire;
    }
    
    
    
}
