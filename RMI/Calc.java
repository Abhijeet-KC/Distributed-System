package RMI;
import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Calc extends Remote {
    int multiply(int a, int b) throws RemoteException;
}
