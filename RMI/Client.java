package RMI;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

public class Client {
    public static void main(String[] args) {
        try {
            Registry reg = LocateRegistry.getRegistry(9000);
            Calc obj = (Calc) reg.lookup("multiply");
            int value = obj.multiply(10, 30);
            System.out.println("Result: " + value);
        } catch (Exception e) {
            System.out.println("Failed to connect to server: " + e);
            e.printStackTrace();
        }
    }
}
