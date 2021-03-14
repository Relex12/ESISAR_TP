package TestFSMIO;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import FSMIO.*;

/**
 * A FSMIO with Strings in the Tag reading the automaton description from a file
 * @author ioannis.parissis@grenoble-inp.fr
 *
 */
public class FSMIOString{
	
	FSMIO<String, String> fsms;

	/** 
	* Constructor : Builds a FSMIO from a file. <p>
	* The file contains one transition per line. 
	* Every line has the following syntax: <p>
	* statenameorig input output statenamedest <p>
	* The first transition is supposed to start from the initial state.
	* @param filename the absolute path of the filename containing the FSMIO description
	*/ 
	public  FSMIOString (String filename) {
		BufferedReader fileR;
		try {
			fileR = new BufferedReader(new FileReader(filename));
			String line = fileR.readLine();
			String [] t;
			State orig, dest;
			if(line != null && !line.equals("")){
				t = readTransition(line);
				orig = new State(t[0]);
				dest = new State(t[3]);
				this.fsms = new FSMIO<String, String>(orig);			
				while(line != null && !line.equals("")){				
					this.fsms.addState(orig);
					this.fsms.addState(dest);
					this.fsms.addTransition(orig, t[1], t[2], dest); 
					line = fileR.readLine();
					if(line != null && !line.equals("")){
						t = readTransition(line);
						orig = new State(t[0]);
						dest = new State(t[3]);
					}
				}
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
				   || line.charAt(pos) == '\t')){
				pos++ ;
			}
			while (pos < line.length() 
				   && line.charAt(pos) != ' ' 
				   && line.charAt(pos) != '\t'){ 
				word[cword] += line.charAt(pos++);
			}
			cword++;
		}
		return word;
	}

	/** 
	* Returns the built FSMIO
	*/ 
	public FSMIO<String, String> getFSM(){
		return this.fsms;
	}
	
	/** 
	* Returns the String description corresponding to the FSMIO
	*/
	public String toString(){
		return this.fsms.toString();
	}
			
}
