#include <iostream>
#include <memory>
#include <vector>

#include "ProfileBase.hpp"
#include "CommunityProfile.hpp"
#include "PremiumProfile.hpp"
#include "Achievement.hpp"
#include "Leaderboard.hpp"
#include "SleepTracker.hpp"
#include "HydrationTracker.hpp"
#include "RecoverySession.hpp"
#include "Challenge.hpp"

int main() {

    // --- создаём базовый профиль (CommunityProfile) и premium профиль (производный) ---
    CommunityProfile alice = CommunityProfile::createProfile("u1", "Alice", "2025-01-01");
    alice.note = new std::string("Alice initial note"); 

    PremiumProfile premiumBob("u2", "BobPremium", "2025-02-10", "Gold");
    premiumBob.note = new std::string("BobPremium note");

    // Demonstration protected: PremiumProfile can access friends/badges directly in operator=
    alice.addFriend("uX");
    premiumBob.addFriend("uY");

    // --- virtual functions via a base pointer ---
    ProfileBase* basePtr = &alice;      // указываем на базовый объект
    ProfileBase* derivedPtr = &premiumBob; // указываем на производный через базовый указатель

    std::cout << "[Calling a virtual function via a base pointer]\n";
    basePtr->showProfileInfo();     // вызывает CommunityProfile::showProfileInfo
    derivedPtr->showProfileInfo();  // вызывает PremiumProfile::showProfileInfo (переопределённый)

    // вызов виртуальной функции через невиртуальную обёртку базового класса 
    std::cout << "\n[Calling via a non-virtual wrapper printViaNonVirtual()]\n";
    basePtr->printViaNonVirtual();     // вызывает виртуальную функцию внутри -> динамический полиморфизм
    derivedPtr->printViaNonVirtual();  // тоже вызывает переопределённую реализацию

    // демонстрация клонирования: поверхностного и глубокого 
    std::cout << "\n[Profile cloning (shallow vs deep)]\n";
    ProfileBase* shallow = alice.cloneShallow();
    ProfileBase* deep = alice.cloneDeep();

    // приводим к типу CommunityProfile* чтобы посмотреть note
    CommunityProfile* shallowCp = dynamic_cast<CommunityProfile*>(shallow);
    CommunityProfile* deepCp = dynamic_cast<CommunityProfile*>(deep);

    std::cout << "Original note: " << (alice.note ? *alice.note : "<null>") << "\n";
    std::cout << "Shallow note: " << (shallowCp->note ? *shallowCp->note : "<null>") << "\n";
    std::cout << "Deep note: " << (deepCp->note ? *deepCp->note : "<null>") << "\n";

    // Изменим оригиналную заметку и посмотрим поведение
    *alice.note = "Alice changed note";

    std::cout << "-- After changing original --\n";
    std::cout << "Original note: " << *alice.note << "\n";
    std::cout << "Shallow note: " << (shallowCp->note ? *shallowCp->note : "<null>") << " (same pointer -> changed)\n";
    std::cout << "Deep note: " << (deepCp->note ? *deepCp->note : "<null>") << " (deep copy -> unchanged)\n";

    // оператор присваивания базового класса к производному
    std::cout << "\n[operator= from CommunityProfile to PremiumProfile]\n";
    CommunityProfile copySrc = CommunityProfile::createProfile("u100", "CopySrc", "2025-07-07");
    copySrc.note = new std::string("copySrc note");
    premiumBob = copySrc; // используем PremiumProfile::operator=(const CommunityProfile&)
    premiumBob.showProfileInfo();

    // запрет копирования Leaderboard
    std::cout << "\n[Leaderboard copy ctor is deleted: compile-time check]\n";
    Leaderboard lb = Leaderboard::createLeaderboard("lb1", "week");
    lb += {"u1", 100};
    lb += {"u2", 50};
    lb.showLeaderboard();
    std::cout << "Attempting copy would fail at compile time (line commented)\n";

    //  виртуальный деструктор проверка: удаление через базовый указатель ---
    ProfileBase* ptmp = new PremiumProfile("tmp", "TmpUser", "2025-08-01", "Silver");
    delete ptmp; 

    delete shallow;
    delete deep;

    return 0;
}