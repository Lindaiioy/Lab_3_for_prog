public class Mascot {
    private String mascotType;
    private int xp;
    private String name;
    private ProgressTracker tracker;

    public Mascot() {
        this.mascotType = "Mascot";
        this.xp = 0;
        this.name = "Default Mascot";
    }

    public Mascot(String nameStr, int initialXp) {
        this.mascotType = "Mascot";
        this.xp = initialXp;
        this.name = nameStr;
    }

    public Mascot(Mascot other) {
        this.mascotType = other.mascotType;
        this.xp = other.xp;
        this.name = (other.name != null) ? new String(other.name) : null;
        this.tracker = other.tracker;
    }

    public Mascot assign(Mascot other) {
        if (this != other) {
            this.mascotType = other.mascotType;
            this.xp = other.xp;
            this.name = (other.name != null) ? new String(other.name) : null;
            this.tracker = other.tracker;
        }
        return this;
    }

    public String getType() {
        return mascotType;
    }

    public String reactToWorkoutStart(Workout workoutStatus) {
        String message = "Let's go with " + workoutStatus.getName() + "!";
        int pos = message.indexOf("go");
        if (pos != -1) {
            message = message.substring(0, pos) + "start" + message.substring(pos + 2);
        }
        return message;
    }

    public String getDailyMessage(UserProfile user, ProgressTracker progress) {
        StringBuilder sb = new StringBuilder();
        sb.append("Good morning, ").append(user.getProfileInfo()).append("! Progress: ").append(progress.getProgress());
        String daily = sb.toString();
        daily += " Keep it up!";
        return daily;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Mascot other = (Mascot) obj;
        return xp == other.xp && name.equals(other.name);
    }

    public boolean notEquals(Mascot other) {
        return !this.equals(other);
    }

    public Mascot add(Mascot other) {
        String combinedName = name + " & " + other.name;
        int combinedXp = xp + other.xp;
        return new Mascot(combinedName, combinedXp);
    }

    @Override
    public String toString() {
        return "Mascot: " + name + " (XP: " + xp + ")";
    }
}