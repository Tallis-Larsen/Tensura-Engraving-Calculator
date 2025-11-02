#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <config.hpp>

class UI {
public:
    UI() = delete;

    static void start(const std::function<void()> &calculateCallback);

    inline static bool isEngraved = true;
    inline static int selectedTab;
    inline static int selectedTier;
    inline static std::deque<bool> selectedWeaponEngravings = std::deque<bool>(Config::weaponEngravings.size(), false);
    inline static std::deque<bool> selectedArmorEngravings = std::deque<bool>(Config::armorEngravings.size(), false);
    inline static std::deque<bool> selectedHelmetEngravings = std::deque<bool>(Config::helmetEngravings.size(), false);

private:
    static ftxui::Component render();
    static ftxui::Component createSeparatorComponent();
    static ftxui::Component createTextComponent(const std::string& text);

    inline static ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    inline static std::vector<ftxui::Component> renderedComponents;
    inline static ftxui::Component title = ftxui::Renderer([] {
        return ftxui::vbox({ftxui::text("Tensura Engraving Calculator") | ftxui::bold | ftxui::center}) | ftxui::border;
    });
    inline static ftxui::Component probabilityHeader = ftxui::Renderer([] {
        return ftxui::vbox({ftxui::text("Probabilities") | ftxui::bold | ftxui::center});
    });
    inline static std::vector<std::string> tabOptions = {"Weapon", "Armor", "Helmet"};
    inline static std::vector<std::string> tierOptions = {"Unique", "Legendary", "God"};
    inline static std::vector<std::string> isEngravedOptions = {"Yes", "No"};
    inline static ftxui::Component tabsMenu;
    inline static ftxui::Component tabs;
    inline static ftxui::Component tiers;
    inline static ftxui::Component isEngravedSelector;
    inline static int selectedIsEngraved;
    inline static std::vector<ftxui::Component> weaponEngravingOptions;
    inline static std::vector<ftxui::Component> armorEngravingOptions;
    inline static std::vector<ftxui::Component> helmetEngravingOptions;
    inline static ftxui::Component weaponEngravings;
    inline static ftxui::Component armorEngravings;
    inline static ftxui::Component helmetEngravings;
    inline static ftxui::Component calculate;
    inline static ftxui::Element probabilities;
};