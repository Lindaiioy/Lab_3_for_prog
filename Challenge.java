import java.util.ArrayList;
import java.util.List;

public class Challenge {
    // Поля с приватным доступом и геттерами/сеттерами
    private String id;
    private String title;
    private String description;

    // NEW: protected (доступен в подклассах)
    protected List<String> participants = new ArrayList<>();

    // Конструктор
    public Challenge(String id, String title, String description) {
        this.id = id;
        this.title = title;
        this.description = description;
    }

    // Геттеры и сеттеры
    // Id имеет геттер с публичным доступом и сеттер с protected
    public String getId() {
        return id;
    }

    protected void setId(String id) {
        this.id = id;
    }

    // Title имеет публичный геттер и сеттер
    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    // Description имеет публичный геттер и сеттер
    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    // Виртуальный метод для отображения информации
    public void showChallengeInfo() {
        System.out.printf("Challenge: %s — %s%n", title, description);
    }

    // Виртуальный метод для получения прогресса
    public double getProgress(String userId) {
        return participants.contains(userId) ? 30.0 : 0.0;
    }

    // Метод для добавления участника
    public void addParticipant(String userId) {
        participants.add(userId);
    }

    // Метод для получения списка участников (геттер)
    public List<String> getParticipants() {
        return participants;
    }

    // Метод для очистки списка участников
    public void clearParticipants() {
        participants.clear();
    }
}