# IP-over-audio

This project implements the transmission of morse-encoded messages over TCP and UDP transmission systems. 

The client encodes an audio message in the Morse code and generates a WAV file. In order to send the audio message to the server, the user can choose between TCP and UDP protocols. The audio file is transported using the selected protocol and the receiver stores it locally. The receiver then decodes the message and gives the appropriate response.


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

Both server and client have various options at their disposal.

```shell
$> ./ip-over-morse -h
Options:
  -s / --send          send the message
  -r / --receive       receive the message
  -p / --port          specify port(default:8080
  -a / --address       specify destination address(default: 127.0.0.1)
  -pcl                 specify protocol: UDP or TCP (default:TCP)
  -h / --help          print this help
```

Example for a receiver (using TCP):

```shell
shell1$>./ip-over-morse -s -p 54321 -a 127.0.0.1
```

Example for a sender (using TCP):

```shell
shell1$>./ip-over-morse -r
```

Example for a receiver (using UDP):

```shell
shell1$>./ip-over-morse -s -p 54321 -a 127.0.0.1 -pcl UDP
```

Example for a sender (using TCP):

```shell
shell1$>./ip-over-morse -r -pcl UDP
```

## Important references

https://sox.sourceforge.net/sox.html

https://github.com/andrewacashner/txt2morse/tree/master

A webpage to validate Morse codes: https://cryptii.com/pipes/morse-code-translator

