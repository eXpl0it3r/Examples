Examples
========

Every now and then I sit down and tryout some features of some library or even C++ itself or since I'm quite active in the official SFML forum I end up writing the same example code over and over again.
So instead of letting those code fragments go to waste on my computer or in the SFML forum I decided to put them openly and centralized here on GitHub for everyone to see, share and learn from them.

Keep in mind that the code is provided as-is and isn't always suited for final products, since I didn't spend much time thinking about performance or nice code design decisions.

zlib
====

[gzip Decompression](https://github.com/eXpl0it3r/Examples/blob/master/zlib/GzipDecompression.cpp)
--------------------

zlib is a small and useful library which allows the compression and decompression of data. By applying some settings it's possible to let zlib decompress a gzip file, which this examples demonstrates by loading a file into memory and output the decompressed data to standard output.

SFML
====

[Fading Dots](https://github.com/eXpl0it3r/Examples/blob/master/SFML/FadingDots.cpp)
-------------

This was originally created as a test for [this thread](http://en.sfml-dev.org/forums/index.php?topic=9350.0) (or was it [this one](http://en.sfml-dev.org/forums/index.php?topic=9139.0)?), but since I kind of liked the result I adjusted a few things and uploaded it.

![Fading Dots](https://i.imgur.com/7UZEi3s.png)

[Flashlight](https://github.com/eXpl0it3r/Examples/blob/master/SFML/Flashlight.cpp)
------------

Out of nowhere came suddenly all those requests (starting with [this one](http://en.sfml-dev.org/forums/index.php?topic=9210.0)) for subjective blending and I think, I could help a few people with my example on how to achieve what they wanted.

![Flashlight 1](https://i.imgur.com/B6g0Ba5.png) ![Flashlight 2](https://i.imgur.com/N7xn8v6.png)


[Hue Shift](https://github.com/eXpl0it3r/Examples/blob/master/SFML/HueShift.cpp)
-----------

Although I can't find the original SFML thread about this, I found the [StackOverflow question](http://stackoverflow.com/questions/11458552/cycle-r-g-b-vales-as-hue/) which was IIRC created before the forum thread. This effect can definitely give a nice ambiance, but it probably could need some retouching.
Since the picture do not tell much: Starting off with one color the example automatically iterates through the whole RGB color spectrum in a smooth way.


[Lightning](https://github.com/eXpl0it3r/Examples/tree/master/SFML/Lightning)
-----------

I had once read a tutorial in connection with SFML on how to create some nice 'laser' effect. Unfortunately I don't remember which blog/site this was on, because he was using some texture moving which made everything look even better. While doing a search to possible find that tutorial again, I found another similar piece of code [on the forum](http://en.sfml-dev.org/forums/index.php?topic=3189.0), adapted it for SFML 2 and made a nicer class out of it.

![Lightning](https://i.imgur.com/XJdze9h.png)


[Road](https://github.com/eXpl0it3r/Examples/blob/master/SFML/Road.cpp)
------

I'm not sure if there ever existed a forum post or if the whole conversation happened on IRC, but someone wanted to make a 'scrolling' road and since I really liked that idea, I went ahead and implemented an example. The code here is particularly not that nice, so keep that in mind when adapting it.

![Road](https://i.imgur.com/3dtHMNk.png)


[Simple AABB](https://github.com/eXpl0it3r/Examples/blob/master/SFML/SimpleAABB.cpp)
-------------

Every month there's at least one question on simple collision detection testing the last 'bigger' one with in [this forum thread](http://en.sfml-dev.org/forums/index.php?topic=9352.0), which lead to this example. I've even implemented some *very* simple physics, which will fail in most situations, but you can at least move around and jump.

![AABB](https://i.imgur.com/imYEzXa.png)


[Mixing SoundBuffers](https://github.com/eXpl0it3r/Examples/blob/master/SFML/MixingSoundBuffers.cpp)
---------------------

The other day in #learnprogramming on freenode someone was trying to implement a way to mix two audio files without actually playing them back. I wondered how something like that would work with SFML and thus went ahead an wrote a small example. A quick Google search on audio sample mixing brought me to [this site](http://atastypixel.com/blog/how-to-mix-audio-samples-properly-on-ios/) and lead me to the current implementation.


License
=======

All examples are under the zlib/png license and thus free to use. See the [LICENSE](https://github.com/eXpl0it3r/Examples/blob/master/LICENSE) file for more details.
