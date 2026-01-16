import java.util.ArrayList;
import java.util.List;
import java.util.OptionalDouble;
import java.util.stream.Collectors;

public class SleepTracker {
    private String userId;
    private List<Integer> sleepRecords;

    // Конструктор по умолчанию
    public SleepTracker() {
        this.sleepRecords = new ArrayList<>();
    }

    // Конструктор с userId
    public SleepTracker(String userId) {
        this.userId = userId;
        this.sleepRecords = new ArrayList<>();
    }

    // Геттер и сеттер для userId
    public String getUserId() {
        return userId;
    }

    public void setUserId(String userId) {
        this.userId = userId;
    }

    // Геттер для sleepRecords (возвращаем копию списка для защиты инкапсуляции)
    public List<Integer> getSleepRecords() {
        return new ArrayList<>(sleepRecords);
    }

    // Сеттер для sleepRecords с валидацией
    public void setSleepRecords(List<Integer> value) {
        if (value == null) {
            throw new NullPointerException("Sleep records cannot be null.");
        }
        sleepRecords = new ArrayList<>(value);
    }

    // Статический метод создания трекера
    public static SleepTracker createSleepTracker(String userId) {
        return new SleepTracker(userId);
    }

    // Метод записи сна
    public void logSleep(int hours) {
        try {
            if (hours <= 0) {
                throw new IllegalArgumentException("Sleep hours must be positive.");
            }
            sleepRecords.add(hours);
        } catch (Exception ex) {
            System.out.println("Error logging sleep: " + ex.getMessage());
        }
    }

    // Метод расчета среднего сна за последние N дней (с использованием Stream API)
    public double averageSleep(int days) {
        if (sleepRecords.isEmpty()) {
            return 0.0;
        }

        int count = Math.min(days, sleepRecords.size());

        // Используем Stream API для вычисления среднего
        OptionalDouble average = sleepRecords
                .stream()
                .skip(sleepRecords.size() - count)
                .mapToInt(Integer::intValue)
                .average();

        return average.isPresent() ? average.getAsDouble() : 0.0;
    }

    // Альтернативная реализация без Stream API
    public double averageSleepAlternative(int days) {
        if (sleepRecords.isEmpty()) {
            return 0.0;
        }

        int count = Math.min(days, sleepRecords.size());
        int sum = 0;

        for (int i = sleepRecords.size() - count; i < sleepRecords.size(); i++) {
            sum += sleepRecords.get(i);
        }

        return (double) sum / count;
    }

    // Метод для получения последних N записей
    public List<Integer> getRecentSleepRecords(int days) {
        int count = Math.min(days, sleepRecords.size());
        return sleepRecords
                .stream()
                .skip(sleepRecords.size() - count)
                .collect(Collectors.toList());
    }

    // Метод для получения общего количества записей
    public int getRecordCount() {
        return sleepRecords.size();
    }

    // Метод для получения общей суммы часов сна
    public int getTotalSleepHours() {
        return sleepRecords.stream().mapToInt(Integer::intValue).sum();
    }

    // Метод для очистки записей
    public void clearRecords() {
        sleepRecords.clear();
    }
}