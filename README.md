# TimeCo
TimeCo: Time Commando Engine Reimplementation

Welcome to the TimeCo project.
This project aims to reimplement the PC version of Time Commando, a game developed by Adeline Software International in 1996.

With the original source code of both LBA1 and LBA2 now available, we aim to finish to use the shared libraries between Adeline games and create a new engine for Time Commando. The intention is to have a clean codebase for learning purposes and to make it available for everyone and eventually merge few common parts with TwinEngine.

## Project References

* Time Commando Dbug Articles with technical details - https://blog.defence-force.org/index.php?tag=Time%20Commando

* TwinEngine - https://github.com/LBALab/twin-e

* ScummVM twine - https://github.com/scummvm/scummvm/tree/master/engines/twine

* LBA1 Source Code - https://github.com/LBALab/lba1-classic-community

* LBA2 Source Code - https://github.com/LBALab/lba2-classic-community



## Goals

The main goal of this project is to create a modern and portable engine for the game Time Commando and have a clean codebase for learning purposes. We believe that the original architecture of the game is a good base for learning game development and we want to make it available for everyone.

## Status

The project is in its initial stages. We are currently working on the engine architecture and the game data structures. The game is not yet playable.

Check the [TODO.md](TODO.md) for more comprehensive list of upcoming features and tasks.

# How to use it

Place the contents of the game folder into the bin folder and run the executable.


# Compiling

There is a dependency on SDL3 library and it will be reference as a git submodule that will be compiled with the project.

## Mac OS X/Linux

> make sdl

> make

> make run


# Authors

Refer [AUTHORS.md](AUTHORS.md) file for a full list of contributions on this project.

# Copyright

Copyright [2.21]. The intellectual property is currently owned by [2.21].

Originaly developed by Adeline Software International in 1994.

# License

Copyright (C) 2024 TimeCo Team

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Refer [LICENSE](LICENSE) file for full license descriptions.
