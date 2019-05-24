import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FiltreBloom {

	static int m = 200_000_000;
	int k;
	
	static boolean table[] = new boolean[m];
	
	public FiltreBloom (int k)
	{
		this.k = k;
	}
	
	public void insert (String nouveau)
	{
		for (int i = 0; i < k ; i++)
			table[Hash.hachage(nouveau, i)] = true;
	}
	
	public boolean research (String element)
	{
		for (int i = 0; i < k ; i++)
			if (table[Hash.hachage(element, i)] == false) 		// comparer des booléens dans une condition c'est moche
				return false;
		return true;
	}
	
	public void fill (String chemin) throws IOException
	{
		SeekableByteChannel file = Files.newByteChannel(Paths.get(chemin), StandardOpenOption.READ);
		ByteBuffer buf = ByteBuffer.allocate(50_000);
		int ret = file.read(buf);
		String str;
		
		while(ret>0)
		{			
			for (int i = 0; i < 1000; i++)
			{
				str = new String(buf.array(),i*50,50);
				str = str.trim();
				this.insert(str);
			}
			buf.clear();
			ret = file.read(buf);
		}
		file.close();	
	}
	
}
