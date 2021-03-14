package communication.ex03_replyingToMessages;

import static communication.ex01.Society.COMMUNITY;
import static communication.ex01.Society.GROUP;
import static communication.ex01.Society.ROLE;

import communication.ex01.PingAgent;
import madkit.kernel.Madkit;
import madkit.kernel.Message;
import madkit.message.StringMessage;

/**
 * Shows how agents exchange messages by targeting roles.
 * 
 * 
 * 
 * 
 * 
 * 
 * Receiving a message, you can learn information about the sender. This is illustrated firstly in this example.
 * Sometimes, agents need to communicate by replying to messages. There are primitives for that and they have two
 * advantages. (1) This will identify the message as being a concrete reply to the received message thus easing the
 * programming of protocols for instance. (2) This greatly improves code legibility
 */
public class ReplierAgent extends PingAgent {// So I do the same activate

    @Override
    protected void live() {

	// until I found someone having that role
	while (sendMessage(COMMUNITY, GROUP, ROLE, new Message()) != ReturnCode.SUCCESS) {
	    pause((int) (Math.random() * 1000 + 100));
	}

	Message m = nextMessage();
	if (m != null) {
	    getLogger().info("I have to thank " + m.getSender());
	    sendReply(m, new StringMessage("thanks"));
	}
	pause(100000);
    }

    @SuppressWarnings("unused")
    public static void main(String[] args) {
	new Madkit("--launchAgents", ReplierAgent.class.getName() + ",true,10;", PingAgent.class.getName()// This one so that agents always find someone (breaking the first while)
	);
    }

}
