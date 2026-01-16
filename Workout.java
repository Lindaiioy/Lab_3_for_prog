public class Workout {
    private String workoutType;
    private String date;
    private String metricsData;
    private Double caloriesEstimate;

    public Workout() {
        this.workoutType = "Workout";
        this.date = "Today";
        this.metricsData = "No metrics";
    }

    public Workout(String dateVal) {
        this.workoutType = "Workout";
        this.date = dateVal;
        this.metricsData = "No metrics";
    }

    public Workout(Workout other) {
        this.workoutType = other.workoutType;
        this.date = other.date;
        this.metricsData = (other.metricsData != null) ? new String(other.metricsData) : null;
        this.caloriesEstimate = other.caloriesEstimate;
    }

    public Workout assign(Workout other) {
        if (this != other) {
            this.workoutType = other.workoutType;
            this.date = other.date;
            this.metricsData = (other.metricsData != null) ? new String(other.metricsData) : null;
            this.caloriesEstimate = other.caloriesEstimate;
        }
        return this;
    }

    public String getType() {
        return workoutType;
    }

    public int complete(String metrics) {
        StringBuilder sb = new StringBuilder();
        sb.append("Completed with ").append(metrics);
        metricsData = sb.toString();
        int pos = metricsData.indexOf("with");
        if (pos != -1) {
            metricsData = metricsData.substring(0, pos) + "using" + metricsData.substring(pos + 4);
        }
        return 1;
    }

    public String reschedule(String newDate) {
        date = newDate;
        return "Rescheduled to " + date;
    }

    public double estimateCaloriesUsed() {
        String estimateStr = "Estimate: 500";
        return (caloriesEstimate != null) ? caloriesEstimate : 0.0;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Workout other = (Workout) obj;
        return date.equals(other.date);
    }

    public boolean notEquals(Workout other) {
        return !this.equals(other);
    }

    public Workout add(Workout other) {
        String combinedDate = date + " & " + other.date;
        return new Workout(combinedDate);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Workout on ").append(date);
        if (metricsData != null) {
            sb.append(" - ").append(metricsData);
        }
        return sb.toString();
    }
}