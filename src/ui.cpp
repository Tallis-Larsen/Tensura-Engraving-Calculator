#include <ui.h>

using namespace ftxui;

void som() {
    auto document = vbox({
        text("Hello World"),
        text("This is a TUI")
    });

    auto screen = ScreenInteractive::FitComponent();
    // YAAAAAY LAMBDAS I HATE THEM RAAAAAh
    screen.Loop(Renderer([&]{ return center(border(document)); }));
}