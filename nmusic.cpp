//Nicholas Parsly
//CS494 Jgraph 
//nmusic - Creates jgraph files from the file given on the command line
//NOTE - If you decide to change the size of the graph or the measure lengths, you will probably have to make
//small adjustments to a decent portion of the note placing code

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdlib>

using namespace std;

//These are some defaults used for note and accidental placing
//The baseline for all notes is the middle line on the staff (B4 in treble, D3 in bass)
const double xbase = 23.0;
const char ntreble = 'B';
const int otreble = 4;
const char nbass = 'D';
const int obass = 3;
const double basenote = 0.5; //A downward note on the middleline is placed at 0.5 so that the notehead lines up properly
const double upadjust = 3.0; //An upward note needs to have 3 added to that y value so that it's head lines up
const double flatadjust = 0.3;
const double trelative[] = {-0.5, 0.0, -3.0, -2.5, -2.0, -1.5, -1.0};
const double brelative[] = {2.5, 3.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0};

//Places the title, composer, arranger, style, and tempo
//These things are necessary in a file input into the program
void placeTitle(istream &fin, ostream &fout) {

	string s;

	getline(fin, s);
	fout << "newstring hjc vjc x 80 y 15 fontsize 20 : " << s << "\n";
	getline(fin, s);
	fout << "newstring hjr vjc x 155 y 10 fontsize 10 : Composer: " << s << "\n";
	getline(fin, s);
	fout << "newstring hjr vjc x 155 y 8 fontsize 10 : Arranger: " << s << "\n";
	getline(fin, s);	
	fout << "newstring hjl vjc x 0 y 10 fontsize 10 : Style: " << s << "\n";
	getline(fin, s);
	fout << "newstring hjl vjc x 0 y 8 fontsize 10 : Tempo = " << s << " bpm\n";

	return;

}

//Places a page number. Useful for longer compositions
void placePageNum(ostream &fout, int num) {

	fout << "newstring hjc vjc x 0 y 15 fontsize 10 : " << num << "\n";

	return;
}

//Fills a vector with the base values for accidentals on the key signature
//Putting - will just skip the process entirely
vector <double> fillVec(string temp) {

	vector <double> v;
	v.resize(0);

	if (temp == "-") {

		return v;
	}

	if (temp.find("A") != string::npos) {

		v.push_back(1.5);	
	}

	if (temp.find("B") != string::npos) {

		v.push_back(2.0);	
	}

	if (temp.find("C") != string::npos) {

		v.push_back(2.5);	
	}

	if (temp.find("D") != string::npos) {

		v.push_back(3.0);	
	}

	if (temp.find("E") != string::npos) {

		v.push_back(3.5);	
	}

	if (temp.find("F") != string::npos) {

		v.push_back(4.0);	
	}

	if (temp.find("G") != string::npos) {

		v.push_back(4.5);	
	}

	return v;
}

//Adds the time signature. This is a method solely in case anyone wants to add diferent time signatures
void placeTimeSig(ostream &fout) {

	fout << "newstring hjl vjc x 16 y 3 fontsize 24 : 4\n";
	fout << "newstring hjl vjc x 16 y 1 fontsize 24 : 4\n";

	return;
}

