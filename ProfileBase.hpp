#pragma once
#include <string>
#include <memory>
#include <iostream>

class ProfileBase {
public:
    ProfileBase() = default;
    virtual ~ProfileBase() = default;

    virtual void showProfileInfo() const = 0;

    void printViaNonVirtual() const {
        showProfileInfo();
    }

    virtual ProfileBase* cloneShallow() const = 0;
    virtual ProfileBase* cloneDeep() const = 0;
};
