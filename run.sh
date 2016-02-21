#!/bin/bash

progpath=~/chip8-roms/chip8.com/Chip-8\ Programs/

progfile=IBM\ Logo.ch8
progfile=Chip8\ Picture.ch8
progfile=BMP\ Viewer\ -\ Hello\ \(C8\ example\)\ [Hap,\ 2005].ch8
#progfile=Clock\ Program\ \[Bill\ Fisher,\ 1981\].ch8 # 0xF8FA; bad


progpath=~/chip8-roms/chip8.com/Chip-8\ Demos/

progfile=Zero\ Demo\ \[zeroZshadow,\ 2007\].ch8
#progfile=Trip8\ Demo\ \(2008\)\ \[Revival\ Studios\].ch8
progfile=Maze\ \[David\ Winter,\ 199x\].ch8
#progfile=Sierpinski\ \[Sergey\ Naydenov,\ 2010\].ch8


progpath=~/chip8-roms/chip8.com/Chip-8\ Games/

#progfile=Blinky\ \[Hans\ Christian\ Egeberg,\ 1991\].ch8
#progfile=Blinky\ \[Hans\ Christian\ Egeberg\]\ \(alt\).ch8
#progfile=Pong\ \(alt\).ch8
#progfile=Space\ Flight.ch8
progfile=Space\ Invaders\ \[David\ Winter\]\ \(alt\).ch8
#progfile=Tetris\ \[Fran\ Dachille,\ 1991\].ch8
#progfile=Tron.ch8
#progfile=ZeroPong\ \[zeroZshadow,\ 2007\].ch8
#progfile=Tank.ch8


#progpath=~/chip8/roms/

#progfile=minimal.ch8
#progfile=pong-story.com/UFO
#progfile=pong-story.com/BLINKY

chip8-sdl "${progpath}${progfile}"

