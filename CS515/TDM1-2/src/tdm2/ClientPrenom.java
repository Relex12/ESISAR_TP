// Exo1

package tdm2;

import tdm1.*;

public class ClientPrenom implements GetField<Client, String> {

	@Override
	public String getField(Client t) 
	{
		return t.prenom;
	}
}
