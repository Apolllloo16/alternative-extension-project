#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Load the sprite sheet texture
    sf::Texture spriteSheet;
    if (!spriteSheet.loadFromFile("your_spritesheet.png")) {
        std::cerr << "Failed to load sprite sheet!" << std::endl;
        return 1;
    }

    // Set the dimensions of each individual sprite in the sprite sheet
    const int spriteWidth = spriteSheet.getSize().x / 5; // 5 columns
    const int spriteHeight = spriteSheet.getSize().y / 4; // 4 rows

    // Create 20 different textures using the sprite sheet
    std::vector<sf::Texture> textures;
    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 5; ++col) {
            sf::IntRect textureRect(col * spriteWidth, row * spriteHeight, spriteWidth, spriteHeight);
            sf::Texture texture;
            texture.loadFromImage(spriteSheet.copyToImage(), textureRect);
            textures.push_back(texture);
        }
    }

    // Example: Use the first texture to create a sprite
    sf::Sprite sprite;
    sprite.setTexture(textures[0]);

    // Now you can use 'sprite' to render the first texture

    // ... (Use other textures in a similar way)

    // Run the SFML window loop
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Sprite Sheet Example");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(sprite); // Draw the sprite with the first texture
        window.display();
    }

    return 0;
}
