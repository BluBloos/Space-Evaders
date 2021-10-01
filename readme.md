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