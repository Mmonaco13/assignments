package Assignment2;
import java.util.*;

public class Exercise {

    private ApparatusType at;
    private Map<WeightPlateSize, Integer> weight;
    private int duration;

    public Exercise(ApparatusType at, Map<WeightPlateSize, Integer> weight, int duration) {
        this.at = at;
        this.weight = weight;
        this.duration = duration;
    }

    public Map<WeightPlateSize, Integer> getWeight() {
        return weight;
    }

    public ApparatusType getApparatus() {
        return at;
    }

    public int getDuration() {
        return duration;
    }

    public static Exercise generateRandom(){
        ApparatusType arr[] = ApparatusType.values();
        Random rand = new Random(); 
        
        int noOf3 = rand.nextInt(10);
        int noOf5 = rand.nextInt(10);
        int noOf10 = rand.nextInt(10);
        if(noOf3 + noOf5 + noOf10 == 0){
            noOf3 = 1;
        }
        
        Map<WeightPlateSize, Integer> genWeight = new HashMap<WeightPlateSize, Integer>();
        genWeight.put(WeightPlateSize.SMALL_3KG, new Integer(noOf3));
        genWeight.put(WeightPlateSize.MEDIUM_5KG, new Integer(noOf5));
        genWeight.put(WeightPlateSize.LARGE_10KG, new Integer(noOf10));
        
        Exercise ret = new Exercise(arr[rand.nextInt(8)], genWeight, (rand.nextInt(40) + 15) * 500);

        return ret;
    }
}
