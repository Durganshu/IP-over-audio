# IP-over-audio

--Explanation here--

## Text To Morse

--Explanation here--

Notes:
* if the text file specified does not exist,
this program creates a new text file and asks the user to enter its content.
* This program creates an audio file as well as plays it at run-time.


## Prerequisites

Sox: 
```shell
sudo apt install sox
```

Command 'paplay': 
```shell
sudo apt install pulseaudio-utils
```
    
To play an audio file, execute:    
```shell
paplay example_file.wav
```

cmake: 
```shell
sudo apt install cmake
```


Port-Audio: http://www.portaudio.com/docs/v19-doxydocs/compile_linux.html

Might be a prequisite (as for now, works with\without it):

In the file '/etc/modprobe.d/blacklist.conf',

turn the line 'blacklist pcspkr' to a comment using '#'.

## Build instructions

```shell
mkdir build && cd build
cmake ../
make
```

## Execution

```shell
./test_code example_file.txt
```

## Important references

https://sox.sourceforge.net/sox.html

https://cmusphinx.github.io/doc/pocketsphinx/simple_8c-example.html

https://github.com/andrewacashner/txt2morse/tree/master

A webpage to validate Morse codes: https://cryptii.com/pipes/morse-code-translator

