# nmusic
nmusic is a program that converts files of musical notation in a highly specific format into jgraph files. These jgraph files can then be run through the jgraph program to produce a transcription of the music. The name of nmusic comes from me blatently ripping off Dr. Plank's naming conventions.

# Setting up nmusic
Download everything and then run "sh nmake.sh". This will create nmusic, convert 3 files for jgraph, and then produce 5 pictures of transcribed music.

# Music Theory 
Before I can really get into describing how to use nmusic, I need to make sure you know some basic music theory. If you already know how music generally works, feel free to skip this because it will probably be long.
First, let's talk about time signatures. The most basic (and currently only one available in nmusic) time signature is 4/4.
The first "4" indicates that there are 4 beats in a measure. The second "4" indicates that a quarter note takes up a unit of one beat.
What's a quarter note? Well, this chart should help explain some things:

![1](https://images.prismic.io/flowkey/6ac5b6e8-a0d6-416d-8a78-da310178ffb2_notes-rests.png?auto=compress,format)

These are your basic note types. The length of each beat is relative and determined by the time signature. A quarter note is usually seen as the standard, so I will explain everything relative to that. A half note is two quarter notes. An eighth note is half a quarter note. A sixteenth note is a fourth of a quarter note. The whole note is special. It takes up the entire length of the measure (usually -- sometimes it is depicted as being four quarter notes). There are also "dots". When placed after a note, a dot adds on half of the note's length to the note. So, a dotted half note is three quarter notes. There are also rests. Rest indicate a period of time of not playing a note. They are shown with their note equivalents on the chart. Next, we need to talk about accidentals. 

![2](https://images.prismic.io/flowkey/eee4678f-002e-432e-a326-d7e14a8a416c_notes-accidentals.png?auto=compress,format)

The one shaped like a "#" is called a sharp. It raises a note's pitch. The one shaped like "b" is a flat, and it does the opposite. The one I haven't mentioned yet, and don't have a convenient on-keyboard shape for is called a natural. It removes the effects of a sharp or a flat from a note. It should be noted that sharps, flats, and naturals last until the end of a measure, or until another accidental is placed after it on the measure (for the specific note it is modifying). So, if you place a sharp on the note C in beat 1 of a measure, you do not have to place another sharp on the C in beat 3, assuming you also want it to be sharp. Accidentals do not carry over between notes of the same name on different octaves. This is a good time to also talk about key signatures.

![3](https://images.prismic.io/flowkey/34a1ea23-507a-49ac-9df1-ed62e1a7aca9_grand-staff-key-signature.png?auto=compress,format)

The two fancy looking shapes on the staff (the 5 horizontal lines) are the clefs of music. The one on top is treble, and the one on the bottom is bass. Treble usually contains higher notes, and is played by the right hand on a piano, bass is lower and played by the left hand. (Technically, the hands are actually meant to follow the two staves. The higher one is for the right hand, the lower one is for the left hand). Following the clefs, sharps or flats can be placed. This indicates the key signature. You don't need to know the names of them right now, just know that they indicate that certain accidentals are always active for notes, unless other accidentals are used to cancel them for a measure. For instance, if there is a flat on B in the key signature, then all B's regardless of octave should be played as B-flat, unless otherwise indicated.

```
This next part is important even if you do know what notes are.
```
Notes in music are represented by the letters "ABCDEFG", where A is the lowest of these, and G is the highest. Notes go in order up and down the staff, centered around "Middle C". The note names repeat after all are exhausted, so if you play A-B-C-D-E-F-G-, then the next note will be A again. We'll call this second A, A'. The set of A-A' is called an octave. An octave is the set of eight notes contained between a specific note, and the closest note of the same name. Octaves can be number to indicate their pitch. A higher number indicates a higher pitched octave. Note names and octave can be combined in what is called Scientific Pitch Notation to specificy any note of any pitch. 

![3](https://upload.wikimedia.org/wikipedia/commons/thumb/4/41/Scientific_pitch_notation_octaves_of_C.png/450px-Scientific_pitch_notation_octaves_of_C.png)

This notation is also centered around Middle C. C4 is Middle C. The C above Middle C is C5. The C below Middle C is C3. The A pitch used for tuning instruments, A above Middle C, is A4. nmusic uses this notation to know where to place notes on the staff, so if you are unfamiliar with it, learn how it works. One last really basic thing I should explain is what chords are. Chords are when notes are placed on the same beat on the same staff. This should be enough for you to understand the formatting for nmusic.

# Using nmusic
nmusic is fairily simple. Just run `./nmusic <input_file> <output_file>.jgr`
I will note that it does not automatically run jgraph for you. It merely creates the file for jgraph to read. 
`When run through jgraph, the .jgr file should produce lines of two measures each, with both a bass and treble clef.`

# Creating files for nmusic
Admittedly, the file formatting needed for nmusic is kind of tedious. I feel it absolutely necessary to say that it is very rigid, and you should not put anything that does not need to be there in it. Also, don't forget your delimiters.

## Before actually getting into inputting notes
The file you give nmusic must have a title, composer, arranger, tempo, style, and keys signature. They should be in this format:
```
[Title]
[Composer]
[Arranger]
[Tempo (in bpm)]
[Style]
[SHARP/FLAT] [Notes/-]
```
The newlines are necessary. There can be spaces in the title, composer, arranger, tempo, and style fields. Notes specified in the key signature should be in caps with no spaces. Order of notes does not matter. Put "-" if there are no notes in the key signaute (but make sure to put SHARP or FLAT before it). Here is an example of using this format:
```
Cool Music
Nicholas Parsly
nparsly
200
Ragtime
FLAT BFED
```

## Placing Notes
Each section of notes is divided into 64 possible notes, 32 in treble, and 32 in bass, in that order. This means that each line of music from nmusic is two measures. Each measure is divided into 16 fourths of a beat.
`The word "start" must proceed every section of treble clef. The words "stop" or "continue" must proceed every section of bass clef.`
```
Everything is case sensitive.
```

### Formatting and Options
Every fourth of a beat should be of the format `[typemodifier][notetype] [notemodifier][note] %`
Do not worry about pages. nmusic is smart enough to handle making them.
  #### notetypes
  * `qn`: Places a quarter note
  * `hn`: Places a half note
  * `wn`: Places a whole note
  * `en`: Places an eighth note
  * `sn`: Places a sixteenth note
  * `qr`: Places a quarter rest `DO NOT USE RESTS IN CHORDS AND DO NOT PLACE NOTES AFTER RESTS`
  * `hr`: Places a half rest
  * `wr`: Places a whole rest
  * `en`: Places an eighth rest
  * `sr`: Places a sixteenth rest
  #### typemodifiers
  * `c`: Indicates a chord. Formed by preprending 'c' with any notetype (ex: "cqn"). As many notes of a single type may be placed after a chord as you wish.
  #### notes
  * `(A-G)(0-9)`: Always place notes in that format. Middle C would be denoted as C4
  #### notemodifier
  All note modifiers should be prepended to the notes, or else nmusic will not be able to read the note. More than one modifier can be added to a note, though really it should just be a signal combination of a dot and an accidental. Ex: #.A4
  * `#`: Adds a sharp to a note (It looks like a sharp)
  * `b`: Adds a flat to a note (It looks like a flat)
  * `u`: Adds a natural to a note (If you copy, mirror, and reverse a u, it looks like a natural symbol)
  * `.`: Dots a note (It's a dot)
  #### Note delimiter
  * `%`: Should be placed after every fourth of a beat, even empty beats. Indicates to the program that it can move on to the next fourth of a beat
  #### Section delimiters
  Every 16 possible notes, one of these should be placed. They alternate between `[start]-[continue/stop]-[start]-[continue/stop]-...` "start" comes before treble sections, "continue" and "stop" come before bass sections
  * `start`: Indicates to the program to start a new staff. Must be placed before a treble clef section
  * `continue`: Indicates to the program that there will be more notes after the upcoming bass section
  * `stop`: Indicates that there will not be more notes after the upcoming bass section. Also adds on the end markers to the last measures.
  
### Formatting Example
Here is an exmaple of how to format a simple file for nmusic. Note that the newlines are not necessary (except for the title section). I merely use them to keep things orderly.

```
Title
I composed it
Also me
Swing
120
SHARP AGDE

start
qn B4 %
%
%
%

hn A4 %
%
%
%

en C5 %
%
%
%

en #F4 %
%
%
%

wn bB4 %
%
sn uD5 %
%

qn .B4 %
%
%
%

qr %
%
cen bB4 A4 C5 %
%

hr %
%
qn .#C5 %
%

stop

qn D3 %
%
%
%

hn C3 %
%
%
%

en E3 %
%
%
%

en #A2 %
%
%
%

wn bD3 %
%
sn uF3 %
%

qn .D3 %
%
%
%

qr %
%
cen bD3 C3 E3 %
%

hr %
%
qn .#D3 %
%
```

## Using jgraph
[This webpage](http://web.eecs.utk.edu/~jplank/plank/jgraph/jgraph.html) should help you out if you need to figure out jgraph usage options.

# Images
The first three pictures came from and are linked to this site: https://www.flowkey.com/en/piano-guide/reading-notes
The last picture comes from the wikipedia page on SPN and is in public domain: https://en.wikipedia.org/wiki/Scientific_pitch_notation

# Afterward
Feel free to use and edit this software in any way you like, just credit back here for the original code. If I have some free time in the future, I may well rework nmusic to be a bit better. The biggest issues, at least in my eyes, is that the formatting is far too tedious and the music itself comes out looking a little bit scrunched. Unfortunately these were just two things that I couldn't easily fix once I had delved far enough into the project.  I also realized a fairly simple way to beam runs of flagged notes, but it would have required me rewriting the note handling system, which I just didn't have the time for. I actually think adding onto this would be a pretty decent jgraph project for a future student. They could add in dynamics, ties, accents, a proper way to do chords of varying lengths. I think the first thing anyone should try to rework, though would be the measures. Originally I had wanted to put the standard four measures on each line, but there just wasn't enough space on a page horizontally to also be able to fit the possible sixteeen notes with accidentals per measure. A dynamic measure system

