package communication.ex04;

import java.util.logging.Level;

import madkit.gui.AgentFrame;
import madkit.kernel.Agent;
import madkit.kernel.Madkit;
import madkit.kernel.Message;

/**
 * Shows how agents exchange messages.
 * 
 * 
 *  
 * 
 * This Agent3 is communicating using another method than Agent 1 and 2.
 */
public class Agent3 extends Agent {

    /*
     * This Activate period is almost the same as Agent 1 and 2, the difference is that this Agent 3 create is own Role.
     */
    @Override
    protected void activate() {
	getLogger().setLevel(Level.FINEST);

	createGroup("communication", "GroupTest");
	requestRole("communication", "GroupTest", "RoleTest3");
	pause(500);
    }

    /**
     * Agent3 is sending his message in a loop, until this message is successfully sent to another Agent having the Role
     * "RoleTest1".
     */
    @Override
    protected void live() {
	ReturnCode code = null;

	// Until we succeed in sending a message to an agent (in the group GroupTest in the community communication with the
	// role RoleTest1).
	while (code != ReturnCode.SUCCESS) {
	    // If several agents match, the target is chosen randomly.
	    code = sendMessage("communication", "GroupTest", "RoleTest1", new Message());
	    pause((int) (Math.random() * 1000 + 100));
	}

	while (nextMessage() != null)
	    pause(6000);
	pause(6000);
    }

    /**
     * @param argss
     *            Running Agent1 will launch 2 Agent1 and 2 Agent2. They will send themselves 1 message.
     */
    public static void main(String[] argss) {
	new Madkit("--launchAgents", Agent1.class.getName() + ",true,1;", // During his the live() period, Agent 1 will first try to found an Agent with the role "RoleTest2", than
									  // he will find Agend3 ("RoleTest3").
		Agent3.class.getName() + ",true,1;");
    }

    /**
     * Setting where the agent's window will be.
     */
    @Override
    public void setupFrame(AgentFrame frame) {
	super.setupFrame(frame);
	frame.setLocation(550, 100);
    }

}
