#include "global.hpp"
#include "map.hpp"
#include "player.hpp"
#include "collision.hpp"

//TODO 7/11
//texture
//sprites
//rename shit

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOWX,WINDOWY), "invaderz");
    window.setFramerateLimit(144);
    cout << window.getSize().x << ' ' << window.getSize().y;

    //the player
    Player guy;
    sf::Texture gunTexture;
    gunTexture.loadFromFile("Resources/Images/gun_WIP.png");
    sf::Sprite gun(gunTexture);
    gun.setPosition(WINDOWX/2 + 128, WINDOWY - 128);
    sf::Texture crossHairTexture;
    crossHairTexture.loadFromFile("Resources/Images/crosshair.png");
    sf::Sprite crossHair(crossHairTexture);
    crossHair.setOrigin(16.f, 16.f);
    crossHair.setPosition(512.f, 384);
    sf::Font vcrfont;
    if (!vcrfont.loadFromFile("Resources/Fonts/VCR_OSD_MONO_1.001.ttf"))
    {
        cout << "error loading VCR_OSD_MONO_1.001.ttf" << endl;
        return -1;
    }
    sf::Text playerCellText;
    playerCellText.setFont(vcrfont);
    playerCellText.setCharacterSize(21);
    playerCellText.setFillColor(sf::Color::Blue);

    //the map
    char testMap[8][8] =
    {
        {'#','#','#','#','#','#','#','#'},
        {'#','0','0','0','0','0','0','#'},
        {'#','0','0','#','0','0','0','#'},
        {'#','0','0','0','0','0','0','#'},
        {'#','0','0','#','0','0','0','#'},
        {'#','0','0','0','#','#','0','#'},
        {'#','0','0','0','0','0','0','#'},
        {'#','#','#','#','#','#','#','#'}
    };
    Map testLevel;
    testLevel.convertMap(testMap);


    while (window.isOpen())
    {

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        guy.update(testLevel,window);
        playerCellText.setString("x: " + std::to_string((int)(guy.x / CELL_SIZE)) + " y: " + std::to_string((int)(guy.y / CELL_SIZE)));
        

        window.clear();
        //testLevel.drawMap(window);
        //guy.drawMap(window);
        guy.draw3D(window);
        window.draw(playerCellText);
        window.draw(gun);
        window.draw(crossHair);
        window.display();
    }

    return 0;
}