#include <ui.hpp>

using namespace ftxui;

void UI::start(const std::function<void()> &calculateCallback) {
    title = text("Tensura Engraving Calculator") | bold | center;
    subTitle = text("Probabilities");
    tabOptions = {"Weapon", "Armor", "Armor (Helmet)"};
    tabs = Menu(&tabOptions, &selectedTab, MenuOption::Horizontal());
    tierOptions = {"Unique", "Legendary", "God"};
    tiers = Toggle(&tierOptions, &selectedTier);
    isEngravedOptions = {"Yes", "No"};
    isEngraved = Toggle(&isEngravedOptions, &selectedIsEngraved);

    selectedWeaponEngravings = std::deque<bool>(Config::weaponEngravings.size(), false);
    selectedArmorEngravings = std::deque<bool>(Config::armorEngravings.size(), false);
    selectedHelmetEngravings = std::deque<bool>(Config::helmetEngravings.size(), false);
    for (int i = 0; i < Config::weaponEngravings.size(); i++) {
        weaponEngravingOptions.push_back(Checkbox(Config::weaponEngravings[i].second, &selectedWeaponEngravings[i]));
    }
    for (int i = 0; i < Config::armorEngravings.size(); i++) {
        armorEngravingOptions.push_back(Checkbox(Config::armorEngravings[i].second, &selectedArmorEngravings[i]));
    }
    for (int i = 0; i < Config::helmetEngravings.size(); i++) {
        helmetEngravingOptions.push_back(Checkbox(Config::helmetEngravings[i].second, &selectedHelmetEngravings[i]));
    }
    weaponEngravings = Container::Vertical(weaponEngravingOptions);
    armorEngravings = Container::Vertical(armorEngravingOptions);
    helmetEngravings = Container::Vertical(helmetEngravingOptions);

    const std::string calculateLabel = "Calculate";
    calculate = Button(&calculateLabel, calculateCallback);

    screen.Loop(render());
}

Component UI::render() {
    renderedComponents.push_back(Renderer([] {
        return vbox({ title }) | border;
    }));
    return Container::Vertical(renderedComponents);
}
