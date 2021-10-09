# How to Build
After cloning the repo, make sure to run:

```bash
git submodule update --init
```

This will pull the source code from the Raylib repo. At the time of writing 
this readme, the submodule is set to look at Raylib release v3.7.0

## Mac
We will be building the project statically and without xcode.

First ensure that you have xcode tools installed. Update in the app store after if needed.
```bash
xcode-select --install
```

Then run
```bash
sh build.sh
```

## Windows

First ensure that you have the MinGw compiler toolchain installed.
The easiest way to do this is by installing Raylib, then setting
in the PATH environment variable a item pointing to C:\raylib\mingw\bin

Then run
```bash
build.bat
```

If you are running the build script from inside powershell (which happens when you try to run the script from Clion or Visual Studio Code), then make sure to run
```bash
./build.bat
```

### Possible errors on Windows

I found that I had two versions of g++ installed, resulting in 64 bit binaries and 32 bit gdb.
This meant that I was unable to debug the binaries after building, heavily impeding development.

To check for multiple versions run the following.
```bash
where g++
``` 
