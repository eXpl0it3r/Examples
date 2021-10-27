#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    if (!sf::SoundBufferRecorder::isAvailable())
    {
        std::cerr << "No recording device available!\n";
        return 1;
    }

    const auto recorders = sf::SoundRecorder::getAvailableDevices();

    for (auto i = std::size_t{ 0 }; i < recorders.size(); ++i)
    {
        std::cout << (i + 1) << "\t" << recorders[i] << "\n";
    }

    auto option = 0U;

    while(option <= 0 || option > recorders.size())
    {
        std::cout << "Pick your recording device: ";
        std::cin >> option;
    }
    std::cin.ignore();

    auto recorder = sf::SoundBufferRecorder{};
    recorder.setDevice(recorders[option - 1]);

    option = 0;

    while(option <= 0 || option > 3)
    {
        std::cout << "Do you want to record Mono (1) or Stereo (2): ";
        std::cin >> option;
    }
    std::cin.ignore();

    recorder.setChannelCount(option);

    std::cout << "Channel count is: " << recorder.getChannelCount() << "\n";

    std::cout << "Press ENTER to start...";
    std::cin.ignore();
    recorder.start();

    std::cout << "Press ENTER to stop...";
    std::cin.ignore();
    recorder.stop();

    std::cout << "Recording stopped!\n";

    const auto buffer = recorder.getBuffer();

    std::cout << "Recording properties:\n";
    std::cout << "\tSample Count:\t" << buffer.getSampleCount() << "\n";
    std::cout << "\tSample Rate:\t" << buffer.getSampleRate() << "\n";
    std::cout << "\tChannel Count:\t" << buffer.getChannelCount() << "\n";
    std::cout << "\tDuration:\t" << buffer.getDuration().asSeconds() << "s\n";

    auto sound = sf::Sound{ buffer };
    sound.play();

    std::cout << "Playing it back...\n";

    while(sound.getStatus() == sf::Sound::Playing)
    {
        sf::sleep(sf::seconds(0.5f));
    }

    auto choice = char{ 0 };

    while(choice != 'y' && choice != 'Y' && choice != 'n' && choice != 'N')
    {
        std::cout << "Do you want to save it to file (y/n): ";
        std::cin >> choice;
    }
    std::cin.ignore();

    if(choice == 'y' || choice == 'Y')
    {
        if (!buffer.saveToFile("buffer.wav"))
        {
            std::cout << "Failed to save audio to buffer.wav\n";
        }
    }

    std::cout << "Goodbye!\n";
    std::cout << "Press ENTER to exit...";
    std::cin.ignore();
}
