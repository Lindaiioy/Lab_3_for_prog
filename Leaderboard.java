import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;

public class Leaderboard {
    // Статическая переменная для отслеживания общих очков во всех лидербордах
    public static int totalPoints = 0;

    private String id;
    private String period;
    private List<ScoreEntry> scores;

    // Внутренний класс для представления записи в таблице лидеров
    public static class ScoreEntry {
        private String userId;
        private int points;

        public ScoreEntry(String userId, int points) {
            this.userId = userId;
            this.points = points;
        }

        public String getUserId() {
            return userId;
        }

        public int getPoints() {
            return points;
        }
    }

    // Конструктор по умолчанию
    public Leaderboard() {
        this.scores = new ArrayList<>();
    }

    // Конструктор с параметрами
    public Leaderboard(String id, String period) {
        this.id = id;
        this.period = period;
        this.scores = new ArrayList<>();
    }

    // Геттеры и сеттеры
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getPeriod() {
        return period;
    }

    public void setPeriod(String period) {
        this.period = period;
    }

    // Метод для получения копии списка scores
    public List<ScoreEntry> getScores() {
        return new ArrayList<>(scores);
    }

    // Статический метод создания лидерборда
    public static Leaderboard createLeaderboard(String id, String period) {
        return new Leaderboard(id, period);
    }

    // Метод добавления счета
    public void addScore(String userId, int points) {
        try {
            if (points < 0) {
                throw new IllegalArgumentException("Points cannot be negative.");
            }

            scores.add(new ScoreEntry(userId, points));
            totalPoints += points;
        } catch (Exception ex) {
            System.out.println("Error adding score: " + ex.getMessage());
        }
    }

    // Метод получения топ N результатов
    public List<ScoreEntry> top(int n) {
        return scores.stream()
                .sorted(Comparator.comparingInt(ScoreEntry::getPoints).reversed())
                .limit(n)
                .collect(Collectors.toList());
    }

    // Метод отображения лидерборда
    public void showLeaderboard() {
        System.out.println("Leaderboard (" + period + ")");
        List<ScoreEntry> topScores = top(scores.size());

        for (int i = 0; i < topScores.size(); i++) {
            ScoreEntry entry = topScores.get(i);
            System.out.println((i + 1) + ". " + entry.getUserId() + " — " + entry.getPoints() + " pts");
        }
    }

    // Статический метод для отображения общего количества очков
    public static void showTotalPoints() {
        System.out.println("Total points across all leaderboards: " + totalPoints);
    }

    // Альтернативная реализация метода top без использования Stream API
    public List<ScoreEntry> topAlternative(int n) {
        List<ScoreEntry> sorted = new ArrayList<>(scores);
        sorted.sort(Comparator.comparingInt(ScoreEntry::getPoints).reversed());

        if (n > sorted.size()) {
            n = sorted.size();
        }

        return sorted.subList(0, n);
    }
}
