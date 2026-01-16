import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;
import java.util.List;

class ScheduleBase {
    protected String ownerName;

    public ScheduleBase() {
        this("User");
    }

    public ScheduleBase(String owner) {
        this.ownerName = owner;
    }

    public ScheduleBase(ScheduleBase other) {
        this.ownerName = other.ownerName;
    }

    public String getOwnerName() {
        return ownerName;
    }
}

public class CalendarSchedule extends ScheduleBase {
    private Workout currentWorkout;
    private Map<String, Workout> schedule = new HashMap<>();
    private List<Workout> snoozedWorkouts = new ArrayList<>();

    public CalendarSchedule() {
        super("Default User");
        this.currentWorkout = null;
    }

    public CalendarSchedule(String owner) {
        super(owner);
        this.currentWorkout = null;
    }

    public CalendarSchedule(CalendarSchedule other) {
        super(other);
        this.currentWorkout = (other.currentWorkout != null) ? new Workout(other.currentWorkout) : null;
        this.schedule = new HashMap<>(other.schedule);
        this.snoozedWorkouts = new ArrayList<>(other.snoozedWorkouts);
    }

    public CalendarSchedule assign(CalendarSchedule other) {
        if (this != other) {
            super.ownerName = other.ownerName;
            this.currentWorkout = (other.currentWorkout != null) ? new Workout(other.currentWorkout) : null;
            this.schedule = new HashMap<>(other.schedule);
            this.snoozedWorkouts = new ArrayList<>(other.snoozedWorkouts);
        }
        return this;
    }

    public void scheduleWorkout(Workout workout, String trainingSlot) {
        schedule.put(trainingSlot, new Workout(workout));
        currentWorkout = new Workout(workout);
    }

    public void snoozeWorkout(String trainingSlot, int minutes) {
        Workout workout = schedule.remove(trainingSlot);
        if (workout != null) {
            snoozedWorkouts.add(workout);
            StringBuilder sb = new StringBuilder();
            sb.append("Workout snoozed for ").append(minutes).append(" minutes.");
            String message = sb.toString();
        }
    }

    public int syncWithSystemCalendar() {
        String syncStatus = "Sync completed: " + schedule.size() + " workouts.";
        int pos = syncStatus.indexOf("completed");
        return (pos != -1) ? schedule.size() : -1;
    }

    public Workout get(String slot) {
        return schedule.get(slot);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        CalendarSchedule other = (CalendarSchedule) obj;
        return schedule.equals(other.schedule) && getOwnerName().equals(other.getOwnerName());
    }

    public boolean notEquals(CalendarSchedule other) {
        return !this.equals(other);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Calendar of ").append(getOwnerName()).append("\n");
        sb.append("Scheduled workouts: ").append(schedule.size()).append("\n");
        for (Map.Entry<String, Workout> entry : schedule.entrySet()) {
            sb.append("  [").append(entry.getKey()).append("] ").append(entry.getValue()).append("\n");
        }
        sb.append("Snoozed: ").append(snoozedWorkouts.size()).append("\n");
        return sb.toString();
    }
}