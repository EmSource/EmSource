
# Half-Life 2: Javascript
Half-Life 2: Javascript is a work-in-progress port of Half-Life 2 to Emscripten, and no this isn't going to be some kind of shitty remake of HL2 for the browser, no this is an actual port of it.

## History
The history of this project is fairly simple. This project originally started under the name "CSGO: Plus", but later the original account which owned the "CSGO: Plus" repository was deleted. Later, a new project was made named "EmSource", which was based under the Source 2013 leak instead of the CSGO leak, but later, after a few days, the project was renamed to NeoSource, since Mohamed Ashraf wanted to to do something more than just simply port Source 2013 to Emscripten, he wanted to add new features. But later the project was renamed to Lambda Complex: Source where it is a remake of Opposing Force. But currently, it is now under the name "HL2JS" running on the Source 2013 engine branch for more support for newer mods.

```
Source 2013 ⭨
            EmSource ⭨        
               NeoSource ⭨ 
                    Lambda Complex Source ⭨ 
Kisak Strike ⭨      🡕                     HL2JS
    ⭦     CSGO: Plus
    CSGO ⭧
```

## FAQ
- **What version of Source does this run on?**
The Source 2013 Engine branch, from the 2020 leak.
- **Can I use this as a base for my modification?**
Yes you may, but credit Mohamed Ashraf in your mod's credits (Unless, you were approved by me before.)
- **Can I compile on Windows?**
No, you can't, and I have no plans on supporting platforms other than Linux. But if you'd like to add VS2022 or MSVC support, then you're PR will be greatly appreciated.

## Documentation

### Compiling

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