//Places the clef, key signature, and measure lines on the staff
void placeKeySig(ostream &fout, vector <double> &v, bool sharp, bool treble) {

	double val;
	double x;

	//Placing measure lines
	fout << "newline pts 159 0 159 4\n";
	fout << "newline pts 88 0 88 4\n";

	//Placing clef
	if (treble) {

		fout << "newcurve eps noteeps/treble.eps marksize 4 7 pts 3 2\n";
	}

	else {

		fout << "newcurve eps noteeps/bass.eps marksize 4 3 pts 3 2.6\n";
	}

	//Determines which accidental to use
	if (sharp) {

		fout << "newcurve eps noteeps/sharp.eps marksize 1.5 1.5 pts";
	}

	else {

		fout << "newcurve eps noteeps/flat.eps marksize 1.5 1.5 pts";
	}

	//Places the accidentals from the vector
	for (int i = 0; i < v.size(); i++) {

		//Adjusts for which clef it's in
		if (treble) {

			val = 0;
		}

		else {

			val = -1;
		}

		//Adjust for which accidentals are being used
		if (!sharp) {

			val = val + flatadjust;
		}

		//These are all literal values because that seemed like it would be easiest
		//You will have to adjust all of these if you change the way measures work
		
		//A
		if (v.at(i) == 1.5) {

			if (sharp) {

				x = 12;
			}

			else {

				x = 10;
			}
		}

		//B
		if (v.at(i) == 2.0) {

			if (sharp) {

				x = 14;

			}

			else {

				x = 8;
			}
		}

		//C
		if (v.at(i) == 2.5) {

			if (sharp) {

				x = 9;
			}

			else {

				x = 13;
			}
		}

		//D
		if (v.at(i) == 3.0) {

			if (sharp) {

				x = 11;
			}

			else {

				x = 11;
			}
		}

		//E
		if (v.at(i) == 3.5) {

			if (sharp) {

				x = 13;
			}

			else {

				x = 9;
			}
		}

		//F
		if (v.at(i) == 4.0) {

			if (sharp) {

				x = 8;
			}

			//F and G have special cases where they drop in octave if the signature is flat
			else {

				val = val - 3.5;
				x = 14;
			}
		}

		//G
		if (v.at(i) == 4.5) {

			if (sharp) {

				x = 10;
			}

			else {

				val = val - 3.5;
				x = 12;
			}
		}

		val = val + v.at(i);

		fout << " " << x << " " << val;
	}

	fout << "\n";
}

//These all place accidentals and dots
//They should remain consistent with changes to measure lengths
void placeSharp(ostream &fout, double x, double y) {

	fout << "newcurve eps noteeps/sharp.eps marksize 1.5 1.5 pts " << x << " " << y << "\n";
}

void placeFlat(ostream &fout, double x, double y) {

	fout << "newcurve eps noteeps/flat.eps marksize 1.5 1.5 pts " << x - 0.5 << " " << y << "\n";

}

void placeNatural(ostream &fout, double x, double y) {

	fout << "newcurve eps noteeps/natural.eps marksize 1.5 1.5 pts " << x - 0.5 << " " << y << "\n";

}

void placeDot(ostream &fout, double x, double y) {

	fout << "newstring hjl vjc x " << x << " y " << y << " fontsize 36 : .\n";
}

