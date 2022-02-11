# RLUtilities C++ Example Bot - RLBotBM edition

A ready to use template of a C++ Rocket League bot using [RLBot-BM](https://github.com/L0laapk3/RLBot-BM_Lib) and [RLUtilities](https://github.com/samuelpmish/RLUtilities/).

## Prerequisites
- [RLBotGUI](http://rlbot.org/)
- [CMake](https://cmake.org/download/) 3.8 and higher
- Compiler with c++17 support
  - GCC 8.1 and higher (9.1 if using mingw)
  - Visual Studio 2017 and higher
  - Clang 7 and higher (not tested)

## How to use:
- Clone this repository by running:

  `git clone https://github.com/L0laapk3/RLBotBM-RLUtilitiesCPPExampleBot.git --recursive`
- Open RLBotGUI, add the cloned folder (Add -> Load Folder) and start a match with the example bot(s).
### Visual Studio
- Navigate to the folder and run `cmake -A x64 -B build .`
- Go to the generated `build` folder and open the `.sln` file with Visual Studio.
- Confirm that Build->Build Solution works.
- Right click on _RLUtilitiesCPPExampleBot_ in the solution explorer and choose 'Set as StartUp Project'
- Choose Debug->Start Debugging (or F5), or press the green play button in Visual Studio.
### VS Code
- Install the [CMake Tools extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools).
- Run the `CMake: Debug` command (or press Ctrl+F5) to start debugging
- To build in release mode, run `CMake: Select Variant` and select `Release`. Then you can run `CMake: Build`.
### CLion
- CLion detects CMakeLists.txt and add a Debug configuration automatically.
- Press F5 to debug or Ctrl+F5 to run.
- To add a Release configuration, go to _Settings -> Build, Execution, Deployment -> CMake_ and add a new profile with Build type set to Release.
## Auto-start
The rlbot framework has the ability to launch the bot executable automatically. This is useful when sharing your bot and usually required when you enter a tournament.

In order to get auto-starting to work you will need to do the following things.
- Build your bot executable (in Release mode!).
- Find your bot executable in CMake build output (usually `build/Release`) and copy it to the `rlbot` folder.
- Set the `cpp_executable_path` field in `rlbot/CppPythonAgent.cfg` so it points to the bot executable.
