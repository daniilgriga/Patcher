#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

int main ()
{
    sf::RenderWindow window (sf::VideoMode (500, 800), "Patcher GRD");

    window.setActive(true);
    window.requestFocus();
    window.setMouseCursorGrabbed(true);

    // ========================= MUSIC ========================= //
    sf::Music music;
    if (!music.openFromFile (".mp3"))
    {
        std::cerr << "Load music ERROR\n";
        //return 1;
    }

    music.setLoop (true);
    music.play ();

    // ========================= FONT ========================== //
    sf::Font font;
    if (!font.loadFromFile ("arial_b.ttf"))
    {
        std::cerr << "Load font ERROR\n";
        return 1;
    }

    // ======================= ANIMATION ======================= //
    std::vector<sf::Texture> frames; // container (dynamic array)
    for (int i = 1; i < 150; ++i)
    {
        sf::Texture frame;
        std::string filename = "images/frames/" + std::to_string (i) + ".gif";
        if (!frame.loadFromFile (filename))
        {
            std::cerr << "Load pictures ERROR " << filename << "\n";
            return 1;
        }
        frames.push_back (frame);
    }
//     sf::Texture texture;
//     if (!texture.loadFromFile ("images/spritesheet.png"))
//     {
//         std::cerr << "Load spritesheet ERROR\n";
//         return 1;
//     }
//
//     sf::Sprite sprite;
//     sprite.setTexture (texture);
//     sprite.setTextureRect (sf::IntRect (0, 0, 888, 500));
//
//     float frameTime = 0.1f;
//     float currentTime = 0.f;
//     unsigned int currentFrame = 0;


    sf::Sprite display;
    display.setTexture (frames[0]);
    float frameTime = 0.05f;              // velocity of animation (per second)
    float currentTime = 0.f;
    unsigned int currentFrame = 0;

    // ========================================================= //
//     sf::Texture customImageTexture;
//     if (!customImageTexture.loadFromFile ("images/background.jpg"))
//     {
//         std::cerr << "Load pictures ERROR\n";
//         return 1;
//     }
//
//     sf::Sprite customImageSprite;
//     customImageSprite.setTexture (customImageTexture);
//     customImageSprite.setPosition (0.f, 350.f);
//     customImageSprite.setScale (740.f / customImageTexture.getSize ().x, 250.f / customImageTexture.getSize ().y);



    // ========================= BUTTONS ======================== //
    //sf::Texture startButtonTexture;
    //if (!startButtonTexture.loadFromFile ("butt.jpg"))
    //{
    //    std::cerr << "Load texture for go ERROR\n";
    //    return 1;
    //}

    //sf::Sprite startButton;
    //startButton.setTexture (startButtonTexture);
    //startButton.setPosition (200.f, 400.f);
    sf::RectangleShape startButton (sf::Vector2f (150.f, 50.f));
    startButton.setPosition (110.f, 410.f);
    startButton.setFillColor (sf::Color::Black);
    startButton.setOutlineThickness (2);
    startButton.setOutlineColor (sf::Color::White);

    sf::Text startText;
    startText.setFont (font);
    startText.setString ("Hack");
    startText.setCharacterSize (20);
    startText.setFillColor (sf::Color::White);
    startText.setPosition ( startButton.getPosition ().x + (startButton.getSize ().x - startText.getGlobalBounds ().width)  / 2,
                            startButton.getPosition ().y + (startButton.getSize ().y - startText.getGlobalBounds ().height) / 2 );

    bool IsHovered = false;
    // ========================================================== //
    sf::RectangleShape exitButton (sf::Vector2f (200.f, 50.f));
    exitButton.setPosition (430.f, 410.f);
    exitButton.setFillColor (sf::Color::White);

    sf::Text exitText;
    exitText.setFont (font);
    exitText.setString ("OUT");
    exitText.setCharacterSize (24);
    exitText.setFillColor (sf::Color::Black);
    exitText.setPosition (495.f, 420.f);

    sf::Clock clock;

    // MAIN
    while (window.isOpen ())
    {
        sf::Event event;
        while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                window.close ();

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i MousePos = sf::Mouse::getPosition (window);
                sf::FloatRect ButtonBounds = startButton.getGlobalBounds ();

                IsHovered = ButtonBounds.contains (MousePos.x, MousePos.y);

                startButton.setFillColor (IsHovered ? sf::Color(50, 50, 50) : sf::Color::Black);
            }

            if (event.type == sf::Event::GainedFocus)
                std::cout << "window get focus" << std::endl;
            if (event.type == sf::Event::LostFocus)
                std::cout << "window lost focus" << std::endl;

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition (window);
                std::cout << "Мышь: " << mousePos.x << ", " << mousePos.y << std::endl;
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition (window);

                if (startButton.getGlobalBounds ().contains (mousePos.x, mousePos.y))
                {
                    std::cout << "program is starting...\n";
                    system ("../build/test ../CRACK.COM ../rules.txt ../cracked.com");
                }

                if (exitButton.getGlobalBounds ().contains (mousePos.x, mousePos.y))
                {
                    std::cout << "Exit\n";
                    window.close ();
                }
            }
        }

        // animation update
        float deltaTime = clock.restart ().asSeconds ();
        currentTime += deltaTime;
        if (currentTime >= frameTime)
        {
            currentTime = 0.f;
            currentFrame = (currentFrame + 1) % frames.size ();
            display.setTexture (frames[currentFrame]);

        }

        // rendering
        window.clear (sf::Color::Black);
        //window.draw (customImageSprite);
        window.draw (display);
        window.draw (startButton);
        window.draw (startText);
        window.draw (exitButton);
        window.draw (exitText);
        window.display ();
    }

    return 0;
}