//The backbone of this system basically. It place each note
void placeNote(ostream &fout, string s, string notetype, bool treble, double x) {

	double y;
	double truey;				//truey is the actual note position on the staff. Used for whole notes, rest, accidentals
	int o;
	char n;
	bool flip;					//If a note must be moved slightly to avoid adjacent note overlap on a chord
	bool stem;
	bool forcedown;
	bool forceup;
	bool nup;					//If a note is facing upward
								//nup and flip lead to coordinate changes

	flip = false;
	stem = false;
	forcedown = false;
	forceup = false;
	nup = false;
	y = basenote;

	//Stemmed notes use y, nonstemmed notes (whole notes) use truey
	if (notetype != "w") {

		stem = true;
	}

	//These bools are important for chord positioning
	if (notetype.find("f") != string::npos) {

		flip = true;
	}

	if (notetype.find("-") != string::npos) {

		forcedown = true;

	}

	if (notetype.find("+") != string::npos) {

		forceup = true;
	}

	//Extract note value from input
	n = s.at(s.length() - 2);
	o = s.at(s.length() - 1) - '0';

	//Note values are determined from their octave and the note itself
	//These values are adjusted pased on relativity to the midline
	//Each 3.5 indicates an octave up or down
	//Basic formula (y = [position from midline] + [3.5 * number of octaves from midnote] + modifiers)
	if (treble) {

		y = y + trelative[n - 'A'];
		y = y + (3.5 * (o - otreble));

		if (y < 0.5) {

			//Note stem direction logic - If a note is below midline it's stem goes up, otherwise it goes down
			//There are exceptions - that's why forceup and forcedown exist
			nup = true; 
		}
	}

	else {

		y = y + brelative[n - 'A'];
		y = y + (3.5 * (o - obass));


		if (y < 0.5) {

			nup = true; 
		}

	}

	if (forceup) {

		nup = true;
	}

	if (forcedown) {

		nup = false;
	}

	//true y value adjustment
	truey = y + 1.5;

	//Place accidentals and dots based on input
	//May need to fiddle with x adjustments if you change measure lengths/graph size
	if (s.find("#") != string::npos) {

		placeSharp(fout, (x - 2.25), truey);
	}

	if (s.find("b") != string::npos) {

		placeFlat(fout, (x - 2), (truey + flatadjust));

	}

	if (s.find("u") != string::npos) {

		placeNatural(fout, (x - 2), truey);

	}

	if (s.find(".") != string::npos) {

		placeDot(fout, (x + 1), (truey + 1));
	}

	//True y is also used to calculate the placement lines used for high and low notes
	//These are theoretically infinitely scaleable if you want to go into pitches that humans can/should not hear
	if (truey > 4.5) {

		for (int i = 5; i <= truey; i++) {

			fout << "newline linethickness 2.0 pts " << (x - 1) << " " << i << " " << (x + 1) << " " << i << "\n";
		}
	}

	else if (truey < -0.5) {

		for (int i = -1; i >= truey; i--) {

			fout << "newline linethickness 2.0 pts " << (x - 1) << " " << i << " " << (x + 1) << " " << i << "\n";
		}
	}

	//Whole note placement
	if (!stem) {

		if (flip) {

			x = x - 1.25;
		}

		fout << "newcurve eps noteeps/whole.eps marksize 2.5 1 pts " << x << " " << truey << "\n";
		return;
	}

	//Stemmed notes
	else {

		//Quarter notes and half notes have a gimmick where 4 different versions of them have to exist
		//to handle every way they can be flipped for chords

		//Quarter notes
		if (notetype.find("q") != string::npos) {

			if (nup) {

				y = y + upadjust;

				if (flip) {

					x = x + 1.25;
					fout << "newcurve eps noteeps/quarternotestemupleft.eps marksize 1.6 4 pts ";
					fout << x << " " << y << "\n";
				}

				else {

					fout << "newcurve eps noteeps/quarternotestemupright.eps marksize 1.6 4 pts ";
					fout << x << " " << y << "\n";
				}
			}

			else {

				if (flip) {

					x = x - 1.25;
					fout << "newcurve eps noteeps/quarternotestemdownright.eps marksize 1.6 4 pts ";
					fout << x << " " << y << "\n";
				}

				else {

					fout << "newcurve eps noteeps/quarternotestemdownleft.eps marksize 1.6 4 pts ";
					fout << x << " " << y << "\n";
				}
			}
		}

		//Half notes
		else if (notetype.find("h") != string::npos) {

			if (nup) {

				y = y + upadjust;

				if (flip) {

					x = x + 1.25;
					fout << "newcurve eps noteeps/halfnotestemupleft.eps marksize 1.6 4 pts ";
					fout << x << " " << y << "\n";
				}

				else {

					fout << "newcurve eps noteeps/halfnotestemupright.eps marksize 1.6 4 pts ";
					fout << x << " " << y << "\n";
				}
			}

			else {

				if (flip) {

					x = x - 1.25;
					fout << "newcurve eps noteeps/halfnotestemdownright.eps marksize 1.6 4 pts ";
					fout << x << " " << y << "\n";
				}

				else {

					fout << "newcurve eps noteeps/halfnotestemdownleft.eps marksize 1.6 4 pts ";
					fout << x << " " << y << "\n";
				}
			}
		}

		//Eighth and Sixteenth notes should theoretically have the gimmick listed above,
		//but I realized that after I already set up most of this program
		//so I created a workaround in placeChord

		//Eighth notes 
		else if (notetype.find("e") != string::npos) {

			if (nup) {

				y = y + upadjust;
				fout << "newcurve eps noteeps/eighthup.eps marksize 3 4 pts " << x + 0.5 << " " << y << "\n";
			}

			else {

				fout << "newcurve eps noteeps/eighthdown.eps marksize 1.5 4 pts " << x + 0.2 << " " << y << "\n";
			}

		}

		//Sixteenth note
		else if (notetype.find("s") != string::npos) {

			if (nup) {

				y = y + upadjust;
				fout << "newcurve eps noteeps/sixteenthup.eps marksize 3 4 pts " << x + 0.5 << " " << y << "\n";
			}

			else {

				fout << "newcurve eps noteeps/sixteenthdown.eps marksize 1.5 4 pts " << x + 0.2 << " " << y << "\n";
			}
		}
	}
}

