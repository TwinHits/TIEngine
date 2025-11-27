# TIEngine

<img src="https://github.com/TwinHits/TIEngine/blob/master/assets/textures/logo.png" alt="TIEngine Logo"
	title="TIEngine Logo" width="350" margin-right="auto" margin-left="auto" />

TIEngine is a 2D game engine built with SFML and Lua scripting. SFML provides the multimedia foundation while Lua handles game-specific logic, keeping the C++ core focused on performance and the gameplay code modifiable without recompilation.

This is a personal project, to me it's like working on an old car in the garage. It's not meant to be finished, just worked on for fun. The goal is to explore design patterns, enjoy writing C++, and express my creativity.

## Architecture

- Cross-platform support (tested on Visual Studio 19.0 and g++ 9.3.0)
- SFML 2.5 for graphics and windowing
- Lua 5.3.5 scripting via sol2 3.2.1
- Boost 1.72.0 for utilities

## Building

1. Clone the repository
2. Install dependencies to a `lib` folder with versioned names (e.g., `SFML-2.5.1-win`)
3. Run `cmake .` to generate Visual Studio solution
4. Copy SFML, Lua, and Boost filesystem DLLs to `src/Debug`
5. Build and run from Visual Studio

## Configuration

Copy `config.ini.sample` to `config.ini` and set your preferred options. Point the `StartUpScript` parameter to your Lua script to begin.

## License

Licensed under [Creative Commons Attribution-NonCommercial-NoDerivatives 4.0 International License](http://creativecommons.org/licenses/by-nc-nd/4.0/).
