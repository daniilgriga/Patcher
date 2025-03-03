#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode(740, 600), "SFML App");

    // ========================= MUSIC ========================= //
    sf::Music music;
    if (!music.openFromFile("Mobil edit (Keygen music).mp3"))
    {
        std::cerr << "Load music ERROR\n";
        return 1;
    }

    music.setLoop(true);
    music.play();

    // ========================= FONT ========================== //
    sf::Font font;
    if (!font.loadFromFile("Astakhov Flacon.otf"))
    {
        std::cerr << "Load font ERROR\n";
        return 1;
    }

    // ======================= ANIMATION ======================= //
    std::vector<sf::Texture> frames;
    for (int i = 1; i <= 16; ++i)
    {
        sf::Texture frame;
        std::string filename = "images/pic" + std::to_string(i) + ".png";
        if (!frame.loadFromFile(filename))
        {
            std::cerr << "Load pictures ERROR " << filename << "\n";
            return 1;
        }
        frames.push_back(frame);
    }

    sf::Sprite display;
    display.setTexture(frames[0]);
    display.setPosition(0.f, 0.f);
    float frameTime = 0.2f;              // velocity of animation (per second)
    float currentTime = 0.f;
    unsigned int currentFrame = 0;

    // ========================================================= //
    sf::Texture customImageTexture;
    if (!customImageTexture.loadFromFile("images/background.jpg"))
    {
        std::cerr << "Load pictures ERROR\n";
        return 1;
    }

    sf::Sprite customImageSprite;
    customImageSprite.setTexture(customImageTexture);
    customImageSprite.setPosition(0.f, 350.f);
    customImageSprite.setScale(740.f / customImageTexture.getSize().x, 250.f / customImageTexture.getSize().y);  // Подгоняем под 400x100

    // ========================= BUTTONS ======================== //
    //sf::Texture startButtonTexture;
    //if (!startButtonTexture.loadFromFile("butt.jpg"))
    //{
    //    std::cerr << "Load texture for go ERROR\n";
    //    return 1;
    //}

    //sf::Sprite startButton;
    //startButton.setTexture(startButtonTexture);
    //startButton.setPosition(200.f, 400.f);
    sf::RectangleShape startButton(sf::Vector2f(200.f, 50.f));
    startButton.setPosition(210.f, 400.f);
    startButton.setFillColor(sf::Color::Green);

    sf::Text startText;
    startText.setFont(font);
    startText.setString("GO");
    startText.setCharacterSize(24);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(230.f, 410.f);

    // ========================================================== //
    sf::RectangleShape exitButton(sf::Vector2f(200.f, 50.f));
    exitButton.setPosition(450.f, 400.f);
    exitButton.setFillColor(sf::Color::Red);

    sf::Text exitText;
    exitText.setFont(font);
    exitText.setString("OUT");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::Black);
    exitText.setPosition(490.f, 410.f);

    sf::Clock clock;

    // MAIN
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    std::cout << "program is starting...\n";
                    system("build/test CRACK.COM rules.txt cracked.com");
                }

                if (exitButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                {
                    std::cout << "Exit\n";
                    window.close();
                }
            }
        }

        // animation update
        float deltaTime = clock.restart().asSeconds();
        currentTime += deltaTime;
        if (currentTime >= frameTime)
        {
            currentTime = 0.f;
            currentFrame = (currentFrame + 1) % frames.size();
            display.setTexture(frames[currentFrame]);
        }

        // rendering
        window.clear(sf::Color::Black);
        window.draw(customImageSprite);
        window.draw(display);
        window.draw(startButton);
        window.draw(startText);
        window.draw(exitButton);
        window.draw(exitText);
        window.display();
    }

    return 0;
}
