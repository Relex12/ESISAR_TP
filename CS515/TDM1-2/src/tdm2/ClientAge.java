// Exo1

package tdm2;

import tdm1.*;

public class ClientAge implements GetField<Client, Integer> {

	@Override
	public Integer getField(Client t) 
	{
		return t.age;
	}
}
