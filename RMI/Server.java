package RMI;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Server {
    public static void main(String[] args) {
        try {
            CalcRemote obj = new CalcRemote();
            Registry reg = LocateRegistry.createRegistry(9000);
            reg.rebind("multiply", obj);
            System.out.println("Server ready");
        } catch (Exception e) {
            System.out.println("Server failed: " + e);
            e.printStackTrace();
        }
    }
}
