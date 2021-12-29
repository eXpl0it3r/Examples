#include <SFML/Audio.hpp>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

int main()
{
    auto bufferOne = sf::SoundBuffer{};
	auto bufferTwo = sf::SoundBuffer{};

    if (!bufferOne.loadFromFile("test1.wav"))
    {
        std::cerr << "Unable to open test1.wav\n";
        return 1;
    }
    if (!bufferTwo.loadFromFile("test2.wav"))
    {
        std::cerr << "Unable to open test2.wav\n";
        return 1;
    }

    if (bufferOne.getChannelCount() != bufferTwo.getChannelCount() || bufferOne.getSampleRate() != bufferTwo.getSampleRate())
    {
        std::cerr << "Both buffers must have the same channel count and sample rate\n";
        return 1;
    }

    const auto channels = bufferOne.getChannelCount();
    const auto rate = bufferOne.getSampleRate();
    const auto size = std::max(bufferOne.getSampleCount(), bufferTwo.getSampleCount());

    auto samples = std::vector<sf::Int16>(size, 0);

    for (auto i = std::size_t{ 0u }; i < size; ++i)
    {
        auto bufferOneSample = sf::Int16{ 0 };
        auto bufferTwoSample = sf::Int16{ 0 };

        if (i < bufferOne.getSampleCount())
        {
	        bufferOneSample = bufferOne.getSamples()[i];
        }
        if (i < bufferTwo.getSampleCount())
        {
	        bufferTwoSample = bufferTwo.getSamples()[i];
        }

        // Mixing
        if (bufferOneSample < 0 && bufferTwoSample < 0)
        {
	        samples[i] = static_cast<sf::Int16>((bufferOneSample + bufferTwoSample) - static_cast<sf::Int16>((bufferOneSample * bufferTwoSample) / INT16_MIN));
        }
        else if (bufferOneSample > 0 && bufferTwoSample > 0)
        {
	        samples[i] = static_cast<sf::Int16>((bufferOneSample + bufferTwoSample) - static_cast<sf::Int16>((bufferOneSample * bufferTwoSample) / INT16_MAX));
        }
        else
        {
	        samples[i] = static_cast<sf::Int16>(bufferOneSample + bufferTwoSample);
        }
    }

    auto buffer = sf::SoundBuffer{};
    if (!buffer.loadFromSamples(samples.data(), samples.size(), channels, rate))
    {
        std::cerr << "Unable to load the mixed sample data\n";
    }

    auto sound = sf::Sound{ buffer };
    sound.play();

    while (sound.getStatus() == sf::Sound::Playing)
    {
        sf::sleep(sf::seconds(0.5f));
    }
}
