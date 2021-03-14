// Exo1

package tdm2;

import tdm1.*;

public class ClientNom implements GetField<Client, String> {

	@Override
	public String getField(Client t) 
	{
		return t.nom;
	}
}
