package TP1;

import madkit.kernel.Agent;
import madkit.kernel.AgentAddress;
import madkit.kernel.Message;

public class AgentEmetteur extends Agent {

    @Override
    protected void activate() {
    	createGroupIfAbsent("communication", "GroupTest");// Create the group GroupTest in the community communication
    	requestRole("communication", "GroupTest", "Compteur");// Request the role RoleTest1
    	pause(500);    	
    }

    @Override
    protected void live() {
    	AgentAddress other = null;
    	while (other == null) {
    	    other = getAgentWithRole("communication", "GroupTest", "RoleTest2");
    	    if (other == null)
    	    	other = getAgentWithRole("communication", "GroupTest", "RoleTest3");
    	    pause(1000);
    	}
    	getLogger().info("\n\tI found someone !!\n" + other + "\n\n");
    	pause(1000);
    	
    	sendMessage(other, new Message());// Sending the message to the agent we found.
    	pause(1000);

    	while (nextMessage() != null)
    	    pause(6000);

    }
}
