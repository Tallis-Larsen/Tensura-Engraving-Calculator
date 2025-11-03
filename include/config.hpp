#pragma once

enum SelectedTab {
    WEAPON,
    ARMOR,
    HELMET
};

enum Rarity {
    COMMON,
    UNCOMMON,
    RARE,
    VERY_RARE
};

enum Tier {
    UNIQUE,
    LEGENDARY,
    GOD
};

struct Engraving {
    Rarity rarity;
    std::string name;
    int level;
    int maxLevel = 1;
};

inline std::string rarityToString(Rarity rarity) {
    switch (rarity) {
        case COMMON:
            return "COMMON";
        case UNCOMMON:
            return "UNCOMMON";
        case RARE:
            return "RARE";
        case VERY_RARE:
            return "VERY RARE";
    }
    return "ERROR: Bad rarity value";
}

namespace Config {
    inline std::vector<Engraving> weaponEngravings = {
        {COMMON, "Swift", 1},
        {COMMON, "Sturdy", 1},
        {COMMON, "Crushing", 1},
        {UNCOMMON, "Magic Weapon", 1},
        {UNCOMMON, "Holy Weapon", 1},
        {UNCOMMON, "Slotting", 1, 3},
        {RARE, "Energy Steal", 1},
        {RARE, "Slotting", 2, 3},
        {RARE, "Barrier Piercing", 1},
        {VERY_RARE, "Severance", 1},
        {VERY_RARE, "Soul Eater", 1},
        {VERY_RARE, "Slotting", 3, 3}
    };

    inline std::vector<Engraving> armorEngravings = {
        {COMMON, "Sturdy", 1},
        {UNCOMMON, "Elemental Boost", 1, 2},
        {UNCOMMON, "Elemental Resistance", 1, 2},
        {VERY_RARE, "Elemental Boost", 2, 2},
        {VERY_RARE, "Elemental Resistance", 2, 2}
    };

    inline std::vector<Engraving> helmetEngravings = {
        {COMMON, "Sturdy", 1},
        {UNCOMMON, "Breathing Support", 1},
        {UNCOMMON, "Elemental Boost", 1, 2},
        {UNCOMMON, "Elemental Resistance", 1, 2},
        {VERY_RARE, "Elemental Boost", 2, 2},
        {VERY_RARE, "Elemental Resistance", 2, 2}
    };

    inline std::vector<std::pair<Rarity, float>> uniqueRarities = {
        std::pair<Rarity, float>(COMMON, 0.50),
        std::pair<Rarity, float>(UNCOMMON, 0.30),
        std::pair<Rarity, float>(RARE, 0.15),
        std::pair<Rarity, float>(VERY_RARE, 0.05)
    };

    inline std::vector<std::pair<Rarity, float>> legendaryRarities = {
        std::pair<Rarity, float>(UNCOMMON, 0.40),
        std::pair<Rarity, float>(RARE, 0.40),
        std::pair<Rarity, float>(VERY_RARE, 0.20)
    };

    inline std::vector<std::pair<Rarity, float>> godRarities = {
        std::pair<Rarity, float>(RARE, 0.60),
        std::pair<Rarity, float>(VERY_RARE, 0.40)
    };
}
