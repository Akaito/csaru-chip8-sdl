#!/bin/bash

pushd working-dir >/dev/null
progfile=~/chip8-roms/chip8.com/Chip-8\ Programs/IBM\ Logo.ch8
progfile=~/chip8/roms/minimal.ch8
chip8-step "$progfile" "$1" "$2"
popd >/dev/null

