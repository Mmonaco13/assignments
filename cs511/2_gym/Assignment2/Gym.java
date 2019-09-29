
package Assignment2;
import java.util.*;
import java.util.concurrent.*;
public class Gym implements Runnable {
    
    private static final int GYM_SIZE = 30;
    private static final int GYM_REGISTERED_CLIENTS = 10000;
    
    private Map<WeightPlateSize, Integer> noOfWeightPlates;

    private Set<Integer> clients; //For generating fresh client ids
    private ExecutorService executor;
    
    //Various Semaphores
    Semaphore clientMutex = new Semaphore(1);
    Semaphore[] apparatusKey = {new Semaphore(5), new Semaphore(5), new Semaphore(5), 
            new Semaphore(5), new Semaphore(5), new Semaphore(5), new Semaphore(5), 
            new Semaphore(5)};

    public Client makeClient() {
        Random rand = new Random();
        int clientID = 111111;
        clientMutex.acquire();
        while(clients.contains(clientID)){
            clientID = rand.nextInt(100000);
        }
        clients.add(clientID);
        clientMutex.release();

        return Client.generateRandom(clientID);
    }

    public void goToTheGym(Client user) {
        System.out.println(user.getId() + " Im working out!!");
        return;
    }

    public void run() {
        noOfWeightPlates = new HashMap<>();
        noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, new Integer(110));
        noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, new Integer(90));
        noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, new Integer(75));

        executor = Executors.newFixedThreadPool(GYM_SIZE);
        for(int x = 0; x < GYM_REGISTERED_CLIENTS; x++){
            executor.execute(new Runnable() {
                public void run(){
                    goToTheGym(makeClient());
                    return;
                }
            });
        }

        executor.shutdown();
    }
}
