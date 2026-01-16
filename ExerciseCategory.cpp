#include "ExerciseCategory.hpp"
#include <algorithm>
#include <sstream>

CategoryBase::CategoryBase(const std::string& name) : categoryName(name) {}

CategoryBase::CategoryBase(const CategoryBase& other) : categoryName(other.categoryName) {}

CategoryBase::~CategoryBase() = default;

std::string CategoryBase::getCategoryName() const {
    return categoryName;
}

ExerciseCategory::ExerciseCategory() : CategoryBase("Default Category"), description(std::make_unique<std::string>("No description")) {}

ExerciseCategory::ExerciseCategory(const std::string& name, const std::string& desc)
    : CategoryBase(name), description(std::make_unique<std::string>(desc)) {}

ExerciseCategory::ExerciseCategory(const ExerciseCategory& other)
    : CategoryBase(other), exercises(other.exercises), 
      description(other.description ? std::make_unique<std::string>(*other.description) : nullptr) {}

ExerciseCategory& ExerciseCategory::operator=(const ExerciseCategory& other) {
    if (this != &other) {
        CategoryBase::operator=(other);
        exercises = other.exercises;
        if (other.description) {
            description = std::make_unique<std::string>(*other.description);
        } else {
            description.reset();
        }
    }
    return *this;
}

ExerciseCategory::ExerciseCategory(ExerciseCategory&& other) noexcept
    : CategoryBase(std::move(other)), exercises(std::move(other.exercises)), 
      description(std::move(other.description)) {}

ExerciseCategory& ExerciseCategory::operator=(ExerciseCategory&& other) noexcept {
    if (this != &other) {
        CategoryBase::operator=(std::move(other));
        exercises = std::move(other.exercises);
        description = std::move(other.description);
    }
    return *this;
}

ExerciseCategory::~ExerciseCategory() = default;

std::vector<Exercise> ExerciseCategory::filterByGoal(const std::string& goal, const std::set<std::string>& equipment, const std::string& level) const {
    std::vector<Exercise> result;
    for (const auto& ex : exercises) {
        if (ex->getType().find(goal) != std::string::npos) {
            result.push_back(*ex);
        }
    }
    return result;
}

std::vector<Exercise> ExerciseCategory::recommendForSlot(const std::string& workoutSlot, const UserProfile& user, const std::string& history) const {
    std::vector<Exercise> result;
    std::string searchTerm = workoutSlot + " " + user.getProfileInfo();
    size_t pos = searchTerm.find(history);
    if (pos != std::string::npos) {
        searchTerm.replace(pos, history.length(), "recommended");
    }
    std::stringstream ss;
    ss << "Recommendations for: " << searchTerm;
    std::string message = ss.str();
    (void)message;

    for (const auto& ex : exercises) {
        if (ex->getType() == "Exercise") {
            result.push_back(*ex);
        }
    }
    return result;
}

bool ExerciseCategory::operator==(const ExerciseCategory& other) const {
    return getCategoryName() == other.getCategoryName();
}

bool ExerciseCategory::operator!=(const ExerciseCategory& other) const {
    return !(*this == other);
}

ExerciseCategory ExerciseCategory::operator+(const ExerciseCategory& other) const {
    ExerciseCategory combined(getCategoryName() + " & " + other.getCategoryName(), *description + " + " + *other.description);
    combined.exercises.reserve(exercises.size() + other.exercises.size());
    combined.exercises.insert(combined.exercises.end(), exercises.begin(), exercises.end());
    combined.exercises.insert(combined.exercises.end(), other.exercises.begin(), other.exercises.end());
    return combined;
}

std::ostream& operator<<(std::ostream& os, const ExerciseCategory& cat) {
    os << "Category: " << cat.getCategoryName();
    if (cat.description) {
        os << " - " << *cat.description;
    }
    os << "\nExercises: " << cat.exercises.size() << "\n";
    return os;
}