#pragma once

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)
    // #define STARTUP_SONG SONG(ONE_UP_SOUND)
    // #define STARTUP_SONG SONG(MARIO_THEME)


    #define DEFAULT_LAYER_SONGS { SONG(MARIO_GAMEOVER), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(ZELDA_PUZZLE), \
                                  SONG(ZELDA_TREASURE), \
                                  SONG(ZELDA_TREASURE), \
                                  SONG(ZELDA_TREASURE), \
                                  SONG(ZELDA_TREASURE), \
                                  SONG(ZELDA_TREASURE), \
                                  SONG(MARIO_GAMEOVER) \
                                }
#endif

#define RGB_MATRIX_KEYPRESSES
// stop ignoring my quick mod keys
#define PERMISSIVE_HOLD
#define TAPPING_TOGGLE 2
/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/

#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

// Most tactile encoders have detents every 4 stages
#define ENCODER_RESOLUTION 4

