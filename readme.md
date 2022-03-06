<img width="843" alt="Screen Shot 2021-12-06 at 11 02 21 PM" src="https://user-images.githubusercontent.com/38915815/144964107-0618a666-bca1-4c03-bc6a-dc05cfb2c224.png">

# Space-Evaders 🚀

A single-level, space-themed game built with C and the popular games programming library, Raylib https://www.raylib.com/

This game was built as a course project for CMPE 320. This project was completed together with a team of 6 other students. We followed the agile development methodology and the scrum framework, and we used JIRA to manage project tasks.

You can find a demo of the game at https://spacevaders.surge.sh

# Steps for Building

After cloning the repo, make sure to run:

```bash
git submodule update --init
```

This will pull the source code from the Raylib repo. At the time of writing, the submodule is set to look at Raylib release v3.7.0

## macOS
The project is built statically and without xcode.

Ensure that you have xcode tools installed. Update in the app store after if needed.

```bash
xcode-select --install
```

Then run
```bash
./build.sh
```

Finally, to the run the game, use the run script
```bash
./run.sh
```

## Web

Simply run

```bash
./build_web.sh
```

This will generate all needed files in bin/surge. To run the web app, use

```bash
./run_web.sh
```

## Windows

For building on windows, MinGW is required.
The easiest way to do this is by installing Raylib, then setting an environment variable pointing to C:\raylib\mingw\bin

Then run
```bash
build.bat
```
