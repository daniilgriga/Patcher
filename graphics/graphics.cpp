#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

int main ()
{
    sf::RenderWindow window (sf::VideoMode (500, 700), "Patcher GRD");

    window.setActive(true);
    window.requestFocus();
    window.setMouseCursorGrabbed(true);

    // ========================= MUSIC ========================= //
    sf::Music music;
    if (!music.openFromFile (".Platina.mp3"))
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

    sf::Sprite display;
    display.setTexture (frames[0]);
    float frameTime = 0.05f;              // velocity of animation (per second)
    float currentTime = 0.f;
    unsigned int currentFrame = 0;
    // ======================== TEXTFIELD ======================= //

    sf::RectangleShape textField (sf::Vector2f (300, 50));
    textField.setPosition (4, 571);
    textField.setFillColor (sf::Color::Black);
    textField.setOutlineThickness (2);
    textField.setOutlineColor (sf::Color(255, 255, 214));

    sf::Text inputText;
    inputText.setFont (font);
    inputText.setCharacterSize (20);
    inputText.setFillColor (sf::Color(255, 255, 214));
    inputText.setPosition ( textField.getPosition ().x + 5,
                            textField.getPosition ().y + (textField.getSize ().y - inputText.getGlobalBounds ().height) / 2 );

    std::string text = "";
    const int maxLength = 20;

    // ========================= BUTTONS ======================== //
    sf::RectangleShape startButton (sf::Vector2f (492.f, 50.f));
    startButton.setPosition (4.f, 500.f);
    startButton.setFillColor (sf::Color::Black);
    startButton.setOutlineThickness (2);
    startButton.setOutlineColor (sf::Color(255, 255, 214));

    sf::Text startText;
    startText.setFont (font);
    startText.setString ("Hack");
    startText.setCharacterSize (20);
    startText.setFillColor (sf::Color(255, 255, 214));
    startText.setPosition ( startButton.getPosition ().x + (startButton.getSize ().x - startText.getGlobalBounds ().width)  / 2,
                            startButton.getPosition ().y + (startButton.getSize ().y - startText.getGlobalBounds ().height) / 2 - 3 );

    bool IsHoveredexit = false;

    sf::RectangleShape exitButton (sf::Vector2f (492.f, 50.f));
    exitButton.setPosition (4.f, 646.f);
    exitButton.setFillColor (sf::Color::Black);
    exitButton.setOutlineThickness (2);
    exitButton.setOutlineColor (sf::Color(255, 255, 214));

    sf::Text exitText;
    exitText.setFont (font);
    exitText.setString ("Exit");
    exitText.setCharacterSize (20);
    exitText.setFillColor (sf::Color(255, 255, 214));
    exitText.setPosition ( exitButton.getPosition ().x + (exitButton.getSize ().x - exitText.getGlobalBounds ().width)  / 2,
                           exitButton.getPosition ().y + (exitButton.getSize ().y - exitText.getGlobalBounds ().height) / 2 - 3 );

    bool IsHoveredstart = false;
    // ========================================================== //
    sf::Clock clock;

    // MAIN
    while (window.isOpen ())
    {
        sf::Event event;
        while (window.pollEvent (event))
        {
            if (event.type == sf::Event::Closed)
                window.close ();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == 8 && !text.empty ())
                        text.pop_back ();

                    else if (event.text.unicode != 8 && text.length () < 15) // need const
                        text += static_cast<char>(event.text.unicode);

                    inputText.setString (text);
                }
            }

            if (event.type == sf::Event::MouseMoved)
            {
                sf::Vector2i MousePos = sf::Mouse::getPosition (window);
                sf::FloatRect ButtonBoundsStart = startButton.getGlobalBounds ();
                sf::FloatRect ButtonBoundsExit  =  exitButton.getGlobalBounds ();

                IsHoveredstart = ButtonBoundsStart.contains (MousePos.x, MousePos.y);
                IsHoveredexit  = ButtonBoundsExit.contains (MousePos.x, MousePos.y);

                startButton.setFillColor (IsHoveredstart ? sf::Color(50, 50, 50) : sf::Color::Black);
                 exitButton.setFillColor (IsHoveredexit  ? sf::Color(50, 50, 50) : sf::Color::Black);
            }

            //if (event.type == sf::Event::GainedFocus)
            //    std::cout << "window get focus" << std::endl;
            //if (event.type == sf::Event::LostFocus)
            //    std::cout << "window lost focus" << std::endl;

            //if (event.type == sf::Event::MouseMoved)
            //{
            //    sf::Vector2i mousePos = sf::Mouse::getPosition (window);
            //    std::cout << "MOUSE: " << mousePos.x << ", " << mousePos.y << std::endl;
            //}

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
        window.draw (display);
        window.draw (startButton);
        window.draw (startText);
        window.draw (exitButton);
        window.draw (exitText);
        window.draw (textField);
        window.draw (inputText);
        window.display ();
    }

    return 0;
}
