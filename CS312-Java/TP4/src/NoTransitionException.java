@SuppressWarnings("serial")
public class NoTransitionException extends Exception{
  public NoTransitionException(){
    System.out.println("Pas de transition depuis cet état avec cette entrée");
  }
}
