# Singing Animatronic (Arduino)

Firmware for a singing animatronic character. It plays songs from an MP3
module, moves its servo mouth in time with the audio, and blinks animated LED
eyes. Built on an Arduino in summer 2024.

## Sketches

- `spealer/`: the main sketch, which combines everything:
  - **Audio:** controls a serial MP3 player module (DFPlayer-style command
    frames over SoftwareSerial). It plays songs on startup, and buttons skip
    forward and back.
  - **Volume and pause:** a rotary encoder, read with hardware interrupts,
    sets the volume from 0 to 30. Its push button pauses and resumes.
  - **Lip sync:** an analog audio-level reading opens the servo mouth when the
    signal crosses a threshold. The threshold scales with the volume setting.
    The mouth then eases closed.
  - **Eyes:** a 4×8 WS2812 LED matrix driven with FastLED shows two eyes and
    plays a timed multi-frame blink animation.
- `heartsong/`: the MP3 player controls on their own (rotary encoder to change
  tracks, button to play and pause).
- `trufflute_eye/` and `eye_test/`: development sketches for the LED-matrix
  eyes and blink frames.
- `suit/`: a quick analog sensor reading test.

The MP3 module's command format follows the educ8s.tv Arduino MP3 player
tutorial.

## Hardware

- Arduino (Uno-class)
- Serial MP3 player module and speaker
- Hobby servo (mouth)
- Rotary encoder with push button, plus two buttons
- 4×8 WS2812 LED matrix (eyes)
- Audio-level input on A0

Libraries: FastLED, Servo, SoftwareSerial.
