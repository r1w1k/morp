#ifndef _KMIDI_H_
#define _KMIDI_H_

#define NOTE_ON 0b10010000
#define NOTE_OFF 0b10000000
#define CHANNEL_MODE 0b10110000
#define CONTROL 0b10110000
#define SUSTAIN 64
#define STOP_KNOB 83
#define ADD_REST 0b00111000
#define ALL_OFF 0b01111011
#define KEYBOARD "nanoKEY2 KEYBOARD"
#define KMIDI_OUTPUT "IAC Driver KMidi"


#include <map>
#include "RtMidi.h"
#include "Phrase.h"
#include "ProjectSaver.h"

namespace KMidi{
	extern std::map<int, std::string> note_names;
	extern std::map<int, std::string> note_names_flats;
	std::string note_name(int decimal, bool use_flats = true);
}


class MidiIn{
public:
	RtMidiIn *in;
	bool open = false;
	std::string id;

	std::vector<std::vector<Note>> get_voices(const std::string& message="Press enter when done:");
	
	int tap_tempo();
	void clear_queue();

	MidiIn();
	~MidiIn();
};

class MidiOut{
public:
	RtMidiOut *out;
	int channel;
	std::string id;

	void sleep(const int &ms);
	double play(Phrase *p, double l=0);
	void note_on(Note n);
	void note_off(Note n);
	void sustain_on();
	void sustain_off();

	void all_notes_off();
	bool sustain{ false };

	MidiOut(int c=0);
	~MidiOut();
};

#endif