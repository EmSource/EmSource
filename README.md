
#  Half-Life 2: Javascript
Half-Life 2: Javascript is a work-in-progress port of Half-Life 2 to Emscripten, and no this isn't going to be some kind of shitty remake of HL2 for the browser, no this is an actual port of it.

## FAQ
- **What version of Source does this run on?**
The Source 2013 Engine branch, from the 2020 leak.
- **Can I use this as a base for my modification?**
Yes you may, but credit Mohamed Ashraf in your mod's credits (Unless, you were approved by me before.)
- **Can I compile on Windows?**
No, you can't, and I have no plans on supporting platforms other than Linux. But if you'd like to add VS2022 or MSVC support, then you're PR will be greatly appreciated.


## Features
- Full Emscripten toolset supported (emcc, em++, emar, etc.)


## Compiling

> [!NOTE]
> Note that this implementation isn't only limited to "Half-Life 2", rather any game that runs on the Source 2013 engine branch.

Firstly, ensure you have all dependencies listed on the Valve Developer Wiki article on developing Source SDK 2013 modifications, and you obviously have to have the Emscripten toolset installed with you.

Firstly clone this repository and enter the src directory.

```bash
git clone https://github.com/HalfLife2JS/HL2JS
cd HL2JS/src/
```

Now run the `createallprojects` file then run `make -f everything.mak`, or `make -f <MAKEFILE GENERATED>`.

## License
There is no license, since this is based on the Source Engine leak. All you really need to do is credit me.
