import java.util.ArrayList;
import java.util.List;

public class WorkoutPlan extends Workout {  // Придумываем наследование: WorkoutPlan extends Workout для демонстрации вызова базового конструктора
    private String planName;
    private UserProfile userProfile;
    private List<Workout> upcomingWorkouts = new ArrayList<>();

    public WorkoutPlan() {
        super();  // Вызов конструктора базового класса
        this.planName = "Workout Plan";
        this.userProfile = null;
    }

    public WorkoutPlan(String name) {
        super("Plan Date");  // Вызов конструктора базового класса с параметром
        this.planName = name;
        this.userProfile = null;
    }

    public WorkoutPlan(WorkoutPlan other) {
        super(other);  // Вызов копи-конструктора базового
        this.planName = other.planName;
        this.upcomingWorkouts = new ArrayList<>(other.upcomingWorkouts);
        this.userProfile = (other.userProfile != null) ? new UserProfile(other.userProfile) : null;
    }

    public WorkoutPlan assign(WorkoutPlan other) {
        if (this != other) {
            super.assign(other);  // Присваивание базового
            this.planName = other.planName;
            this.upcomingWorkouts = new ArrayList<>(other.upcomingWorkouts);
            this.userProfile = (other.userProfile != null) ? new UserProfile(other.userProfile) : null;
        }
        return this;
    }

    public String getPlanName() {
        return planName;
    }

    public void generatePersonalizedParams(ExerciseCategory category) {
        String params = "Params for " + category.getCategoryName();
        int pos = params.indexOf("for");
        if (pos != -1) {
            params = params.substring(0, pos) + "based on" + params.substring(pos + 3);
        }
    }

    public void adaptOnFeedback(String feedback) {
        StringBuilder sb = new StringBuilder();
        sb.append("Adapted based on: ").append(feedback);
        String message = sb.toString();
        message += "!";
    }

    public List<Workout> getUpcoming(int count) {
        List<Workout> result = new ArrayList<>();
        for (int i = 0; i < count && i < upcomingWorkouts.size(); i++) {
            result.add(new Workout(upcomingWorkouts.get(i)));
        }
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        WorkoutPlan other = (WorkoutPlan) obj;
        return planName.equals(other.planName);
    }

    public boolean notEquals(WorkoutPlan other) {
        return !this.equals(other);
    }

    public WorkoutPlan add(WorkoutPlan other) {
        WorkoutPlan combined = new WorkoutPlan(planName + " & " + other.planName);
        combined.upcomingWorkouts.addAll(upcomingWorkouts);
        combined.upcomingWorkouts.addAll(other.upcomingWorkouts);
        return combined;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Workout Plan: ").append(planName).append("\nUpcoming: ").append(upcomingWorkouts.size());
        return sb.toString();
    }
}