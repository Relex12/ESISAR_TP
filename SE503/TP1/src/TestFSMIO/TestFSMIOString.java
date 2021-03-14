package TestFSMIO;
import java.util.*;
import FSMIO.*;

public class TestFSMIOString {
	
	// Change the workDir value!!!
	static final String workDir = "C:/Users/Adrian/eclipse-workspace/se503-tp1/src";
	static final String specFile1 =  workDir + "/test.fsm";
	static final String iutFile1 = workDir + "/test1.fsm";
	static final String coffeeMachineSpec = workDir + "/coffeemachine.fsm";
	static final String coffeeMachineIUT = workDir + "/coffeemachineIUT.fsm";

	
	public static void main(String argv[]){
		// Building the FSMIOs of the specification and of the IUT from the fsm files
		FSMIOString fsms = new FSMIOString(specFile1);
		System.out.println("Specification: \n" +  fsms);
		
		FSMIOString iut = new FSMIOString(iutFile1);
		System.out.println("Implementation: \n" + iut);
		
		FSMIO<String, String> iut1 = iut.getFSM();
		FSMIO<String, String> fsm1 = fsms.getFSM();
		
		// Executing a sequence on fsm1
		fsm1.reset();
		fsm1.doTransition("a");
		fsm1.doTransition("b");
		fsm1.doTransition("a");
		fsm1.doTransition("a");
		System.out.println("Execution of sequence reset-abaa leads to state : " + fsm1.getCurrentState());

		// A distinguishing sequence for fsm1
		ArrayList<String> ds = new ArrayList<String>();
		ds.add("b");
		// TO COMPLETE
		System.out.println("is " + ds + " distinguishing? : " + (fsm1.isDistinguishing(ds)?"yes":"no"));
		
		// Creating a synchronizing sequence for fsm1
		ArrayList<String> ss = new ArrayList<String>();
		ss.add("a"); // TO COMPLETE
		System.out.println("is " + ss + " synchronizing? : " + (fsm1.isSynchronizing(ss)?"yes":"no"));
		
		ArrayList<String> ts = new ArrayList<String>();
		ts.add("a"); // TO COMPLETE
		// Testing  the conformity of iut1 to fsm1
		System.out.println(fsm1.testFSMOneSequence(iut1, ts, ds));
		// To complete
		
		
		// Application to the coffee machine specification and implementation
		/*
		FSMIOString coffeemachine = new FSMIOString(coffeeMachineSpec);
		System.out.println(coffeemachine);
		FSMIO<String, String> cfm1 = coffeemachine.getFSM();

		FSMIOString coffeemachineIUT = new FSMIOString(coffeeMachineIUT);
		System.out.println(coffeemachineIUT);
		FSMIO<String, String> cfmiut1 = coffeemachineIUT.getFSM();

		TO COMPLETE		
		*/
		// Testing the conformity of cfmiut1 to cfm1
		// To complete
	}

}