//Comparison function for placeChord
//Needed to order notes in a vector based on placement
bool compFunction(string s1, string s2) {

	char a1;
	char b1;
	char a2;
	char b2;

	a1 = s1.at(s1.length() - 1);
	b1 = s1.at(s1.length() - 2);

	a2 = s2.at(s2.length() - 1);
	b2 = s2.at(s2.length() - 2);

	if (a1 != a2) {

		return (a1 < a2);
	}

	return (b1 < b2);
}

//Places chords. Has a lot of edge cases
void placeChord(istream &fin, ostream &fout, string notetype, bool treble, double x) {

	string temp;
	string s;
	bool flagnext;				//The workaround I mentioned above. If an eight note needs to be flipped for a chord
								//Just let the one above/below it handle the stem
								
	bool flipnext;				//Indicates if the next note above/below needs to be flipped
	int o;
	int tempv;
	char n;
	double val1;
	double val2;
	double high;
	double low;
	double y;
	bool nup;
	vector <string> is;
	vector <double> iv;

	flagnext = false;
	flipnext = false;

	nup = false;

	//Simplification of notetypes so I don't have to check for npos on all of them
	if (notetype.find("qn") != string::npos) {

		temp = "q";
	}

	else if (notetype.find("hn") != string::npos) {

		temp = "h";
	}

	else if (notetype.find("wn") != string::npos) {

		temp = "w";
	}

	else if (notetype.find("en") != string::npos) {

		temp = "e";
	}

	else if (notetype.find("sn") != string::npos) {

		temp = "s";
	}

	//Read until the delimiter
	while (fin >> s) {

		if (s == "%") {

			break;
		}

		//Calculate note position and put it into the vector along with its name
		n = s.at(s.length() - 2);
		o = s.at(s.length() - 1) - '0';

		if (treble) {

			y = trelative[n - 'A'];
			y = y + (3.5 * (o - otreble));	
		}

		else {

			y = brelative[n - 'A'];
			y = y + (3.5 * (o - obass));
		}

		is.push_back(s);
		iv.push_back(y);

		//Save the highest and low position for chord stem direction logic
	}

	//Sort the notes from low to high
	sort(is.begin(), is.end(), compFunction);
	sort(iv.begin(), iv.end());
	
	low = iv.at(0) - 0.5;
	high = iv.at(iv.size() - 1);
	//Chord stems are based on the which note is farthest from the midline
	//If the farthest note is above, the stem points down
	//Otherwise it points up. If there's a tie, the stem points down by default
	if (low < 0) {

		low = low * -1;
	}

	if (high < low) {

		nup = true;
	}

	//This conditional holds basically all the chord logic
	//I will explain most of it in the first half
	//They are divided based on if the stem goes up or down
	if (nup) {

		//Also an initial explanation. For notes with flags (eight, sixteenth, etc) they are placed
		//as quarter notes on the chord, except for the highest/lowest depending on chord direction
		//because there is only one flag on a flagged chord. Also this decision will help you
		//if you decide to add beams to flagged notes

		//Starts from the highest note
		for (int i = (is.size() - 1); i >= 0; i--) {

			//If this note needs to be flipped, flip it
			if (flipnext) {

				flipnext = false;

				if (temp == "w") {

					placeNote(fout, is.at(i), "wf+", treble, x);

				}

				else if (temp == "h") {

					placeNote(fout, is.at(i), "hf+", treble, x);
				}

				else {

					placeNote(fout, is.at(i), "qf+", treble, x);
				}

				continue;
			}

			//tempv is used for determining if a note falls on or between staff lines
			tempv = (int) (2 * (iv.at(i) + 1.5));

			if (tempv < 0) {

				tempv = tempv * -1;
			}

			//If this note needs to have a flag, make sure it is placed as one that has the proper flag
			if (flagnext) {

				flagnext = false;

				if (temp == "e") {

					placeNote(fout, is.at(i), "e+", treble, x);
				}

				else {

					placeNote(fout, is.at(i), "s+", treble, x);
				}

				continue;
			}

			//Checks every note before the last one
			if (i > 0) {

				//Determine the distance between this note and the one below it
				val1 = iv.at(i);
				val2 = iv.at(i - 1);
				
				val1 = val2 - val1;

				if (val1 < 0) {

					val1 = val1 * -1;
				}
				

				//If they are adjacent
				if (val1 == 0.5) {

					//Check if the note is on a line
					if (tempv % 2 == 0) {

						//If it is and is a flagged note,
						if (temp == "e" || temp == "s") {

							///Check if it is the highest note
							if (i == (is.size() - 1)) {

								//If it is, set the second highest note to have a flag instead
								flagnext = true;
								placeNote(fout, is.at(i), "qf+", treble, x);
								continue;
							}
						}

						//If it isn't flagged or the highest note, place it as a whole, half, or quarter note
						if (temp == "w") {

							placeNote(fout, is.at(i), "wf+", treble, x);

						}

						else if (temp == "h") {

							placeNote(fout, is.at(i), "hf+", treble, x);
						}

						else {

							placeNote(fout, is.at(i), "qf+", treble, x);
						}

						continue;
					}

					//If this note is between lines, then the one below it needs to be flipped
					else {

						flipnext = true;
					}
				}
			}


			//If none of these conditions are met, place it normally
			if (temp == "w") {

				placeNote(fout, is.at(i), "w+", treble, x);

			}

			else if (temp == "h") {

				placeNote(fout, is.at(i), "h+", treble, x);
			}

			else {

				//And if it is the highest note and flagged, make sure it has a flag
				if (i == (is.size() - 1)) {

					if (temp == "e") {
				
						placeNote(fout, is.at(i), "e+", treble, x);
						continue;
					}

					if (temp == "s") {

						placeNote(fout, is.at(i), "s+", treble, x);
						continue;
					}
				}

				placeNote(fout, is.at(i), "q+", treble, x);
			}
		}
	}

	//This is the case for notes pointing down. This set is done from the lowest note to the highest
	else {

		for (int i = 0; i < is.size(); i++) {

			//Check for flipping
			if (flipnext) {

				flipnext = false;

				if (temp == "w") {

					placeNote(fout, is.at(i), "wf-", treble, x);

				}

				else if (temp == "h") {

					placeNote(fout, is.at(i), "hf-", treble, x);
				}

				else {

					placeNote(fout, is.at(i), "qf-", treble, x);
				}

				continue;
			}

			tempv = (int) ((iv.at(i) + 1.5) * 2);

			if (tempv < 0) {

				tempv = tempv * -1;

			}

			//Check if the second lowest note needs to be flagged
			if (flagnext) {

				flagnext = false;

				if (temp == "e") {

					placeNote(fout, is.at(i), "e-", treble, x);
				}

				else {

					placeNote(fout, is.at(i), "s-", treble, x);
				}

				continue;
			}


			//Check every note above this note, unless this is the highest note
			if (i < (is.size() - 1)) {

				
				val1 = iv.at(i);
				val2 = iv.at(i + 1);
				
				val1 = val2 - val1;

				if (val1 < 0) {

					val1 = val1 * -1;
				}	

				if (val1 == 0.5) {
					
					if (tempv % 2 == 0) {

						//If it's on a line, and adjacent, and the lowest note, set the next note to be flagged
						if (temp == "e" || temp == "s") {

							if (i == 0) {

								flagnext = true;
								placeNote(fout, is.at(i), "qf-", treble, x);
								continue;
							}
						}

						//Place this normally
						if (temp == "w") {

							placeNote(fout, is.at(i), "wf-", treble, x);

						}

						else if (temp == "h") {

							placeNote(fout, is.at(i), "hf-", treble, x);
						}

						else {

							placeNote(fout, is.at(i), "qf-", treble, x);
						}

						continue;
					}
					
					//Otherwise, if this note is between lines, set the next note above to be flipped
					else {

						flipnext = true;
					}
				}
			}

			if (temp == "w") {

				placeNote(fout, is.at(i), "w-", treble, x);

			}

			else if (temp == "h") {

				placeNote(fout, is.at(i), "h-", treble, x);
			}

			else {

				//Place a stem on the lowest note if the above case is note present
				if (i == 0) {

					if (temp == "e") {
				
						placeNote(fout, is.at(i), "e-", treble, x);
						continue;
					}

					if (temp == "s") {

						placeNote(fout, is.at(i), "s-", treble, x);
						continue;
					}
				}

				placeNote(fout, is.at(i), "q-", treble, x);
			}
		}
	}
}

