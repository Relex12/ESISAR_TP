package communication.ex04;

import java.util.logging.Level;

import madkit.gui.AgentFrame;
import madkit.kernel.Agent;
import madkit.kernel.AgentAddress;
import madkit.kernel.Madkit;
import madkit.kernel.Message;

/**
 * Agent2 works as Agent1, using a different role.
 * 
 * #jws communication.ex05.Agent1 jws#
 * 
 * Agent2 is almost like Agent1, the only difference is the role and frame's location.
 */

public class Agent2 extends Agent {

    @Override
    protected void activate() {
	getLogger().setLevel(Level.FINEST);

	createGroup("communication", "GroupTest");
	requestRole("communication", "GroupTest", "RoleTest2");
	pause(500);
    }

    @Override
    protected void live() {
	AgentAddress other = null;
	while (other == null) {
	    other = getAgentWithRole("communication", "GroupTest", "RoleTest1");
	    pause(1000);
	}
	getLogger().info("\n\tI found someone !!\n" + other + "\n\n");
	pause(1000);

	sendMessage(other, new Message());
	pause(1000);

	while (nextMessage() != null)
	    pause(6000);
    }

    /**
     * Will launch 2 instances of both Agent1 and Agent2. They will send themselves 1 message.
     */
    @SuppressWarnings("unused")
    public static void main(String[] argss) {
	new Madkit("--launchAgents", Agent1.class.getName() + ",true,2;", Agent2.class.getName() + ",true,2;");
    }

    /*
     * Setting where the agent's window will be.
     */
    @Override
    public void setupFrame(AgentFrame frame) {
	super.setupFrame(frame);
	frame.setLocation(550, 350 * (hashCode() - 4));
    }
}
