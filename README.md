# Advent Of Code 2024 :christmas_tree:

This is my repository for the Advent of Code 2024. I will be solving the puzzles in C++ trying to improve my skills in this language and learn the [STL algorithms](https://en.cppreference.com/w/cpp/algorithm). **My goal is not to solve the puzzles as fast as possible**, but to solve them in the best way I can.

## What is Advent of Code?

Advent of Code is an Advent calendar of small programming puzzles for a variety of skill sets and skill levels that can be solved in any programming language you like. People use them as a speed contest, interview prep, company training, university coursework, practice problems, or to challenge each other.

## The structure of the repository

The repository is divided into folders, each one corresponding to a day of the event. Inside each folder, there are two subfolders: `part1` and `part2`. Each one contains the code for the respective part of the puzzle. The input files are stored in the root of the day folder.

```bash
├──day1
│  ├──part1
│  │  ├──src
│  │  │  └──main.cpp
│  │  ├──Makefile
│  ├──part2
│  │  ├──src
│  │  │  └──main.cpp
│  │  ├──Makefile
│  └──input.txt
├──day2
│     etc...
```

## How to run the code?

I will be using Makefiles because using Cmake for such a smalls projects seems like an overkill. Don't forget to include a "input.txt" at the root of each day folder. To compile the code, you can use the following commands:

```bash
cd day01/part1
make
./AoC
```
