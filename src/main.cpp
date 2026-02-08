#include "Game.hpp"
#include <iostream>

int main() {
    std::cout << "==================================" << std::endl;
    std::cout << "  MUTANT FACILITY - Survival Game" << std::endl;
    std::cout << "==================================" << std::endl;
    std::cout << std::endl;
    
    try {
        Game game;
        game.Initialize();
        game.Run();
        game.Shutdown();
    }
    catch (const std::exception& e) {
        std::cerr << "Erro fatal: " << e.what() << std::endl;
        return 1;
    }
    
    std::cout << "Jogo encerrado com sucesso!" << std::endl;
    return 0;
}