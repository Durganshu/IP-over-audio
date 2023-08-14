import wave
morse_encoder = { 'A':'.-', 'B':'-...',
                    'C':'-.-.', 'D':'-..', 'E':'.',
                    'F':'..-.', 'G':'--.', 'H':'....',
                    'I':'..', 'J':'.---', 'K':'-.-',
                    'L':'.-..', 'M':'--', 'N':'-.',
                    'O':'---', 'P':'.--.', 'Q':'--.-',
                    'R':'.-.', 'S':'...', 'T':'-',
                    'U':'..-', 'V':'...-', 'W':'.--',
                    'X':'-..-', 'Y':'-.--', 'Z':'--..',
                    '1':'.----', '2':'..---', '3':'...--',
                    '4':'....-', '5':'.....', '6':'-....',
                    '7':'--...', '8':'---..', '9':'----.',
                    '0':'-----', ', ':'--..--', '.':'.-.-.-',
                    '?':'..--..', '/':'-..-.', '-':'-....-',
                    '(':'-.--.', ')':'-.--.-'}
morse_decoder = {v: k for k, v in morse_encoder.items()}

wav = wave.open('C:/Users/OWNER/Documents/Christian/TUM/EuroTeQ/Distributed Application/morse code/example_file.wav','r')
print( "Number of channels",wav.getnchannels())
print ( "Sample width",wav.getsampwidth())
print ( "Frame rate.",wav.getframerate())
print ("Number of frames",wav.getnframes())
print ( "parameters:",wav.getparams())
num_frames = int(wav.getframerate()*wav.getsampwidth()/100) # how many frames to read at once
print ('frames to read at once', num_frames)
zz = []  #1a (26) 7d
for j in range(wav.getnframes()//num_frames):
    x = wav.readframes(num_frames)
    sum=0
    for i in range(0,len(x),2):
        n = x[i] + x[i+1]*256;
        if n>65536/2: n = n-65536
        if n<0: n = -n
        sum += n;
    sum = 2* sum/ num_frames
    #print (sum)
    if sum>16000:
        zz.append(1)
    else:
        zz.append(0)
#print(zz)
wav.close()
x = zz[0]
max0 = 0
min0 = 0
min1 = 0
max1 = 0
br = 1
for i in zz:
    if i==x:
        br+=1
    else:
        if x == 0:
            if br>max0:
                max0 = br
            if br<min0 or min0==0:
                min0 = br
        else:
            if br>max1:
                max1 = br
            if br<min1 or min1==0:
                min1 = br
        br = 1
        x = i
print(min0,max0,min1,max1)
pause_letter = (2*min0-1)
pause_word = max0 - min0
dash = (min1+max1)/2
letter = ''
word = ''
sentence = ''
br = 1
x = zz[0]
for i in zz:
    if i==x:
        br += 1
    else:
        if x==1:
            if br>dash:
                letter +="-"
            else:
                letter += "."
        else:
            if br> pause_letter:
                print(letter,morse_decoder.get(letter))
                word+=str(morse_decoder.get(letter))
                letter = ''
            if br > pause_word:
                sentence += word + ' '
                word = ''

        br = 1
        x = i
print(sentence)
