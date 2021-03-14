package TP1;

import madkit.kernel.Agent;

public class AgentControleur extends Agent {

	@Override
    protected void activate() {
    	createGroupIfAbsent("communication", "GroupTest");// Create the group GroupTest in the community communication
    	requestRole("communication", "GroupTest", "Compteur");// Request the role RoleTest1
    	pause(500);

    }

    @Override
    protected void live() {
    	
    }
}
