#include <garnish_app.hpp>

int main() {
    garnish::App::CreateInfo createInfo{ };
    createInfo.assetPath = "../3rdParty/GarnishEngine/";
    garnish::App app{ createInfo };

    app.run();
}