#include <ui.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <map>

using namespace ftxui;
using namespace std;

void UI::start(const std::function<void()> &calculateCallback) {
    // Create a shared menu option with custom styling
    auto sharedMenuOption = MenuOption::Horizontal();
    sharedMenuOption.entries_option.transform = [](const EntryState& state) {
        Element e = text(state.label);
        if (state.active) {
            e = e | bold | color(Color::Gold1);
        } else {
            e = e | bold | dim;
        }
        return e;
    };

    // Create a shared checkbox option with custom styling
    auto sharedCheckboxOption = CheckboxOption();
    sharedCheckboxOption.transform = [](const EntryState& state) {
        Element e = text((state.state ? "[X] " : "[ ] ") + state.label);
        if (state.state) {
            e = e | color(Color::Green);
        }
        return e;
    };

    tiers = Container::Horizontal({
        createTextComponent("[Next Tier] - ") | bold | color(Color::Blue),
        Menu(&tierOptions, &selectedTier, sharedMenuOption)
    }) | center;

    isEngravedSelector = Container::Horizontal({
        createTextComponent("[Has Engravings] - ") | bold | color(Color::Blue),
        Menu(&isEngravedOptions, &selectedIsEngraved, sharedMenuOption) | CatchEvent([&](const Event&) {
            isEngraved = selectedIsEngraved == 0;
            return false;
        })
    }) | center;

    tabsMenu = Container::Horizontal({
        createTextComponent("[Gear Type] - ") | bold | color(Color::Blue),
        Menu(&tabOptions, &selectedTab, sharedMenuOption)
    }) | center;

    Rarity lastRarity = COMMON;
    weaponEngravingOptions.push_back(createTextComponent("[COMMON]") | color(Color::Red));
    for (int i = 0; i < Config::weaponEngravings.size(); i++) {
        if (Config::weaponEngravings[i].rarity == lastRarity) {
            weaponEngravingOptions.push_back(Checkbox(Config::weaponEngravings[i].name + " " + toRomanNumeral(Config::weaponEngravings[i]), &selectedWeaponEngravings[i], sharedCheckboxOption));
        } else {
            weaponEngravingOptions.push_back(createTextComponent("[" + rarityToString(Config::weaponEngravings[i].rarity) + "]") | color(Color::Red));
            lastRarity = Config::weaponEngravings[i].rarity;
            i--;
        }
    }
    lastRarity = COMMON;
    armorEngravingOptions.push_back(createTextComponent("[COMMON]") | color(Color::Red));
    for (int i = 0; i < Config::armorEngravings.size(); i++) {
        if (Config::armorEngravings[i].rarity == lastRarity) {
            armorEngravingOptions.push_back(Checkbox(Config::armorEngravings[i].name + " " + toRomanNumeral(Config::armorEngravings[i]), &selectedArmorEngravings[i], sharedCheckboxOption));
        } else {
            armorEngravingOptions.push_back(createTextComponent("[" + rarityToString(Config::armorEngravings[i].rarity) + "]") | color(Color::Red));
            lastRarity = Config::armorEngravings[i].rarity;
            i--;
        }
    }
    lastRarity = COMMON;
    helmetEngravingOptions.push_back(createTextComponent("[COMMON]") | color(Color::Red));
    for (int i = 0; i < Config::helmetEngravings.size(); i++) {
        if (Config::helmetEngravings[i].rarity == lastRarity) {
            helmetEngravingOptions.push_back(Checkbox(Config::helmetEngravings[i].name + " " + toRomanNumeral(Config::helmetEngravings[i]), &selectedHelmetEngravings[i], sharedCheckboxOption));
        } else {
            helmetEngravingOptions.push_back(createTextComponent("[" + rarityToString(Config::helmetEngravings[i].rarity) + "]") | color(Color::Red));
            lastRarity = Config::helmetEngravings[i].rarity;
            i--;
        }
    }
    weaponEngravings = Container::Vertical(weaponEngravingOptions);
    armorEngravings = Container::Vertical(armorEngravingOptions);
    helmetEngravings = Container::Vertical(helmetEngravingOptions);

    tabs = Maybe(Container::Tab({weaponEngravings, armorEngravings, helmetEngravings}, &selectedTab) | bold | center, &isEngraved);

    calculate = Button("Calculate", calculateCallback) | bold | color(Color::Blue) | center;

    engravingProbabilities = Container::Vertical({createTextComponent("")});

    screen.Loop(render());
}

void UI::updateProbabilities(const std::vector<std::pair<Engraving, float>>& newEngravingProbabilities, float noEngravingChance) {
    // Helper function to format percentage with 2 decimal places
    auto formatPercent = [](float value) {
        stringstream ss;
        ss << fixed << setprecision(2) << (value * 100);
        return ss.str() + "%";
    };

    vector<Component> engravingProbabilityComponents;

    // Calculate rarity totals by summing engraving probabilities
    map<Rarity, float> rarityTotals;
    for (const auto& [engraving, probability] : newEngravingProbabilities) {
        rarityTotals[engraving.rarity] += probability;
    }

    // Process engravings grouped by rarity
    Rarity lastRarity = newEngravingProbabilities[0].first.rarity;
    engravingProbabilityComponents.push_back(createTextComponent("[" + rarityToString(lastRarity) + "] - "
        + formatPercent(rarityTotals[lastRarity])
    ) | color(Color::Red));

    for (int i = 0; i < newEngravingProbabilities.size(); i++) {
        if (newEngravingProbabilities[i].first.rarity == lastRarity) {
            engravingProbabilityComponents.push_back(createTextComponent(newEngravingProbabilities[i].first.name
                + toRomanNumeral(newEngravingProbabilities[i].first)
                + " - " + formatPercent(newEngravingProbabilities[i].second)));
        } else {
            // New rarity encountered
            lastRarity = newEngravingProbabilities[i].first.rarity;

            engravingProbabilityComponents.push_back(createTextComponent("[" + rarityToString(lastRarity) + "] - "
                + formatPercent(rarityTotals[lastRarity])
            ) | color(Color::Red));
            i--;
        }
    }

    engravingProbabilityComponents.push_back(createTextComponent("[NO ENGRAVING] - " + formatPercent(noEngravingChance)) | color(Color::Red));

    engravingProbabilities = Container::Vertical(engravingProbabilityComponents) | bold | center;

}

Component UI::render() {
    renderedComponents.push_back(title);

    // Create a dynamic wrapper that always renders the current engravingProbabilities
    auto dynamicProbabilities = Renderer([&] {
        return engravingProbabilities->Render();
    });

    renderedComponents.push_back(Container::Horizontal({
        Container::Vertical({tabsMenu, createSeparatorComponent(), tiers, createSeparatorComponent(), isEngravedSelector, createSeparatorComponent(), tabs, createSeparatorComponent(), calculate}) | border | flex,
        Container::Vertical({probabilityHeader, createSeparatorComponent(), dynamicProbabilities}) | border | flex
    }));
    return Container::Vertical(renderedComponents);
}

Component UI::createSeparatorComponent() {
    return Renderer([] { return separator(); });
}

Component UI::createTextComponent(const std::string& text) {
    return Renderer([=] {
        return vbox({ftxui::text(text)});
    });
}

string UI::toRomanNumeral(Engraving engraving) {
    int number = engraving.level;
    if (engraving.maxLevel != 1) {
        if (number == 1) {
            return " I";
        } if (number == 2) {
            return " II";
        } if (number == 3) {
            return " III";
        } if (number == 4) {
            return " IV";
        } if (number == 5) {
            return " V";
        }
        return "ERROR: Bad number value";
    }
    return "";
}