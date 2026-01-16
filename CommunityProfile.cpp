// CommunityProfile.cpp
#include "CommunityProfile.hpp"

// Конструкторы/деструктор
CommunityProfile::CommunityProfile() : note(new std::string("no-note")) {}

CommunityProfile::CommunityProfile(const std::string& id_, const std::string& nick_, const std::string& joined)
    : id(id_), nickname(nick_), joinedDate(joined), note(new std::string("default-note")) {
}

// Copy constructor — делает глубокую копию note (так удобнее по умолчанию)
CommunityProfile::CommunityProfile(const CommunityProfile& other)
    : id(other.id), nickname(other.nickname), joinedDate(other.joinedDate),
    friends(other.friends), badges(other.badges), note(new std::string(*(other.note))) {
    // Комментарий: реализация конструктора копирования (feature)
}

// operator= — корректно реализуем (с проверкой self-assign)
CommunityProfile& CommunityProfile::operator=(const CommunityProfile& other) {
    if (this == &other) return *this;
    id = other.id;
    nickname = other.nickname;
    joinedDate = other.joinedDate;
    friends = other.friends;
    badges = other.badges;
    // глубокое присваивание note
    if (note) delete note;
    note = new std::string(*(other.note));
    return *this;
}

CommunityProfile::~CommunityProfile() {
    // удаляем выделенную память для note
    delete note;
}

// фабрика
CommunityProfile CommunityProfile::createProfile(const std::string& id_, const std::string& nick_, const std::string& joined) {
    return CommunityProfile(id_, nick_, joined);
}

void CommunityProfile::addFriend(const std::string& friendId) {
    friends.push_back(friendId);
}

void CommunityProfile::awardBadge(const Achievement& badge) {
    badges.push_back(badge);
}

// Виртуальная функция — переопределение
void CommunityProfile::showProfileInfo() const {
    std::cout << "Profile: " << nickname << " (" << id << ")\n"
        << "  Joined: " << joinedDate << "\n"
        << "  Friends: " << friends.size() << "  Badges: " << badges.size() << "\n"
        << "  Note: " << (note ? *note : std::string("<no note>")) << "\n";
}

// operator+ (простой пример, использует this)
CommunityProfile CommunityProfile::operator+(const CommunityProfile& rhs) const {
    CommunityProfile res;
    res.id = this->id + "+" + rhs.id;
    res.nickname = this->nickname + "+" + rhs.nickname;
    res.joinedDate = this->joinedDate;
    // Пример: не копируем note — оставляем дефолт (демо)
    return res;
}

std::ostream& operator<<(std::ostream& os, const CommunityProfile& p) {
    os << p.nickname << "(" << p.id << ")";
    return os;
}

// Клонирование:
// поверхностное: копирует указатель note (shallow copy)
ProfileBase* CommunityProfile::cloneShallow() const {
    CommunityProfile* cp = new CommunityProfile();
    cp->id = id;
    cp->nickname = nickname;
    cp->joinedDate = joinedDate;
    cp->friends = friends;
    cp->badges = badges;
    // поверхностное копирование указателя — оба объекта будут указывать на одну и ту же строку
    cp->note = this->note;
    return cp;
}

// глубокое: создаёт новый note с копированием содержимого
ProfileBase* CommunityProfile::cloneDeep() const {
    CommunityProfile* cp = new CommunityProfile(*this); // copy ctor уже делает глубокую копию note
    return cp;
}