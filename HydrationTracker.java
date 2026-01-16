import java.util.ArrayList;
import java.util.List;

public class HydrationTracker {
    private String userId;
    private int dailyGoalMl;
    private List<Integer> logs;

    // Конструктор по умолчанию
    public HydrationTracker() {
        this.dailyGoalMl = 2000;
        this.logs = new ArrayList<>();
    }

    // Параметризированный конструктор
    public HydrationTracker(String userId, int goal) {
        this.userId = userId;
        setDailyGoalMl(goal); // используем сеттер для валидации
        this.logs = new ArrayList<>();
    }

    // Геттер и сеттер для userId
    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    // Геттер и сеттер для dailyGoalMl с валидацией
    public int getDailyGoalMl() {
        return dailyGoalMl;
    }

    public void setDailyGoalMl(int value) {
        if (value <= 0) {
            throw new IllegalArgumentException("Daily goal must be positive.");
        }
        dailyGoalMl = value;
    }

    // Геттер для logs (возвращаем копию для защиты инкапсуляции)
    public List<Integer> getLogs() {
        return new ArrayList<>(logs);
    }

    // Статический метод создания
    public static HydrationTracker createHydrationTracker(String userId, int goal) {
        return new HydrationTracker(userId, goal);
    }

    // Метод добавления выпитой воды
    public void addDrink(int amount) {
        try {
            if (amount <= 0) {
                throw new IllegalArgumentException("Drink amount must be positive.");
            }
            logs.add(amount);
        } catch (Exception ex) {
            System.out.println("Error adding drink: " + ex.getMessage());
        }
    }

    // Метод расчета прогресса за сегодня
    public double progressToday() {
        int sum = logs.stream().mapToInt(Integer::intValue).sum();
        return sum == 0 ? 0.0 : (sum * 100.0) / dailyGoalMl;
    }

    // Альтернативная реализация суммирования без Stream API
    public double progressTodayAlternative() {
        int sum = 0;
        for (int amount : logs) {
            sum += amount;
        }
        return sum == 0 ? 0.0 : (sum * 100.0) / dailyGoalMl;
    }
}