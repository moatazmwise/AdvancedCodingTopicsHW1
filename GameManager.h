#include <string>

class GameManager {
public:
    GameManager();
    bool loadGameBoard(const std::string& filePath);
    void initializePlayers();
    void runGameLoop(); 
};
