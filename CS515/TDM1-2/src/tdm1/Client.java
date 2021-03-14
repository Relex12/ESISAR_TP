package tdm1;

public class Client {

    public String nom;
    
    public String prenom;
    
    public String numTel;
    
    // Age en année
    public int age;
    
    // Département de résidence 
    public Departement departement;
    
    //
    public Genre genre;

    public Client(String nom, String prenom, String numTel, int age,Departement departement, Genre genre) 
    {
	super();
	this.nom = nom;
	this.prenom = prenom;
	this.numTel = numTel;
	this.age = age;
	this.departement = departement;
	this.genre = genre;
    }
    
    
    
    
}
