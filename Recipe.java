public class Recipe {
    private String recipeType;
    private String perServing;
    private String instructions;
    private UserProfile associatedProfile;

    public Recipe() {
        this.recipeType = "Recipe";
        this.perServing = "1 serving";
        this.instructions = "No instructions";
    }

    public Recipe(String servingInfo) {
        this.recipeType = "Recipe";
        this.perServing = servingInfo;
        this.instructions = "No instructions";
    }

    public Recipe(Recipe other) {
        this.recipeType = other.recipeType;
        this.perServing = other.perServing;
        this.instructions = (other.instructions != null) ? new String(other.instructions) : null;
        this.associatedProfile = other.associatedProfile;
    }

    public Recipe assign(Recipe other) {
        if (this != other) {
            this.recipeType = other.recipeType;
            this.perServing = other.perServing;
            this.instructions = (other.instructions != null) ? new String(other.instructions) : null;
            this.associatedProfile = other.associatedProfile;
        }
        return this;
    }

    public String getType() {
        return recipeType;
    }

    public String scaleServings(double num) {
        StringBuilder sb = new StringBuilder();
        sb.append(num).append(" x ").append(perServing);
        String scaled = sb.toString();
        int pos = scaled.indexOf("x");
        if (pos != -1) {
            scaled = scaled.substring(0, pos) + "times" + scaled.substring(pos + 1);
        }
        return scaled;
    }

    public boolean matchesPreferences(UserProfile profile) {
        String prefs = profile.getProfileInfo();
        return prefs.contains(perServing);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        Recipe other = (Recipe) obj;
        return perServing.equals(other.perServing);
    }

    public boolean notEquals(Recipe other) {
        return !this.equals(other);
    }

    public Recipe add(Recipe other) {
        String combinedServing = perServing + " + " + other.perServing;
        return new Recipe(combinedServing);
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Recipe: ").append(perServing);
        if (instructions != null) {
            sb.append(" - ").append(instructions);
        }
        return sb.toString();
    }
}