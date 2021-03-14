// Exo2 & 3

package tdm2;

import tdm1.*;

//public class ClientDepartement implements GetField<Client, Departement>
public class ClientDepartement implements GetField<Client, Integer>
{
	@Override
	public Integer getField(Client t) 
	{
		return t.departement.numero;
	}    
}