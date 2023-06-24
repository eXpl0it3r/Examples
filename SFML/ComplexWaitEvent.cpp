#include <mutex>
#include <string>
#include <thread>
#include <queue>

#include <SFML/Graphics.hpp>

class Application
{
    sf::RenderWindow m_window;
    std::queue<sf::Event> m_eventQueue;
    std::mutex m_sharedAccess;

    void renderGame()
    {
        // Set OpenGL Context active on the current thread
        m_window.setActive(true);

        auto rectangle = sf::RectangleShape{{100.f, 100.f}};
        rectangle.setFillColor(sf::Color::Red);
        rectangle.setPosition({200.f, 200.f});

        auto clock = sf::Clock{};
        auto accumulator = sf::Time::Zero;

        while (m_window.isOpen())
        {
            {
                auto lock = std::unique_lock<std::mutex>{m_sharedAccess};
                while (!m_eventQueue.empty())
                {
                    auto event = sf::Event{};
                    event = m_eventQueue.back();
                    m_eventQueue.pop();

                    if (event.type == sf::Event::Closed)
                    {
                        m_window.close();
                    }
                }
            }

            if (rectangle.getFillColor() == sf::Color::Red)
            {
                rectangle.setFillColor(sf::Color::Green);
            }
            else
            {
                rectangle.setFillColor(sf::Color::Red);
            }

            auto frameTime = clock.restart();
            accumulator += frameTime;

            if (accumulator >= sf::seconds(1.f))
            {
                m_window.setTitle(std::to_string(1.f / frameTime.asSeconds()));
                accumulator = sf::Time::Zero;
            }

            m_window.clear();
            m_window.draw(rectangle);
            m_window.display();
        }
    }

public:
    Application() : m_window{{1920u, 1080u}, "Complex WaitEvent"}
    {
        m_window.setFramerateLimit(144);
    }

    void run()
    {
        // Set OpenGL Context inactive on the current thread
        m_window.setActive(false);

        auto renderThread = std::thread{&Application::renderGame, this};

        // Handle events on the same thread the window was created on
        auto event = sf::Event{};
        while (m_window.waitEvent(event))
        {
            {
                auto lock = std::unique_lock<std::mutex>{m_sharedAccess};
                m_eventQueue.push(event);
            }

            if (event.type == sf::Event::Closed)
            {
                break;
            }
        }

        renderThread.join();
    }
};

int main()
{
    auto app = Application{};
    app.run();
}