//Places the markers for the end of a song
void placeEnd(ostream &fout) {

	fout << "newline linethickness 5.0 pts 159 0 159 4\n";
	fout << "newline pts 158 0 158 4\n";
}

//Sets up measures based oninput
void setMeasure(istream &fin, ostream &fout, bool treble) {

	double x;
	string s;

	//Reads in two measures
	for (int i = 0; i < 32; i++) {

		x = xbase + ((i % 16) * 4);

		if (i > 15) {

			x = x + 70;
		}

		//Read until you find a % delimiter or there's a chord
		while (fin >> s) {

			if (s == "%") {

				break;
			}

			if (s.find("c") != string::npos) {

				placeChord(fin, fout, s, treble, x);
				break;
			}

			//Place whatever notes are listed
			if (s.find("qn") != string::npos) {

				fin >> s;
				placeNote(fout, s, "q", treble, x); 
			}

			else if (s.find("hn") != string::npos) {

				fin >> s;
				placeNote(fout, s, "h", treble, x); 
			}

			else if (s.find("wn") != string::npos) {

				fin >> s;
				placeNote(fout, s, "w", treble, x); 
			}

			else if (s.find("en") != string::npos) {

				fin >> s;
				placeNote(fout, s, "e", treble, x); 
			}

			else if (s.find("sn") != string::npos) {

				fin >> s;
				placeNote(fout, s, "s", treble, x); 
			}

			//Place whatever rests are listed
			if (s.find("qr") != string::npos) {

				fout << "newcurve eps noteeps/quarterrest.eps marksize 1.5 3 pts " << x << " 2\n";
			}

			if (s.find("hr") != string::npos) {

				fout << "newcurve eps noteeps/halfrest.eps marksize 2.5 1 pts " << x << " 2.5\n";
			}

			if (s.find("wr") != string::npos) {

				fout << "newcurve eps noteeps/wholerest.eps marksize 2.5 1 pts " << x << " 1.5\n";
			}

			if (s.find("er") != string::npos) {

				fout << "newcurve eps noteeps/eighthrest.eps marksize 1.5 2 pts " << x << " 2\n"; 
			}

			if (s.find("sr") != string::npos) {

				fout << "newcurve eps noteeps/sixteenthrest.eps marksize 1.5 2 pts " << x << "2\n";
			}
		}
	}
}

