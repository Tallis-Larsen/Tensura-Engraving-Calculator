#pragma once

enum SelectedTab {
    WEAPON,
    ARMOR_NON_HELMET,
    ARMOR_HELMET
};

enum Rarity {
    COMMON,
    UNCOMMON,
    RARE,
    VERY_RARE
};

namespace Config {
    inline std::vector<std::pair<Rarity, std::string> > weaponEngravings = {
        std::pair<Rarity, std::string>(COMMON, "Swift"),
        std::pair<Rarity, std::string>(COMMON, "Sturdy"),
        std::pair<Rarity, std::string>(COMMON, "Crushing"),
        std::pair<Rarity, std::string>(UNCOMMON, "Magic Weapon"),
        std::pair<Rarity, std::string>(UNCOMMON, "Holy Weapon"),
        std::pair<Rarity, std::string>(UNCOMMON, "Slotting I"),
        std::pair<Rarity, std::string>(RARE, "Energy Steal"),
        std::pair<Rarity, std::string>(RARE, "Slotting II"),
        std::pair<Rarity, std::string>(RARE, "Barrier Piercing"),
        std::pair<Rarity, std::string>(VERY_RARE, "Severance"),
        std::pair<Rarity, std::string>(VERY_RARE, "Soul Eater"),
        std::pair<Rarity, std::string>(VERY_RARE, "Slotting III")
    };

    inline std::vector<std::pair<Rarity, std::string> > armorEngravings = {
        std::pair<Rarity, std::string>(COMMON, "Sturdy"),
        std::pair<Rarity, std::string>(UNCOMMON, "Elemental Boost I"),
        std::pair<Rarity, std::string>(UNCOMMON, "Elemental Resistance I"),
        std::pair<Rarity, std::string>(VERY_RARE, "Elemental Boost II"),
        std::pair<Rarity, std::string>(VERY_RARE, "Elemental Resistance II")
    };

    inline std::vector<std::pair<Rarity, std::string> > helmetEngravings = {
        std::pair<Rarity, std::string>(COMMON, "Sturdy"),
        std::pair<Rarity, std::string>(UNCOMMON, "Breathing Support"),
        std::pair<Rarity, std::string>(UNCOMMON, "Elemental Boost I"),
        std::pair<Rarity, std::string>(UNCOMMON, "Elemental Resistance I"),
        std::pair<Rarity, std::string>(VERY_RARE, "Elemental Boost II"),
        std::pair<Rarity, std::string>(VERY_RARE, "Elemental Resistance II")
    };

    inline std::vector<std::pair<Rarity, int>> uniqueChances = {
        std::pair<Rarity, int>(COMMON, 50),
        std::pair<Rarity, int>(UNCOMMON, 30),
        std::pair<Rarity, int>(RARE, 15),
        std::pair<Rarity, int>(VERY_RARE, 5)
    };

    inline std::vector<std::pair<Rarity, int>> legendaryChances = {
        std::pair<Rarity, int>(UNCOMMON, 40),
        std::pair<Rarity, int>(RARE, 40),
        std::pair<Rarity, int>(VERY_RARE, 20)
    };

    inline std::vector<std::pair<Rarity, int>> godChances = {
        std::pair<Rarity, int>(RARE, 60),
        std::pair<Rarity, int>(VERY_RARE, 40)
    };
}
