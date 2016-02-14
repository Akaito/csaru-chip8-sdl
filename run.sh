#!/bin/bash

pushd working-dir >/dev/null
progfile=~/chip8-roms/chip8.com/Chip-8\ Programs/IBM\ Logo.ch8
chip8-step "$progfile" "$1"
popd >/dev/null