int main(int argc, char *argv[]) {

	ifstream fin;
	ofstream fout;
	vector <double> accidental;
	int counter;
	int pagenum;
	bool sharp;
	bool treble;
	bool ending;
	string temp;
	string s;

	//Check for proper arguments and files
	if (argc != 3) {

		cout << "Usage: " << argv[0] << " input_file output_file\n";
	}

	fin.open(argv[1]);

	if (!fin.is_open()) {

		cout << "Bad input file\n";
		return -1;
	}

	fout.open(argv[2]);

	if (!fout.is_open()) {

		cout << "Bad output file\n";
		return -1;
	}

	//Create the first staff
	fout << "newgraph\n";
	fout << "xaxis size 8 min 0 max 159 hash 1 no_draw_hash_marks no_draw_hash_labels\n";
	fout << "yaxis size 0.5 min 0 max 4 hash 1 mhash 0 no_draw_hash_marks no_draw_hash_labels grid_lines grid_gray 0\n";

	placeTitle(fin, fout);

	//Set the key signature accidentals
	fin >> temp;

	if (temp == "SHARP") {

		sharp = true;
	}

	else {

		sharp = false;
	}

	fin >> temp;

	accidental = fillVec(temp);


	pagenum = 1;
	ending = false;
	counter = 2;

	//Loop for reading the music
	while (fin >> s) {

		//Treble clef must begin with "start" (even if it is not the first treble in the music)
		if (s != "start") {

			fout.close();
			fin.close();
			cout << "Bad file format: No start before treble clef\n";
			return -1;
		}

		treble = true;
		counter = counter - 2;

		//Create a new page after 4 sets of measures are done
		if (counter < -7) {

			counter = 0;
			pagenum = pagenum + 1;
			fout << "newpage\n";
			fout << "newgraph\n";
			fout << "xaxis size 8 min 0 max 159 hash 1 no_draw_hash_marks no_draw_hash_labels\n";
			fout << "yaxis size 0.5 min 0 max 4 hash 1 mhash 0 no_draw_hash_marks no_draw_hash_labels grid_lines grid_gray 0\n";
		}

		//Place the page number and time signature if a new page has just started
		if (counter == 0) {

			placePageNum(fout, pagenum);
			placeTimeSig(fout);
		}

		//Otherwise create a new set of measures
		else {

			fout << "copygraph\n";
			fout << "y_translate " << counter << "\n";
		}


		//Place the key signature and start reading notes
		placeKeySig(fout, accidental, sharp, treble);
		setMeasure(fin, fout, treble);

		fin >> s;

		//There are two options for the delimiter between treble and bass
		//Stop - indicates that this treble and the upcoming bass are the end, and places the end markers
		if (s == "stop") {

			ending = true;
			placeEnd(fout);
		}

		//Continue - indicates that there may be another set of measures after the upcoming bass set
		else if (s != "continue") {

			cout << "bad con: " << s << "\n";
			fout.close();
			fin.close();
			cout << "Bad file format: No continue or stop after treble clef\n";
			return -1;
		}

		//Bass measures
		treble = false;

		fout << "copygraph\n";
		fout << "y_translate " << counter - 1 << "\n";
		placeKeySig(fout, accidental, sharp, treble);
		setMeasure(fin, fout, treble);

		//If the end markers are placed, then it can stop reading
		if (ending) {

			placeEnd(fout);
			break;
		}
	}

	fout.close();
	fin.close();

	return 0;
}
