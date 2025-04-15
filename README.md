
# NeoSource
NeoSource (formerly EmSource) is a fan-made port of the Source Engine to the WASM platform with additional features. It's an attempt of porting all Source 2013 engine based games such as: Half-Life: Source, Counter-Strike: Source, Half-Life 2 (and its episodic releases), and almost every Source 2013 game you can think of!.


## Acknowledgements

 - [Dear ImGui](https://github.com/ocornut/imgui)
 - [CSGO+ (another project I created)](https://github.com/m1n1maalist/csgo-plus/)
 - [Emscripten](https://github.com/emscripten-core/emscripten/)
## Run Locally

Clone EmSource

```bash
  git clone https://github.com/EmSource/EmSource.git
```

Go to the  directory where you cloned EmSource

```bash
  cd EmSource
```

Install dependencies

```bash
sudo apt-get install build-essential gcc-multilib g++-multilib pkg-config ccache
```

Create Solution:
```bash
./createallprojects.sh
```

Compile Solution.sh
```
emmake make -f Makefile
```
## FAQ

#### Which Operating System's can I compile it with?

We are currently only supporting Linux, specifically Debian-based distributions and Arch Linux-distributions. We have no plan of supporting Windows 7, 8, 10, etc.

#### Add `insert feature here`

If you want a feature to get implemented, please create an issue in the GitHub, or fork the repository, add the feature, and create a pull request.

#### Does this use any leaked code?
Unfortunately, yes we do use leaked code, but this is required for us to fully port the entirety of the engine to the web. Without using the leak, this project wouldn't exist. If you want an "SDK" version of this code, delete all leaked contents from this repository.


## Features

- Cross-Platform support
- Dear ImGui implementation
- Emscripten support.
## Roadmap

- [ ] Additional browser support

- [ ] Add more integrations

- [X] ImGui

- [ ] Mobile Device support

- [ ] Source 2 BSP support

- [ ] CSGO BSP support

- [ ] Windows support

- [X] CI
## Optimizations

> What optimizations did you make in your code?

We decreased some common limits in `public/bspfile.h` which lowered the amount of RAM being used.


## Optimization Levels:
Firstly I recommened reading Emscriptens wiki on [Optimizing Code](https://emscripten.org/docs/optimizing/Optimizing-Code.html)
```
-O0 - No Optimization, allows for quick debugging.
-O1 - Simple optimizations, includes LLVM optimizations.
```
