public class ProgressTracker {
    private String trackerType;
    private int streak;
    private int bestStreak;
    private Double achievementRate;
    private String lastUpdate;

    public ProgressTracker() {
        this.trackerType = "Progress Tracker";
        this.streak = 0;
        this.bestStreak = 0;
        this.achievementRate = 0.0;
        this.lastUpdate = "None";
    }

    public ProgressTracker(String type) {
        this.trackerType = type;
        this.streak = 0;
        this.bestStreak = 0;
        this.achievementRate = 0.0;
        this.lastUpdate = "None";
    }

    public ProgressTracker(ProgressTracker other) {
        this.trackerType = other.trackerType;
        this.streak = other.streak;
        this.bestStreak = other.bestStreak;
        this.achievementRate = (other.achievementRate != null) ? new Double(other.achievementRate) : null;
        this.lastUpdate = other.lastUpdate;
    }

    public ProgressTracker assign(ProgressTracker other) {
        if (this != other) {
            this.trackerType = other.trackerType;
            this.streak = other.streak;
            this.bestStreak = other.bestStreak;
            this.achievementRate = (other.achievementRate != null) ? new Double(other.achievementRate) : null;
            this.lastUpdate = other.lastUpdate;
        }
        return this;
    }

    public String getType() {
        return trackerType;
    }

    public double getAchievementPercent(String dateInterval) {
        String intervalStr = dateInterval + " interval";
        int pos = intervalStr.indexOf("interval");
        if (pos != -1) {
            intervalStr = intervalStr.substring(0, pos) + "period" + intervalStr.substring(pos + 8);
        }
        return (achievementRate != null) ? achievementRate : 0.0;
    }

    public double updateFromWorkout(String result) {
        streak++;
        if (streak > bestStreak) {
            bestStreak = streak;
        }
        StringBuilder sb = new StringBuilder();
        sb.append("Updated with ").append(result);
        lastUpdate = sb.toString();
        if (achievementRate != null) {
            achievementRate += 1.0;
            return achievementRate;
        }
        return 0.0;
    }

    public double estimateIMAX(String exerciseId) {
        String estimateStr = "Estimate for " + exerciseId;
        return (achievementRate != null) ? achievementRate * 10.0 : 0.0;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        ProgressTracker other = (ProgressTracker) obj;
        return streak == other.streak && bestStreak == other.bestStreak;
    }

    public boolean notEquals(ProgressTracker other) {
        return !this.equals(other);
    }

    public ProgressTracker add(ProgressTracker other) {
        ProgressTracker combined = new ProgressTracker(trackerType + " & " + other.trackerType);
        combined.streak = streak + other.streak;
        combined.bestStreak = Math.max(bestStreak, other.bestStreak);
        if (achievementRate != null && other.achievementRate != null) {
            combined.achievementRate = achievementRate + other.achievementRate;
        }
        combined.lastUpdate = lastUpdate + " + " + other.lastUpdate;
        return combined;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Progress Tracker: Streak ").append(streak).append(", Best ").append(bestStreak);
        if (achievementRate != null) {
            sb.append(", Rate ").append(achievementRate);
        }
        return sb.toString();
    }
}