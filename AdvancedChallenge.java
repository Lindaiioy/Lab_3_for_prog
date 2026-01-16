// Интерфейс IResettable
public interface IResettable {
    void reset();
}

// Базовый класс Challenge (предполагается, что он существует)
class Challenge {
    protected String id;
    protected String title;
    protected String description;
    protected java.util.List<String> participants;

    public Challenge(String id, String title, String description) {
        this.id = id;
        this.title = title;
        this.description = description;
        this.participants = new java.util.ArrayList<>();
    }

    public void showChallengeInfo() {
        System.out.println("Challenge ID: " + id);
        System.out.println("Title: " + title);
        System.out.println("Description: " + description);
    }

    public double getProgress(String userId) {
        // Базовая реализация, возвращает 0.0
        return 0.0;
    }

    // Геттеры и сеттеры
    public java.util.List<String> getParticipants() {
        return participants;
    }

    public void clearParticipants() {
        participants.clear();
    }
}

// Класс AdvancedChallenge
public class AdvancedChallenge extends Challenge implements IResettable {
    private int difficulty;

    public AdvancedChallenge(String id, String title, String description, int difficulty) {
        super(id, title, description); // вызов базового конструктора
        this.difficulty = difficulty;
    }

    @Override
    public void showChallengeInfo() {
        super.showChallengeInfo(); // вызов базовой версии
        System.out.println("Difficulty: " + difficulty);
    }

    @Override
    public double getProgress(String userId) {
        // переопределение без вызова super
        return 80.0;
    }

    @Override
    public void reset() {
        participants.clear(); // очистка списка участников
        System.out.println("Challenge Reset!");
    }

    // Геттер и сеттер для difficulty
    public int getDifficulty() {
        return difficulty;
    }

    public void setDifficulty(int difficulty) {
        this.difficulty = difficulty;
    }
}
