// Интерфейс для глубокого клонирования
public interface IDeepCloneable<T> {
    T deepClone(); // метод глубокого клонирования
}

// Класс Achievement с реализацией клонирования
public class Achievement implements Cloneable, IDeepCloneable<Achievement> {
    private String id;
    private String name;
    private String criteria;
    private int rewardPoints;

    // Конструктор
    public Achievement(String id, String name, String criteria, int reward) {
        this.id = id;
        this.name = name;
        this.criteria = criteria;
        setRewardPoints(reward); // используем сеттер для валидации
    }

    // Геттеры и сеттеры
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getCriteria() {
        return criteria;
    }

    public void setCriteria(String criteria) {
        this.criteria = criteria;
    }

    public int getRewardPoints() {
        return rewardPoints;
    }

    public void setRewardPoints(int value) {
        if (value < 0) {
            throw new IllegalArgumentException("Reward cannot be negative.");
        }
        this.rewardPoints = value;
    }

    // Поверхностное клонирование (аналог MemberwiseClone)
    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    // Глубокое клонирование (реализация интерфейса IDeepCloneable)
    @Override
    public Achievement deepClone() {
        return new Achievement(id, name, criteria, rewardPoints);
    }

    // Виртуальный метод для отображения информации (в Java все методы по умолчанию виртуальны)
    public void showAchievementInfo() {
        System.out.printf("Achievement: %s (%s) — %d pts%n", name, criteria, rewardPoints);
    }

    @Override
    public String toString() {
        return String.format("Achievement{id='%s', name='%s', criteria='%s', rewardPoints=%d}",
                id, name, criteria, rewardPoints);
    }
}
