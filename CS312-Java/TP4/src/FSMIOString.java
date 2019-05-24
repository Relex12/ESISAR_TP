import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

// A FSMIO with Strings in the Tag reading the automaton description from a file
public class FSMIOString{

	FSMIO<String, String> fsms;

	// Constructor : Reading a FSMIO description from a file
	// The file contains one transition per line
	// Every line has the following syntax :
	// statenameorig input output statenamedest
	// The first transition is supposed to start from the initial state 
	public  FSMIOString (String filename) {
		BufferedReader fileR;
		try {
			fileR = new BufferedReader(new FileReader(filename));
			String line = fileR.readLine();
			String [] t;
			State orig, dest;
			t = readTransition(line);
			orig = new State(t[0]);
			this.fsms = new FSMIO<String, String>(orig);
			while(line != null && !line.equals("")){
				orig = new State(t[0]);
				dest = new State(t[3]);
				this.fsms.addState(orig);
				this.fsms.addState(dest);
				this.fsms.addTransition(orig, t[1], t[2], dest);
				line = fileR.readLine();
				t = readTransition(line);
			}
		} catch (FileNotFoundException e) {
			e.printStackTrace();
			System.exit(1);
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

	// returns an array of the four words describing a transition
	private String[] readTransition(String line) {
		String word[] = new String[4];
		int cword = 0;
		int pos = 0;
		while (pos < line.length() && cword <=3){
			word[cword] = new String();
			while (pos < line.length() 
					&& (line.charAt(pos) == ' '
					|| line.charAt(pos) == '\t')){ pos++;}
			while (pos < line.length() 
					&& line.charAt(pos) != ' ' 
					&& line.charAt(pos) != '\t'){ 
				word[cword] += line.charAt(pos++);
			}
			cword++;
		}
		return word;
	}


	public FSMIO<String, String> getFSM(){
		return this.fsms;
	}

	public String toString(){
		return this.fsms.toString();
	}

}
