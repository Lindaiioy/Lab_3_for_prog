public class Program {
    public static void main(String[] args) {
        System.out.println("==== Демонстрация полиморфизма ====");

        // ---------------------------------------------
        // 1. Создание объектов + полиморфизм
        // ---------------------------------------------

        Challenge ch = new Challenge("C1", "Daily Run", "Run 1 km");
        Challenge adv = new AdvancedChallenge("C2", "Swim", "Swim 500m", 3);

        System.out.println("\nВызов метода из объекта базового класса:");
        ch.showChallengeInfo();

        System.out.println("\nВызов метода из объекта, приведенного к базовому типу:");
        Challenge ref2 = adv;
        ref2.showChallengeInfo(); // работает полиморфизм

        // ---------------------------------------------
        // 2. Protected и наследование
        // ---------------------------------------------
        System.out.println("\nAdvancedChallenge имеет доступ к protected Participants.");

        // ---------------------------------------------
        // 3. Клонирование и поверхностное копирование
        // ---------------------------------------------
        Achievement a1 = new Achievement("A1", "Wake Up", "Wake early", 50);

        // В Java нужно обработать исключение CloneNotSupportedException
        Achievement shallow = null;
        try {
            shallow = (Achievement) a1.clone();
        } catch (CloneNotSupportedException e) {
            System.out.println("Клонирование не поддерживается: " + e.getMessage());
        }

        Achievement deep = a1.deepClone();

        System.out.println("\nПоверхностное и глубокое клонирование достижения.");

        // ---------------------------------------------
        // 4. Абстрактное использование (через интерфейс)
        // ---------------------------------------------
        IResettable r = new AdvancedChallenge("C3", "Push Ups", "Do 20 push ups", 2);
        r.reset();

        System.out.println("\nАбстрактное использование (интерфейс + полиморфизм) продемонстрировано.");

        // ---------------------------------------------
        // 5. Сравнение поведения метода (base + без base)
        // ---------------------------------------------
        System.out.println("\nСравнение GetProgress():");
        System.out.println("Base: " + ch.getProgress("u1"));
        System.out.println("Derived: " + adv.getProgress("u1"));

        System.out.println("\n=== Конец демонстрации ===");
    }
}

// Вспомогательные классы, которые должны быть в том же файле
// (обычно в Java каждый класс в отдельном файле, но для примера можно так)

interface IResettable {
    void reset();
}

class Achievement implements Cloneable {
    private String id;
    private String name;
    private String criteria;
    private int rewardPoints;

    public Achievement(String id, String name, String criteria, int reward) {
        this.id = id;
        this.name = name;
        this.criteria = criteria;
        this.rewardPoints = reward;
    }

    @Override
    public Object clone() throws CloneNotSupportedException {
        return super.clone();
    }

    public Achievement deepClone() {
        return new Achievement(id, name, criteria, rewardPoints);
    }
}

class Challenge {
    private String id;
    private String title;
    private String description;
    protected java.util.List<String> participants;

    public Challenge(String id, String title, String description) {
        this.id = id;
        this.title = title;
        this.description = description;
        this.participants = new java.util.ArrayList<>();
    }

    public void showChallengeInfo() {
        System.out.println("Challenge: " + title + " — " + description);
    }

    public double getProgress(String userId) {
        return participants.contains(userId) ? 30.0 : 0.0;
    }
}

class AdvancedChallenge extends Challenge implements IResettable {
    private int difficulty;

    public AdvancedChallenge(String id, String title, String description, int difficulty) {
        super(id, title, description);
        this.difficulty = difficulty;
    }

    @Override
    public void showChallengeInfo() {
        super.showChallengeInfo();
        System.out.println("Difficulty: " + difficulty);
    }

    @Override
    public double getProgress(String userId) {
        return 80.0;
    }

    @Override
    public void reset() {
        participants.clear();
        System.out.println("Challenge Reset!");
    }
}