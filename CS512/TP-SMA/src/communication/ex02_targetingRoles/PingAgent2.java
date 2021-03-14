package communication.ex02_targetingRoles;

import static communication.ex01.Society.COMMUNITY;
import static communication.ex01.Society.GROUP;
import static communication.ex01.Society.ROLE;

import java.util.logging.Level;

import communication.ex01.PingAgent;
import madkit.kernel.Madkit;
import madkit.kernel.Message;

/**
 * Shows how agents exchange messages by targeting roles.
 * 
 * 
 * 
 * 
 * 
 * 
 * Looking for someone, agents do not necessarily need to know who they talk to in terms of real ID. Indeed, what
 * matters in the artificial society is the roles an agent take. organization tell a lot about what the agent is capable of and
 * supposed to do. So, agents can send messages to roles rather than to IDs. Here, the idea is: I need to contact a
 * "ping agent", no matter who will receive the message. And it is possible to do so using what follows:
 */
public class PingAgent2 extends PingAgent {// So I do the same activate

    /**
     * Now ping another agent, just by targeting the role
     */
    @Override
    protected void live() {

	getLogger().setLevel(Level.ALL);

	ReturnCode code = null;

	// until I find someone having role
	while (code != ReturnCode.SUCCESS) {
	    // This will randomly choose a receiver having this role
	    code = sendMessage(COMMUNITY, GROUP, ROLE, new Message());
	    pause((int) (Math.random() * 1000 + 100));
	}

	nextMessage();
	pause(10000);
    }

    @SuppressWarnings("unused")
    public static void main(String[] args) {
    	//This will launch a new kernel. It will automatically ends when all the agents living on this kernel are done.
	new Madkit("--launchAgents", PingAgent2.class.getName() + ",true,3;", PingAgent.class.getName()// This one so that PingAgent2 agents always find someone (breaking the
												       // first while)
	);
    }

}
