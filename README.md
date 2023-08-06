# IP-over-audio

--Explanation here--

## Text To Morse

--Explanation here--

Notes:
* if the text file specified does not exist,
this program creates a new text file and asks the user to enter its content.
* This program creates an audio file as well as plays it at run-time.


## Prerequisites

Sox: sudo apt install sox

Command 'paplay': sudo apt install pulseaudio-utils
    
    To play an audio file, execute: paplay example_file.wav

Port-Audio: http://www.portaudio.com/docs/v19-doxydocs/compile_linux.html

PocketSphinx: https://cmusphinx.github.io/doc/pocketsphinx/index.html

CMU Flite: http://www.festvox.org/flite/



Might be a prequisite (as for now, works with\without it):

In the file '/etc/modprobe.d/blacklist.conf',

turn the line 'blacklist pcspkr' to a comment using '#'.



## Important references

https://sox.sourceforge.net/sox.html

https://cmusphinx.github.io/doc/pocketsphinx/simple_8c-example.html

https://github.com/andrewacashner/txt2morse/tree/master

A webpage to validate Morse codes: https://cryptii.com/pipes/morse-code-translator

