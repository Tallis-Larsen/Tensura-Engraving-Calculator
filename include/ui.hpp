#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <config.hpp>

class UI {
public:
    UI() = delete;
    static void start(const std::function<void()> &calculateCallback);
    inline static int selectedTab;
    inline static int selectedTier;
    inline static int selectedIsEngraved;
    inline static std::deque<bool> selectedWeaponEngravings;
    inline static std::deque<bool> selectedArmorEngravings;
    inline static std::deque<bool> selectedHelmetEngravings;

private:
    static ftxui::Component render();

    inline static ftxui::ScreenInteractive screen = ftxui::ScreenInteractive::Fullscreen();
    inline static std::vector<ftxui::Component> renderedComponents;
    inline static ftxui::Element title;
    inline static ftxui::Element subTitle;
    inline static ftxui::Element probabilities;
    inline static ftxui::Component tabs;
    inline static std::vector<std::string> tabOptions;
    inline static ftxui::Component tiers;
    inline static std::vector<std::string> tierOptions;
    inline static ftxui::Component isEngraved;
    inline static std::vector<std::string> isEngravedOptions;
    inline static std::vector<ftxui::Component> weaponEngravingOptions;
    inline static std::vector<ftxui::Component> armorEngravingOptions;
    inline static std::vector<ftxui::Component> helmetEngravingOptions;
    inline static ftxui::Component weaponEngravings;
    inline static ftxui::Component armorEngravings;
    inline static ftxui::Component helmetEngravings;
    inline static ftxui::Component calculate;
};