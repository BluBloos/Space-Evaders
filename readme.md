# How to Build
After cloning the repo, make sure to run:

```bash
git submodule update --init
```

This will pull the source code from the Raylib repo. At the time of writing 
this readme, the submodule is set to look at Raylib release v3.7.0

Then, simply run
```bash
build.bat
```

If it fails, it is likely that you do not have MinGW properly setup 
in your system environment variables.

## Possible errors when building

I found that I had two version of g++ installed, resulting in 64 bit binaries and 32 bit gdb.
This meant that I was unable to debug the binaries after building, heavily impeding development.

Simply run 

```bash
where g++
``` 

In any command prompt to find if you have multiple versions of g++. You can try a similar process for
checking on multiple versions of gdb.