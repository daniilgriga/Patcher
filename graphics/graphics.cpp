#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

int main ()
{
    sf::RenderWindow window (sf::VideoMode (500, 700), "Patcher GRD");

    window.setActive (true);
    window.requestFocus ();
    window.setMouseCursorGrabbed (true);

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

    sf::RectangleShape textField (sf::Vector2f (492.f, 50.f));
    textField.setPosition (4, 571);
    textField.setFillColor (sf::Color::Black);
    textField.setOutlineThickness (2);
    textField.setOutlineColor (sf::Color(255, 255, 214));

    sf::Text inputText;
    inputText.setFont (font);
    inputText.setCharacterSize (20);
    inputText.setFillColor (sf::Color(255, 255, 214));
    inputText.setPosition ( textField.getPosition ().x + 5,
                            textField.getPosition ().y + (textField.getSize ().y - inputText.getGlobalBounds ().height) / 2 - 8);

    std::string text = "";
    const int maxLength = 20;

    sf::Text placeholderText;
    placeholderText.setFont (font);
    placeholderText.setString ("Enter the password...");
    placeholderText.setCharacterSize (20);
    placeholderText.setFillColor (sf::Color(128, 128, 128));
    placeholderText.setPosition ( textField.getPosition ().x + 5,
                                  textField.getPosition ().y + (textField.getSize ().y - placeholderText.getGlobalBounds ().height) / 2 );

    sf::RectangleShape cursor (sf::Vector2f (2, 20));
    cursor.setFillColor (sf::Color::White);
    cursor.setPosition (inputText.getPosition ().x, inputText.getPosition ().y + 2);
    bool showCursor = true;
    bool isActive   = false;
    sf::Clock cursorClock;

    // ========================= MESSAGE ======================== //

    sf::RectangleShape message(sf::Vector2f(494, 80));
    message.setFillColor(sf::Color(50, 50, 50)); // Тёмный фон
    message.setOutlineThickness(2);
    message.setOutlineColor(sf::Color(255, 255, 214));
    message.setPosition(3, 300);

    sf::Text messageText;
    messageText.setFont (font);
    messageText.setString ("For hacking, enter the password!");
    messageText.setCharacterSize (22);
    messageText.setFillColor (sf::Color(255, 255, 214));
    messageText.setPosition ( message.getPosition ().x + (message.getSize ().x - messageText.getGlobalBounds ().width)  / 2,
                              message.getPosition ().y + (message.getSize ().y - messageText.getGlobalBounds ().height) / 2 );

    bool showMessage = false;
    sf::Clock messageTimer;

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

            if (isActive && event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    if (event.text.unicode == 8 && !text.empty ()) // 8 = backspace
                        text.pop_back ();

                    else if (event.text.unicode != 8 && text.length () < 25) // need const
                        text += static_cast<char> (event.text.unicode);

                    inputText.setString (text);

                    cursor.setPosition ( inputText.getPosition ().x + inputText.getGlobalBounds ().width + 2,
                                        inputText.getPosition ().y + 2 );
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

                sf::FloatRect fieldBounds = textField.getGlobalBounds ();
                isActive = fieldBounds.contains(static_cast<float> (mousePos.x), static_cast<float> (mousePos.y));

                if (startButton.getGlobalBounds ().contains (mousePos.x, mousePos.y))
                {
                    if (!text.empty ())
                    {
                        std::cout << "Program is hacking...\n";
                        system ("../build/test ../programs/CRACK.COM ../programs/rules.txt ../programs/cracked.com");
                    }
                    else
                    {
                        showMessage = true;
                        messageTimer.restart ();
                    }
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

        if (isActive && cursorClock.getElapsedTime ().asSeconds () > 0.5f)
        {
            showCursor = !showCursor;
            cursorClock.restart ();
        }

        if (showMessage && messageTimer.getElapsedTime().asSeconds() > 3.0f)
            showMessage = false;

        // rendering
        window.clear (sf::Color::Black);
        window.draw (display);
        window.draw (startButton);
        window.draw (startText);
        window.draw (exitButton);
        window.draw (exitText);
        window.draw (textField);

        if (text.empty ())
            window.draw (placeholderText);
        window.draw (inputText);

        if (isActive && showCursor)
            window.draw (cursor);

        if (showMessage)
        {
            window.draw(message);
            window.draw(messageText);
        }

        window.display ();
    }

    return 0;
}
