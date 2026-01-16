import java.util.ArrayList;
import java.util.List;

class CategoryBase {
    protected String categoryName;

    public CategoryBase() {
        this("General");
    }

    public CategoryBase(String name) {
        this.categoryName = name;
    }

    public CategoryBase(CategoryBase other) {
        this.categoryName = other.categoryName;
    }

    public String getCategoryName() {
        return categoryName;
    }
}

public class ExerciseCategory extends CategoryBase {
    private List<Exercise> exercises = new ArrayList<>();
    private String description;

    public ExerciseCategory() {
        super("Default Category");
        this.description = "No description";
    }

    public ExerciseCategory(String name, String desc) {
        super(name);
        this.description = desc;
    }

    public ExerciseCategory(ExerciseCategory other) {
        super(other);
        this.exercises = new ArrayList<>(other.exercises);
        this.description = (other.description != null) ? new String(other.description) : null;
    }

    public ExerciseCategory assign(ExerciseCategory other) {
        if (this != other) {
            super.categoryName = other.categoryName;
            this.exercises = new ArrayList<>(other.exercises);
            this.description = (other.description != null) ? new String(other.description) : null;
        }
        return this;
    }

    public List<Exercise> filterByGoal(String goal, Set<String> equipment, String level) {
        List<Exercise> result = new ArrayList<>();
        for (Exercise ex : exercises) {
            if (ex.getType().contains(goal)) {
                result.add(new Exercise(ex));
            }
        }
        return result;
    }

    public List<Exercise> recommendForSlot(String workoutSlot, UserProfile user, String history) {
        List<Exercise> result = new ArrayList<>();
        String searchTerm = workoutSlot + " " + user.getProfileInfo();
        int pos = searchTerm.indexOf(history);
        if (pos != -1) {
            searchTerm = searchTerm.substring(0, pos) + "recommended" + searchTerm.substring(pos + history.length());
        }
        StringBuilder sb = new StringBuilder();
        sb.append("Recommendations for: ").append(searchTerm);
        String message = sb.toString();
        for (Exercise ex : exercises) {
            if (ex.getType().equals("Exercise")) {
                result.add(new Exercise(ex));
            }
        }
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        ExerciseCategory other = (ExerciseCategory) obj;
        return getCategoryName().equals(other.getCategoryName());
    }

    public boolean notEquals(ExerciseCategory other) {
        return !this.equals(other);
    }

    public ExerciseCategory add(ExerciseCategory other) {
        ExerciseCategory combined = new ExerciseCategory(getCategoryName() + " & " + other.getCategoryName(), description + " + " + other.description);
        combined.exercises.addAll(exercises);
        combined.exercises.addAll(other.exercises);
        return combined;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Category: ").append(getCategoryName());
        if (description != null) {
            sb.append(" - ").append(description);
        }
        sb.append("\nExercises: ").append(exercises.size()).append("\n");
        return sb.toString();
    }
}