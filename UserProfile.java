public class UserProfile {
    private String profileType;
    private int age;
    private int heightCM;
    private double weightKG;
    private boolean notificationsEnabled;
    private String userName;
    private Exercise favoriteExercise;

    public UserProfile() {
        this.profileType = "User Profile";
        this.age = 0;
        this.heightCM = 0;
        this.weightKG = 0.0;
        this.notificationsEnabled = false;
        this.userName = "Anonymous";
    }

    public UserProfile(String name, int ageVal, int height, double weight, boolean notify) {
        this.profileType = "User Profile";
        this.age = ageVal;
        this.heightCM = height;
        this.weightKG = weight;
        this.notificationsEnabled = notify;
        this.userName = name;
    }

    public UserProfile(UserProfile other) {
        this.profileType = other.profileType;
        this.age = other.age;
        this.heightCM = other.heightCM;
        this.weightKG = other.weightKG;
        this.notificationsEnabled = other.notificationsEnabled;
        this.userName = (other.userName != null) ? new String(other.userName) : null;
        this.favoriteExercise = other.favoriteExercise;
    }

    public UserProfile assign(UserProfile other) {
        if (this != other) {
            this.profileType = other.profileType;
            this.age = other.age;
            this.heightCM = other.heightCM;
            this.weightKG = other.weightKG;
            this.notificationsEnabled = other.notificationsEnabled;
            this.userName = (other.userName != null) ? new String(other.userName) : null;
            this.favoriteExercise = other.favoriteExercise;
        }
        return this;
    }

    public String getType() {
        return profileType;
    }

    public boolean canPerform(Exercise ex) {
        String level = ex.getType();
        if (level.contains("Beginner") && age < 18) {
            return false;
        }
        return true;
    }

    public double updateNewWeight(double weight) {
        weightKG = weight;
        StringBuilder sb = new StringBuilder();
        sb.append("Updated weight to ").append(weightKG).append(" kg");
        String message = sb.toString();
        int pos = message.indexOf("to");
        if (pos != -1) {
            message = message.substring(0, pos) + "at" + message.substring(pos + 2);
        }
        return weightKG;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        UserProfile other = (UserProfile) obj;
        return age == other.age && weightKG == other.weightKG;
    }

    public boolean notEquals(UserProfile other) {
        return !this.equals(other);
    }

    public UserProfile add(UserProfile other) {
        String combinedName = userName + " & " + other.userName;
        int combinedAge = (age + other.age) / 2;
        int combinedHeight = (heightCM + other.heightCM) / 2;
        double combinedWeight = (weightKG + other.weightKG) / 2;
        boolean combinedNotify = notificationsEnabled || other.notificationsEnabled;
        return new UserProfile(combinedName, combinedAge, combinedHeight, combinedWeight, combinedNotify);
    }

    @Override
    public String toString() {
        return "User: " + userName + ", Age: " + age + ", Weight: " + weightKG;
    }
}