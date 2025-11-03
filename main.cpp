#include <iostream>
#include <ui.hpp>

using namespace std;

void calculateProbabilities();
void setAvailable();
void setRarityCounts();
void checkEngrave(const pair<Rarity, float> & pair, const Engraving & engraving);
Engraving findEngraving(const string & name);

vector<Engraving>* availableEngravings = nullptr;
deque<bool>* selectedEngravings = nullptr;
vector<pair<Rarity, float>>* availableRarities = nullptr;
vector <pair<Engraving, float>> engravingProbabilities;
array<float, 4> rarityCounts;
float noEngravingChance;

int main() {
    UI::start(calculateProbabilities);
}

void calculateProbabilities() {
    setAvailable();
    setRarityCounts();
    engravingProbabilities.clear();
    noEngravingChance = 0.0;

    for (auto & rarity : *availableRarities) {
        bool canEngrave = false;
        for (auto & engraving : *availableEngravings) {
            if (rarity.first == engraving.rarity) {
                checkEngrave(rarity, engraving);
                canEngrave = true;
            }
        }
        if (!canEngrave) {
            noEngravingChance += rarity.second;
        }
    }

    UI::updateProbabilities(engravingProbabilities, noEngravingChance);

}

void checkEngrave(const pair<Rarity, float> &pair, const Engraving &engraving) {

    Engraving newEngraving = engraving;

    switch (engraving.rarity) {
        case COMMON:
            newEngraving.level = 1;
            break;
        case UNCOMMON:
            newEngraving.level = 1;
            break;
        case RARE:
            newEngraving.level = 2;
            break;
        case VERY_RARE:
            newEngraving.level = 3;
            break;
        default:
            cerr << "[ERROR]: Invalid rarity\n";
            exit(1);
    }

    if (newEngraving.level > engraving.maxLevel) {
        newEngraving.level = engraving.maxLevel;
    }

    Engraving previousEngraving = findEngraving(engraving.name);

    if (previousEngraving.level == previousEngraving.maxLevel || previousEngraving.level > newEngraving.level) {
        noEngravingChance += pair.second * (1 / rarityCounts[engraving.rarity]);
        return;
    }

    if (previousEngraving.level == newEngraving.level && previousEngraving.level == 1) {
        noEngravingChance += pair.second * (1 / rarityCounts[engraving.rarity]);
        return;
    }

    if (previousEngraving.level < 0 || previousEngraving.level < newEngraving.level) {
        engravingProbabilities.push_back(make_pair(newEngraving, pair.second * (1 / rarityCounts[engraving.rarity])));
        return;
    }

    if (previousEngraving.level == newEngraving.level) {
        newEngraving.level++;
        engravingProbabilities.push_back(make_pair(newEngraving, pair.second * (1 / rarityCounts[engraving.rarity])));
        return;
    }

    std::cerr << "[ERROR]: A level calculation edge case was not caught\n";
    exit(1);

}

Engraving findEngraving(const string & name) {
    for (int i = 0; i < availableEngravings->size(); i++) {
        if (availableEngravings->at(i).name == name && (*selectedEngravings)[i]) {
            return availableEngravings->at(i);
        }
    }
    return {COMMON, "NONE", -1};
}

void setAvailable() {
    switch (UI::selectedTab) {
        case WEAPON:
            availableEngravings = &Config::weaponEngravings;
            selectedEngravings = &UI::selectedWeaponEngravings;
            break;
        case ARMOR:
            availableEngravings = &Config::armorEngravings;
            selectedEngravings = &UI::selectedArmorEngravings;
            break;
        case HELMET:
            availableEngravings = &Config::helmetEngravings;
            selectedEngravings = &UI::selectedHelmetEngravings;
            break;
        default:
            cerr << "[ERROR]: Invalid item type\n";
            exit(1);

    }

    if (!UI::isEngraved) {
        for (int i = 0; i < selectedEngravings->size(); i++) {
            (*selectedEngravings)[i] = false;
        }
    }

    switch (UI::selectedTier) {
        case UNIQUE:
            availableRarities = &Config::uniqueRarities;
            break;
        case LEGENDARY:
            availableRarities = &Config::legendaryRarities;
            break;
        case GOD:
            availableRarities = &Config::godRarities;
            break;
        default:
            cerr << "[ERROR]: Invalid item tier\n";
            exit(1);
    }

}

void setRarityCounts() {
    rarityCounts = {0.0, 0.0, 0.0, 0.0};
    for (auto & engraving : *availableEngravings) {
        rarityCounts[engraving.rarity]++;
    }
}