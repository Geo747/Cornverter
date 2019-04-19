/*Copyright 2018 George Rennie

Things to note:
When no note is playing a value of 128 is returned as both note and velocity
Velocities and Notes must be in the range 0-127 as with MIDI
If more than one note on message on the same note is sent before receiving a note off message then the previous note ons will be forgotten from the stack and the note will be removed on the first corresponding note off message reveived*/

#include "PolyToMono.h"

//Data array to keep all the addresses and stuff with one dimension used to determine channel
//Each index in the second dimension represents one midi note with the last index being a no note indicator
//The third dimension contains preceding note to that 2nd dimension index, then following note and then that notes velocity
static uint8_t data[MIDI_CHANNELS][129][3];
static uint8_t saveNote[MIDI_CHANNELS];

void polyToMonoSetup(void) {
  for (uint8_t i = 0; i < MIDI_CHANNELS; i++) {
    for (uint8_t j = 0; j < 129; j++) {
      for (uint8_t k = 0; k < 3; k++) {
        data[i][j][k] = 128; //Init all places in the data array to 128 (i.e. the no note value)
      }
    }
    saveNote[i] = 128; //Init all savenote places to no note value
  }
}

static inline uint8_t channelInRange(uint8_t channel) {
  if (channel < MIDI_CHANNELS) { return 1; }
  return 0;
}

void polyToMonoNoteOn(uint8_t note, uint8_t velocity, uint8_t channel) {

  if ((data[channel][note][2] != 128) && (note != saveNote[channel])) { //If it doesnt have a velocity of 128 (i.e. it is already in the stack, and it isnt the last place on the stack)
		uint8_t prevNote = data[channel][note][0]; //Patch the references for the two notes either side of its original place
		uint8_t nextNote = data[channel][note][1]; //as it is now being moved to the front of the stack
		data[channel][prevNote][1] = nextNote;
		data[channel][nextNote][0] = prevNote;
	}

	data[channel][note][2] = velocity; //Save the velocity of the note
	if (note == saveNote[channel]) { return; } //If its a repeat of current held note do nothing more
	data[channel][saveNote[channel]][1] = note; //The next note for the previous note is the new note
	data[channel][note][0] = saveNote[channel]; //The last note for the new note is the previous note
	saveNote[channel] = note;
}

void polyToMonoNoteOff(uint8_t note, uint8_t channel) {

  data[channel][note][2] = 128; //Velocity off for note
	if (note == saveNote[channel]) { //If it is last note on stack move pointer back one.
		saveNote[channel] = data[channel][note][0]; //As the velocity has been set to 128 (off) the values left in its references are irrelevant
	}
	else {
		uint8_t prevNote = data[channel][note][0]; //Patch references for preceding and following notes
		uint8_t nextNote = data[channel][note][1]; //So they reference each other and not the note that
		data[channel][prevNote][1] = nextNote; //That is being removed
		data[channel][nextNote][0] = prevNote;
	}
}

void polyToMonoAllNotesOff(uint8_t channel) {
  while (saveNote[channel] != 128) {
    data[channel][saveNote[channel]][2] = 128; //Set last note on stack velocity  to 0
		saveNote[channel] = data[channel][saveNote[channel]][0]; //As the velocity has been set to 128 (off) the values left in its references are irrelevant    
  }
}

uint8_t polyToMonoCurrentNote(uint8_t channel) {
  return saveNote[channel];
}

uint8_t polyToMonoCurrentVelocity(uint8_t channel) {
  return data[channel][saveNote[channel]][2];
}

uint8_t polyToMonoIsNoteOn(uint8_t channel) {  
  if (saveNote[channel] == 128) { return 0; }
  return 1;
}