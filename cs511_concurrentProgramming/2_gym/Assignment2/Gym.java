
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
    Semaphore plateMutex = new Semaphore(1);

    /*  LEGPRESSMACHINE[0]  BARBELL[1]              HACKSQUATMACHINE[2] LEGEXTENSIONMACHINE[3]   *
     *  LEGCURLMACHINE[4]   LATPULLDOWNMACHINE[5]   PECDECKMACHINE[6]   CABLECROSSOVERMACHINE[7] */
    Semaphore[] apparatusKey = { new Semaphore(5), new Semaphore(5), new Semaphore(5), 
            new Semaphore(5), new Semaphore(5), new Semaphore(5), new Semaphore(5), 
            new Semaphore(5)};

    public Client makeClient() throws InterruptedException {
        Random rand = new Random();
        Integer clientID = new Integer(111111);
        clientMutex.acquire();
        while(clients.contains(clientID)){
            clientID = new Integer (rand.nextInt(100000));
        }
        clients.add(clientID);
        clientMutex.release();

        return Client.generateRandom(clientID);
    }

    public void performExercise(int id, ApparatusType at, Map<WeightPlateSize, Integer> weight, 
            int duration) throws InterruptedException {
        
        int apparatusNum = 0;
        if(at == ApparatusType.LEGPRESSMACHINE){
            apparatusNum = 0;
        }else if (at == ApparatusType.BARBELL){
            apparatusNum = 1;
        }else if (at == ApparatusType.HACKSQUATMACHINE){
            apparatusNum = 2;
        }else if (at == ApparatusType.LEGEXTENSIONMACHINE){
            apparatusNum = 3;
        }else if (at == ApparatusType.LEGCURLMACHINE){
            apparatusNum = 4;
        }else if (at == ApparatusType.LATPULLDOWNMACHINE){
            apparatusNum = 5;
        }else if (at == ApparatusType.PECDECKMACHINE){
            apparatusNum = 6;
        }else if (at == ApparatusType.CABLECROSSOVERMACHINE){
            apparatusNum = 7;
        }

        boolean noPlates = true;
        while(noPlates){
            plateMutex.acquire();
            int remSmall = noOfWeightPlates.get(WeightPlateSize.SMALL_3KG).intValue() - 
                    weight.get(WeightPlateSize.SMALL_3KG).intValue();
            int remMedium = noOfWeightPlates.get(WeightPlateSize.MEDIUM_5KG).intValue() - 
                    weight.get(WeightPlateSize.MEDIUM_5KG).intValue(); 
            int remLarge = noOfWeightPlates.get(WeightPlateSize.LARGE_10KG).intValue() - 
                    weight.get(WeightPlateSize.LARGE_10KG).intValue();
            if((remSmall > 0) && (remMedium > 0) && remLarge > 0){
                noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, remSmall);
                noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, remMedium);
                noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, remLarge);
                noPlates = false;
            }
            plateMutex.release();
        }
        
        apparatusKey[apparatusNum].acquire();
        System.out.println(id + " started using " + at + " with " + 
                weight.get(WeightPlateSize.SMALL_3KG) + " Small 3kg weights, " + 
                weight.get(WeightPlateSize.MEDIUM_5KG) + " Medium 5kg weight, and " + 
                weight.get(WeightPlateSize.LARGE_10KG) + " Large 10kg weights.");

        Thread.sleep(duration);
        
        System.out.println(id + " finished using " + at + " with " + 
                weight.get(WeightPlateSize.SMALL_3KG) + " Small 3kg weights, " + 
                weight.get(WeightPlateSize.MEDIUM_5KG) + " Medium 5kg weights, and " + 
                weight.get(WeightPlateSize.LARGE_10KG) + " Large 10kg weights.");

        plateMutex.acquire();
        noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, 
                noOfWeightPlates.get(WeightPlateSize.SMALL_3KG) + 
                weight.get(WeightPlateSize.SMALL_3KG));
        noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, 
                noOfWeightPlates.get(WeightPlateSize.MEDIUM_5KG) + 
                weight.get(WeightPlateSize.MEDIUM_5KG));
        noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, 
                noOfWeightPlates.get(WeightPlateSize.LARGE_10KG) + 
                weight.get(WeightPlateSize.LARGE_10KG));
        
        plateMutex.release();
        apparatusKey[apparatusNum].release();
    }

    public void goToTheGym(Client user) throws InterruptedException {
    
        System.out.println(user.getId() + " entered the gym.");
        List<Exercise> routine = user.getRoutine();
        ListIterator itr = routine.listIterator();
        while(itr.hasNext()){
            Exercise ex = (Exercise)itr.next();
            performExercise(user.getId(), ex.getApparatus(), ex.getWeight(), ex.getDuration());
        }
        System.out.println(user.getId() + " left the gym.");
        return;
    }

    public void run() {
        noOfWeightPlates = new HashMap<>();
        noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, new Integer(110));
        noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, new Integer(90));
        noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, new Integer(75));

        executor = Executors.newFixedThreadPool(GYM_SIZE);
        clients = new HashSet<Integer>();
        for(int x = 0; x < GYM_REGISTERED_CLIENTS; x++){
            executor.execute(new Runnable() {
                public void run(){
                    try {
                        goToTheGym(makeClient());
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    return;
                }
            });
        }

        executor.shutdown();
    }
}
