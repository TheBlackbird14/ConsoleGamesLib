# ConsoleGamesLib

A collection of minimalist games, singleplayer and multiplayer, to be played in the Console.

---

## Games

- tictactoe
- battleships

## WIP Games

- Hangman

## Planned games

- Connect 4
- Minesweeper

---

## Install

Download latest version from [releases](https://github.com/TheBlackbird14/ConsoleGamesLib/releases).

or:

```bash

wget https://github.com/TheBlackbird14/ConsoleGamesLib/releases/download/{version}/ConsoleGamesLib.{version}.zip

```

### Unzip

```bash

unzip ConsoleGamesLib.{version}.zip
rm ConsoleGamesLib.{version}.zip
cd ConsoleGamesLib

```

### Compile

Requires CMake to be installed

```bash

cmake .
make

```

### Execute

```bash

./build/cgl

```

### Alternative System-wide install (to /usr/local/bin)

Type ``make install`` instead of ``make``.
To start, type ``cgl`` anywhere in the system.
