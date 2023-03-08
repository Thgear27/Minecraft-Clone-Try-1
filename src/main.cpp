#include "Game.hpp"

void app() {
    Game game;
    while (game.isRuning()) {
        game.update();
        game.handleEvents();
        game.renderAll();
    }
}

int main() {
    try {
        app();
    } catch (std::exception const& e) {
        std::cout << "[ERROR]: " << e.what() << '\n';
    }
}

