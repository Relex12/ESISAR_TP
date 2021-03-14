package communication.ex04;

import java.util.logging.Level;

import madkit.gui.AgentFrame;
import madkit.kernel.Agent;
import madkit.kernel.AgentAddress;
import madkit.kernel.Madkit;
import madkit.kernel.Message;

/**
 * Shows how agents exchange messages.
 * 
 * 
 * 
 * 
 * 
 * 
 * To exchange messages, agents have to exist in an artificial society. That is, agents have to create communities
 * containing groups and take roles within to interact with others. Doing so, agents get agent addresses which could be
 * used to send them messages. Here, one agent (Agent1) is communicating with another agent (Agent2) by getting its
 * agent address in the artificial society and using it with sendMessage.
 */
public class Agent1 extends Agent {

    /*
     * Firstly, take a position in the artificial society.
     */
    @Override
    protected void activate() {
	getLogger().setLevel(Level.FINEST);

	createGroup("communication", "GroupTest");// Create the group GroupTest in the community communication.
	requestRole("communication", "GroupTest", "RoleTest1");// Request the role RoleTest1.
	pause(500);
    }

    /*
     * First getting an Agent address, and then sending him a message.
     */
    @Override
    protected void live() {
	AgentAddress other = null;
	// Until we have an agent (in the group GroupTest in the community communication) having the role RoleTest2.
	while (other == null) {
	    // Getting the address of an agent being in the community "communication" and the group "GroupTest", and having the role
	    // "RoleTest2".
	    other = getAgentWithRole("communication", "GroupTest", "RoleTest2");

	    // Trying to get another agent (Agent3).
	    if (other == null) {
		other = getAgentWithRole("communication", "GroupTest", "RoleTest3");
	    }
	    pause(1000);
	}
	getLogger().info("\n\tI found someone !!\n" + other + "\n\n");
	pause(1000);

	sendMessage(other, new Message());// Sending the message to the agent we found.
	pause(1000);

	while (nextMessage() != null)
	    pause(6000);
    }

    /*
     * Set where the agent's window will be for avoiding a clear presentation. This method give
	 * the opportunity to modify the default settings of the frame.
     * It will be more explained in GUI tutorial.
     */
    @Override
    public void setupFrame(AgentFrame frame) {
	super.setupFrame(frame);
	frame.setLocation(100, 320 * (hashCode() - 2));
    }

    /**
     * @param argss
     *            Running Agent1 will launch 2 instances of both Agent1 and Agent2. They will send themselves 1 message.
     */
    @SuppressWarnings("unused")
    public static void main(String[] argss) {
	new Madkit("--launchAgents", Agent1.class.getName() + ",true,2;", Agent2.class.getName() + ",true,2;");
    }
}