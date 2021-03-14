// Exo2 et 3

package tdm1;

import java.util.Comparator;
import java.util.List;

public class ClientSortStandard{
    public static void main(String[] args)  {
        List<Client> clients = DataSource.getDataSource().getClients();

        Comparator<? super Client> Sort = new SortClient1();
//      Comparator<? super Client> Sort = new SortClient2();		// switch to use the other one
        clients.sort(Sort);
        for (Client client : clients) {
            System.out.println(client.nom + " " + client.prenom);
        }
    }
}