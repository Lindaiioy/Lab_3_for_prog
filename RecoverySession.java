import java.util.Objects;

public class RecoverySession {
    private String id;
    private String date;
    private String type;
    private int durationMin;
    private String notes;

    // Конструктор по умолчанию
    public RecoverySession() { }

    // Полный конструктор
    public RecoverySession(String id, String date, String type, int durationMin, String notes) {
        this.id = id;
        this.date = date;
        this.type = type;
        setDurationMin(durationMin); // Используем сеттер для валидации
        this.notes = notes;
    }

    // Геттеры и сеттеры
    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    public String getDate() {
        return date;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }

    public int getDurationMin() {
        return durationMin;
    }

    public void setDurationMin(int value) {
        if (value <= 0) {
            throw new IllegalArgumentException("Duration must be positive.");
        }
        durationMin = value;
    }

    public String getNotes() {
        return notes;
    }

    public void setNotes(String notes) {
        this.notes = notes;
    }

    // Статический метод создания сессии
    public static RecoverySession createSession(String id, String date, String type, int durationMin, String notes) {
        return new RecoverySession(id, date, type, durationMin, notes);
    }

    // Метод логирования завершения сессии
    public void logCompletion() {
        System.out.println("Session completed!");
    }

    // Метод получения преимуществ
    public void getBenefits() {
        System.out.println("Benefits of " + type + ": relaxation + recovery");
    }

    // Метод отображения информации о сессии
    public void showSessionInfo() {
        System.out.println(type + " session on " + date + ", " + durationMin + " min\nNotes: " + notes);
    }

    // Переопределение метода toString для удобного вывода
    @Override
    public String toString() {
        return "RecoverySession{" +
                "id='" + id + '\'' +
                ", date='" + date + '\'' +
                ", type='" + type + '\'' +
                ", durationMin=" + durationMin +
                ", notes='" + notes + '\'' +
                '}';
    }

    // Переопределение equals и hashCode для сравнения объектов
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        RecoverySession that = (RecoverySession) o;
        return durationMin == that.durationMin &&
                Objects.equals(id, that.id) &&
                Objects.equals(date, that.date) &&
                Objects.equals(type, that.type) &&
                Objects.equals(notes, that.notes);
    }

    @Override
    public int hashCode() {
        return Objects.hash(id, date, type, durationMin, notes);
    }
}
