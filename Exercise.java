import java.util.HashSet;
import java.util.Set;

class ActivityBase {
    protected String activityType;

    public ActivityBase() {
        this("General");
    }

    public ActivityBase(String type) {
        this.activityType = type;
    }

    public ActivityBase(ActivityBase other) {
        this.activityType = other.activityType;
    }

    public String getType() {
        return activityType;
    }
}

public class Exercise extends ActivityBase {
    private String name;
    private String description;
    private Set<String> requiredEquipment = new HashSet<>();
    private String difficultyLevel;

    public Exercise() {
        super("Exercise");
        this.name = "Default";
        this.description = "No description";
        this.difficultyLevel = "Beginner";
    }

    public Exercise(String name, String desc, Set<String> equip, String level) {
        super("Exercise");
        this.name = name;
        this.description = desc;
        this.requiredEquipment = new HashSet<>(equip);
        this.difficultyLevel = level;
    }

    public Exercise(Exercise other) {
        super(other);
        this.name = other.name;
        this.description = (other.description != null) ? new String(other.description) : null;
        this.requiredEquipment = new HashSet<>(other.requiredEquipment);
        this.difficultyLevel = other.difficultyLevel;
    }

    public Exercise assign(Exercise other) {
        if (this != other) {
            super.activityType = other.activityType;
            this.name = other.name;
            this.description = (other.description != null) ? new String(other.description) : null;
            this.requiredEquipment = new HashSet<>(other.requiredEquipment);
            this.difficultyLevel = other.difficultyLevel;
        }
        return this;
    }

    public Exercise getAlternative(Set<String> useEquipment, String level) {
        Exercise alt = new Exercise(this);
        alt.requiredEquipment = new HashSet<>(useEquipment);
        alt.difficultyLevel = level;
        String newDesc = "Alternative: " + description;
        int pos = newDesc.indexOf("No");
        if (pos != -1) {
            newDesc = newDesc.substring(0, pos) + "Yes" + newDesc.substring(pos + 2);
        }
        alt.description = newDesc;
        StringBuilder sb = new StringBuilder();
        sb.append("Level: ").append(level);
        alt.name += sb.toString();
        return alt;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Exercise other = (Exercise) obj;
        return name.equals(other.name) && difficultyLevel.equals(other.difficultyLevel);
    }

    public boolean notEquals(Exercise other) {
        return !this.equals(other);
    }

    public Exercise add(Exercise other) {
        Set<String> combinedEquip = new HashSet<>(requiredEquipment);
        combinedEquip.addAll(other.requiredEquipment);
        String combinedDesc = description + " + " + other.description;
        String combinedName = name + " & " + other.name;
        String combinedLevel = difficultyLevel + "/" + other.difficultyLevel;
        return new Exercise(combinedName, combinedDesc, combinedEquip, combinedLevel);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Exercise: ").append(name).append(" (").append(difficultyLevel).append(")");
        if (description != null) {
            sb.append(" - ").append(description);
        }
        sb.append("\nEquipment: ");
        for (String eq : requiredEquipment) {
            sb.append(eq).append(" ");
        }
        return sb.toString();
    }
}