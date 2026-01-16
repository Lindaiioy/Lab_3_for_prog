import java.util.HashMap;
import java.util.Map;

public class NutritionPlan {
    private String planType;
    private Map<String, Recipe> meals = new HashMap<>();
    private Double weightTarget;

    public NutritionPlan() {
        this.planType = "Nutrition Plan";
        this.weightTarget = 0.0;
    }

    public NutritionPlan(String type) {
        this.planType = type;
        this.weightTarget = 0.0;
    }

    public NutritionPlan(NutritionPlan other) {
        this.planType = other.planType;
        this.meals = new HashMap<>(other.meals);
        this.weightTarget = (other.weightTarget != null) ? new Double(other.weightTarget) : null;
    }

    public NutritionPlan assign(NutritionPlan other) {
        if (this != other) {
            this.planType = other.planType;
            this.meals = new HashMap<>(other.meals);
            this.weightTarget = (other.weightTarget != null) ? new Double(other.weightTarget) : null;
        }
        return this;
    }

    public String getType() {
        return planType;
    }

    public double adjustWeightChangeTargetKg(double kg) {
        String strKg = Double.toString(kg);
        int pos = strKg.indexOf(".");
        if (pos != -1) {
            strKg = strKg.substring(0, pos) + "," + strKg.substring(pos + 1);
        }
        double adjusted = Double.parseDouble(strKg);
        this.weightTarget = adjusted;
        return adjusted;
    }

    public void replaceMeal(String mealType, Recipe newRecipe) {
        meals.put(mealType, new Recipe(newRecipe));
        StringBuilder sb = new StringBuilder();
        sb.append("Replaced ").append(mealType).append(" with ").append(newRecipe.getName());
        String message = sb.toString();
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        NutritionPlan other = (NutritionPlan) obj;
        return planType.equals(other.planType);
    }

    public boolean notEquals(NutritionPlan other) {
        return !this.equals(other);
    }

    public NutritionPlan add(NutritionPlan other) {
        NutritionPlan combined = new NutritionPlan(planType + " & " + other.planType);
        combined.meals.putAll(meals);
        combined.meals.putAll(other.meals);
        if (weightTarget != null && other.weightTarget != null) {
            combined.weightTarget = (weightTarget + other.weightTarget) / 2;
        }
        return combined;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("Nutrition Plan: ").append(planType).append("\nMeals: ").append(meals.size());
        return sb.toString();
    }
}