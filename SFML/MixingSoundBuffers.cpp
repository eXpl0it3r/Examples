#include <SFML/Audio.hpp>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int main()
{
    auto buffer1 = sf::SoundBuffer{};
	auto buffer2 = sf::SoundBuffer{};

    if (!buffer1.loadFromFile("test1.wav"))
    {
        std::cout << "Unable to open test1.wav\n";
        return 1;
    }
    if (!buffer2.loadFromFile("test2.wav"))
    {
        std::cout << "Unable to open test2.wav\n";
        return 1;
    }

    if (buffer1.getChannelCount() != buffer2.getChannelCount() || buffer1.getSampleRate() != buffer2.getSampleRate())
    {
        std::cout << "Both buffers must have the same channel count and sample rate\n";
        return 1;
    }

    const auto channels = buffer1.getChannelCount();
    const auto rate = buffer1.getSampleRate();
    const auto size = std::max(buffer1.getSampleCount(), buffer2.getSampleCount());

    auto samples = std::vector<sf::Int16>(size, 0);

    for (auto i = std::size_t{ 0 }; i < size; ++i)
    {
        auto b1 = sf::Int16{ 0 };
        auto b2 = sf::Int16{ 0 };

        if (i < buffer1.getSampleCount())
        {
	        b1 = buffer1.getSamples()[i];
        }
        if (i < buffer2.getSampleCount())
        {
	        b2 = buffer2.getSamples()[i];
        }

        // Mixing
        if (b1 < 0 && b2 < 0)
        {
	        samples[i] = static_cast<sf::Int16>((b1 + b2) - static_cast<sf::Int16>((b1 * b2) / INT16_MIN));
        }
        else if (b1 > 0 && b2 > 0)
        {
	        samples[i] = static_cast<sf::Int16>((b1 + b2) - static_cast<sf::Int16>((b1 * b2) / INT16_MAX));
        }
        else
        {
	        samples[i] = static_cast<sf::Int16>(b1 + b2);
        }
    }

    auto buffer = sf::SoundBuffer{};
    buffer.loadFromSamples(samples.data(), samples.size(), channels, rate);

    auto sound = sf::Sound{ buffer };
    sound.play();

    while (sound.getStatus() == sf::Sound::Playing)
    {
        sf::sleep(sf::seconds(0.5f));
    }
}
