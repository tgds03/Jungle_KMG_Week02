#include "stdafx.h"
#include "TName.h"

uint32 TName::count = 1;
TMap<FString, uint32> TName::names;

TName::TName(FString name): name(name) {
    if (!names[name])
        names[name] = count++;
}

bool TName::operator==(const TName& other) const {
    return (names[this->name] == names[other.name]);
}
