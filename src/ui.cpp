#include <ui.hpp>

using namespace ftxui;

void UI::start(const std::function<void()> &calculateCallback) {
    tiers = Container::Horizontal({
        createTextComponent("[Next Tier] - ") | bold,
        Toggle(&tierOptions, &selectedTier) | bold
    }) | center;
    isEngravedSelector = Container::Horizontal({
        createTextComponent("[Has Engravings] - ") | bold,
        Toggle(&isEngravedOptions, &selectedIsEngraved) | CatchEvent([&](const Event&) {
            isEngraved = selectedIsEngraved == 0;
            return false;
        })| bold
    }) | center;
    tabsMenu = Container::Horizontal({
        createTextComponent("[Gear Type] - ") | bold,
        Menu(&tabOptions, &selectedTab, MenuOption::Horizontal()) | bold
    }) | center;

    Rarity lastRarity = COMMON;
    weaponEngravingOptions.push_back(createTextComponent("[COMMON]"));
    for (int i = 0; i < Config::weaponEngravings.size(); i++) {
        if (Config::weaponEngravings[i].first == lastRarity) {
            weaponEngravingOptions.push_back(Checkbox(Config::weaponEngravings[i].second, &selectedWeaponEngravings[i]));
        } else {
            weaponEngravingOptions.push_back(createTextComponent("[" + rarityToString(Config::weaponEngravings[i].first) + "]"));
            lastRarity = Config::weaponEngravings[i].first;
            i--;
        }
    }
    lastRarity = COMMON;
    armorEngravingOptions.push_back(createTextComponent("[COMMON]"));
    for (int i = 0; i < Config::armorEngravings.size(); i++) {
        if (Config::armorEngravings[i].first == lastRarity) {
            armorEngravingOptions.push_back(Checkbox(Config::armorEngravings[i].second, &selectedArmorEngravings[i]));
        } else {
            armorEngravingOptions.push_back(createTextComponent("[" + rarityToString(Config::armorEngravings[i].first) + "]"));
            lastRarity = Config::armorEngravings[i].first;
            i--;
        }
    }
    lastRarity = COMMON;
    helmetEngravingOptions.push_back(createTextComponent("[COMMON]"));
    for (int i = 0; i < Config::helmetEngravings.size(); i++) {
        if (Config::helmetEngravings[i].first == lastRarity) {
            helmetEngravingOptions.push_back(Checkbox(Config::helmetEngravings[i].second, &selectedHelmetEngravings[i]));
        } else {
            helmetEngravingOptions.push_back(createTextComponent("[" + rarityToString(Config::helmetEngravings[i].first) + "]"));
            lastRarity = Config::helmetEngravings[i].first;
            i--;
        }
    }
    weaponEngravings = Container::Vertical(weaponEngravingOptions);
    armorEngravings = Container::Vertical(armorEngravingOptions);
    helmetEngravings = Container::Vertical(helmetEngravingOptions);

    tabs = Maybe(Container::Tab({weaponEngravings, armorEngravings, helmetEngravings}, &selectedTab) | bold | center, &isEngraved);

    calculate = Button("Calculate", calculateCallback) | bold | center;

    screen.Loop(render());
}

Component UI::render() {
    renderedComponents.push_back(title);
    renderedComponents.push_back(Container::Horizontal({
        Container::Vertical({tabsMenu, createSeparatorComponent(), tiers, createSeparatorComponent(), isEngravedSelector, createSeparatorComponent(), tabs, createSeparatorComponent(), calculate}) | border | flex,
        Container::Vertical({probabilityHeader, createSeparatorComponent()}) | border | flex
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