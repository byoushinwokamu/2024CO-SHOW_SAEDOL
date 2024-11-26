#include "common.h"

void MIDI_NoteOn(uint8_t note) {
  uint8_t data[3], i;

  // Status byte: Note on & Channel 0
  data[0] = 0b10010000;

  // Data byte 1: Pitch (C3=0 matches to 48)
  data[1] = note + 48;

  // Data byte 2: Velocity (constant)
  data[2] = 64;

  for (i = 0; i < 3; i++)
    UART_transmit(data[i]);
}

void MIDI_NoteOff(uint8_t note) {
  uint8_t data[3], i;

  // Status byte: Note off & Channel 0
  data[0] = 0b10000000;

  // Data byte1: Pitch (C3=0 matches to 48)
  data[1] = note + 48;

  // Velocity (constant)
  data[2] = 0;

  for (i = 0; i < 3; i++)
    UART_transmit(data[i]);
}