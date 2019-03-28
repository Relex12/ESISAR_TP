import java.util.*;

public class Planning
{
	public static void main (String [] args)
	{
		Planning p = new Planning();

		SalleCTD a042 = new SalleCTD(100, "A042");
		SalleCTD d030 = new SalleCTD(180, "D030");

		SalleTP b141 = new SalleTP(16, "B141", Discipline.Informatique);
		SalleCTD a048 = new SalleCTD(25, "A048");

		CM cs310cm = new CM("CM CS310");
		cs310cm.addSalle(a042);
		cs310cm.addSalle(d030);

		TP cs330tp1 = new TP("TP1 CS330");
		cs330tp1.addSalle(b141);

		CM cs410cm = new CM("CM CS410");
		cs410cm.addSalle(a042);
		cs410cm.addSalle(d030);
		cs410cm.addSalle(a048);

		CM cs421_422cm = new CM("CM CS421 - CS422");
		cs421_422cm.addSalle(a042);
		cs421_422cm.addSalle(d030);
		cs410cm.addSalle(a048);

		Groupe a3tp1 = new Groupe("3ATP1", 16);
		Groupe a3tp2 = new Groupe("3ATP2", 16);
		Groupe a3tp3 = new Groupe("3ATP3", 16);
		Groupe a3tp4 = new Groupe("3ATP4", 16);
		Groupe a3tp5 = new Groupe("3ATP5", 16);

		Groupe a4ir = new Groupe("4AIR", 29);
		Groupe a4eis = new Groupe("4AEIS", 35);

		cs310cm.addGroupe(a3tp1);
		cs310cm.addGroupe(a3tp2);
		cs310cm.addGroupe(a3tp3);
		cs310cm.addGroupe(a3tp4);
		cs310cm.addGroupe(a3tp5);

		cs330tp1.addGroupe(a3tp1);
		cs410cm.addGroupe(a4ir);
		cs421_422cm.addGroupe(a4ir);
		cs421_422cm.addGroupe(a4eis);

		Creneau c1 = null, c2 = null, c3 = null, c4 = null, c5 = null;
		c1 = new Creneau(2014, 1, 17, 13, 15, 105, a042, cs310cm);
		c2 = new Creneau(2014, 1, 17, 8, 00, 210, b141, cs330tp1);
		c3 = new Creneau(2014, 1, 17, 15, 15, 105, d030, cs410cm);
		c4 = new Creneau(2014, 1, 17, 10, 00, 105, a042, cs421_422cm);
		c5 = new Creneau(2014, 1, 17, 17, 15, 105, a042, cs310cm);

		System.out.println("ici vivait le E où la prof ne voulait pas reconnaitre son incompétence");
		System.exit(1);

		p.addCreneau(c1);
		p.addCreneau(c2);
		p.addCreneau(c3);
		p.addCreneau(c4);
		p.addCreneau(c5);

		System.out.println(p);

		System.out.println(p.planningGroupe(a3tp1) + " (" + p.totalHeuresGroupe(a3tp1) + " heures)");
		System.out.println(p.planningGroupe(a4ir));
		System.out.println(p.planningGroupe(a3tp1));

	}

	private List<Creneau> edt;

	public Planning()
	{
		edt = new ArrayList<Creneau>();
	}

	public String toString()
	{
		String res = new String();
		for (Creneau c : edt){
			res = res + c + "\n";
		}
		return res;
	}

	public boolean verifCreneau(Creneau c)
	{
		boolean ok = true;
		int i = 0;
		while (ok && i < edt.size()){
			Creneau cour = edt.get(i++);
			ok = !c.intersection(cour);
		}
		return ok;
	}

	public void addCreneau(Creneau c)
	{
		if (this.verifCreneau(c)) edt.add(c);
		else System.out.println("Creneau " + c + " non insere");
	}

/*	public List<Creneau> planningGroupe(Groupe groupe)
	{
        List<Creneau> planning = new List<Creneau>();
        for (Creneau c : this)
		{
            for ( Groupe g : c.getActivite().getGroupes() )
			{
                if ( g == groupe ) planning.add(c);
	        }
		}
	    return planning;
	}
*/
public List<Creneau> planningGroupe(Groupe groupe)
{
	ArrayList<Creneau> liste = new ArrayList<Creneau>();
	for (Creneau c : edt)	for (Groupe g : c.getActivite().getGroupes()) 	if (g == groupe) 	liste.add(c);
	return liste;
}

	public float totalHeuresGroupe(Groupe groupe)
	{
		int total_heures = 0;
		for (Creneau c : this.edt)
			for ( Groupe g : c.getActivite().getGroupes() )
				if ( g == groupe )
					total_heures += c.getDuree();
		return total_heures;
		}
}
