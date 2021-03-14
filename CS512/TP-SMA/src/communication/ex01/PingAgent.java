package communication.ex01;

import static communication.ex01.Society.COMMUNITY;
import static communication.ex01.Society.GROUP;
import static communication.ex01.Society.ROLE;

import java.util.logging.Level;

import madkit.kernel.Agent;
import madkit.kernel.AgentAddress;
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
 * used to send them messages. Here, two agents take a role and ping the other one.
 */
public class PingAgent extends Agent {

    /**
     * Firstly, take a position in the artificial society
     */
    @Override
    protected void activate() {

        getLogger().setLevel(Level.FINEST);

        createGroup(COMMUNITY, GROUP);
        requestRole(COMMUNITY, GROUP, ROLE);

        pause(500);
    }

    /**
     * Now ping the other agent with a message
     */
    @Override
    protected void live() {

        // method seen in organization's tutorial
        AgentAddress other = null;
        while (other == null) {
            other = getAgentWithRole(COMMUNITY, GROUP, ROLE);
            pause(1000);
        }

        getLogger().info("\n\tI found someone !!\n" + other + "\n\n");
        pause(2000);

        // sending the message to other: Success will be logged
        sendMessage(other, new Message());
        pause(2000);

        // waiting other's message: The reception will be logged
        waitNextMessage();
        pause(20000);
    }

    /**
     * @param args
     */
    public static void main(String[] argss) {
        executeThisAgent(2, true);
        // or
        // String[] args = { "--launchAgents", PingAgent.class.getName() + ",true,2" };
        // Madkit.main(args);
    }

}
