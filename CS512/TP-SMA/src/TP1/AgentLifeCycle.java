package TP1;

import madkit.kernel.Agent;

/**
 
 The default life cycle of a threaded agent is composed of three methods 
 which are automatically called sequentially, and each of which being optional:

 1. activate(): The first behavior in the life cycle of an agent.
 It could be considered as a constructor which is called once the agent is launched.
 The agent cannot use agent primitives before that (e.g. in its constructor).
 Activate is a good place to initialize the agent's position in the artificial society.
 (Artificial society is a notion that will be explained later in the tutorials)
 
 2. live(): This behavior is automatically called when the agent exits activate. It usually
 implements an infinite loop wherein the agent send and receive messages: 
 It corresponds to the life of the agent. Here the agent lives 10 seconds and quits.
 
 3. end() this behavior is automatically called when live exits or when the agent is killed, 
 e.g. by the user when closing the agent's GUI. 
 It is usually used to release resources and log the end of life event. 
 
       
 *     
*/

public class AgentLifeCycle extends Agent {

    @Override
    protected void activate() {
       getLogger().info("\tHello World!!\n\n\tI am activating...");
       pause(2000);
    }

    @Override
    protected void live() {
       int nb = 10;
       while (nb-- > 0) {
           getLogger().info("Living... I will quit in " + nb + " seconds");
           pause(1000);
       }
    }

    @Override
    protected void end() {
       getLogger().info("Bye bye !");
       pause(2000);
    }

    public static void main(String[] args) {
       executeThisAgent();
    }
}