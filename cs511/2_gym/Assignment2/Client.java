package Assignment2;
import java.util.*;

public class Client {

    private int id;
    private List<Exercise> routine;

    public Client(int id) {
        this.id = id;
        routine = new ArrayList<Exercise>();
    }

    public int getId() {
        return id;
    }

    public List<Exercise> getRoutine() {
        return routine;
    }

    public void addExercise(Exercise e) {
        this.routine.add(e);
        return;
    }

    public static Client generateRandom(int id) {
        Client ret = new Client(id);
        Random rand = new Random();
        
        int noOfExercises = rand.nextInt(6) + 15;
        for(int x = 0; x < noOfExercises; x++){
            ret.addExercise(Exercise.generateRandom());
        }
        
        return ret;
    }
}
