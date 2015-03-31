#include <SFML/Config.hpp>
#include <SFML/Audio.hpp>

#include <cmath> // max
#include <cstdint>
#include <vector>

int main()
{
    sf::SoundBuffer buffer1, buffer2;
    buffer1.loadFromFile("test1.wav");
    buffer2.loadFromFile("test2.wav");

    unsigned int ch = 2; // Both buffers need to have the same channel count
    unsigned int rate = 44100; // Both buffers need to have the same sample rate
    std::size_t size = std::max(buffer1.getSampleCount(), buffer2.getSampleCount());

    std::vector<sf::Int16> samples(size, 0);

    for(std::size_t i = 0; i < size; ++i)
    {
        sf::Int16 b1 = 0, b2 = 0;
        if(i < buffer1.getSampleCount())
            b1 = buffer1.getSamples()[i];
        if(i < buffer2.getSampleCount())
            b2 = buffer2.getSamples()[i];

        // Mixing
        if(b1 < 0 && b2 < 0)
            samples[i] = (b1 + b2) - static_cast<sf::Int16>((b1 * b2) / INT16_MIN);
        else if(b1 > 0 && b2 > 0)
            samples[i] = (b1 + b2) - static_cast<sf::Int16>((b1 * b2) / INT16_MAX);
        else
            samples[i] = b1 + b2;
    }

    sf::SoundBuffer buffer;
    buffer.loadFromSamples(samples.data(), samples.size(), ch, rate);

    sf::Sound sound(buffer);
    sound.play();

    while(sound.getStatus() == sf::Sound::Playing)
    {
        // Wait
    }
}
