# 3.1 Requirements & Installation

## Requirements
At the moment, this emulator runs only on Windows, and it requires either the MSVC or Clang compiler. That’s because a few compiler-specific pragmas were used along the way.

Support for Linux and GCC is definitely on my radar, but that’s something planned for a future release — so stay tuned.

You will also need >= Python 3.10.

## Installation
### GUI automatic setup
Want an easy setup? You can now use a GUI tool created by Mikael. See  [🛠️ Setup Tool (GUI)](https://github.com/SoWeBegin/MicrovoltsEmulator/blob/mv1.1_2.0/doc/tool_for_setup.md)

If you use the GUI tool you can skip this and most of the next chapters too, as it automatically covers most of the points. However, if you want detailed knowledge on how everything works (so multiple servers across different VPS, linking your website to the servers, etc), you can keep reading.

### Manual setup 
The installation process is pretty much the same as it was in version 1.0 when it comes to setting up the servers. Most of the dependencies are handled through vcpkg, and a vcpkg.json file is already provided to help with that.

Here’s how to get everything set up:
1. Clone this repository locally.
2. Open a terminal and cd into your project’s ExternalLibraries folder: `cd <YourProjectPath>/ExternalLibraries`
3. Clone vcpkg into this directory: `git clone https://github.com/microsoft/vcpkg.git`
4. Go into the new vcpkg folder and bootstrap it: `cd vcpkg` followed by `.\bootstrap-vcpkg.bat`
5. Integrate vcpkg with Visual Studio: `.\vcpkg integrate install`
6. Move the provided vcpkg.json (in the root directory) file into the newly created vcpkg folder.
7. Run the install: `.\vcpkg install`
8. Open the visual studio solution (.sln in the root directory)
9. For each project (MainServer, CastServer, AuthServer, Common):
   - Go to Project Properties > Configuration Properties > vcpkg
   - Under Installed Directory, set it to your vcpkg install path. Example: `..\ExternalLibraries\vcpkg\vcpkg_installed`
   - ⚠️ Important: Only Release mode is fully set up with the right paths. If you want to compile in Debug mode, you’ll need to manually copy over the paths from Release
10. Once everything is configured, build the projects in this order: Common first, and then the servers right after (MainServer / AuthServer / CastServer).

⚠️ Note: if your main server fails to compile with an error `python (...) generate_command_includes.py exited with code 1`:
- right click on the main server => properties
- Go to "Build Events" => "Pre-Build Events"
- change `python "$(ProjectDir)generate_command_includes.py"` to just `"$(ProjectDir)generate_command_includes.py"`
- If this fix does not work for you, please open up a new Issue.

The resulting .exe files will be placed in your project's x64 output folder.


## Next
[3.2 Setting up the emulator](https://github.com/SoWeBegin/MicrovoltsEmulator/blob/mv1.1_2.0/doc/setting_up.md)



### TBA
WINDOWS

1. clone vcpkg in ExternalLibraries
git clone https://github.com/microsoft/vcpkg.git ExternalLibraries/vcpkg

2. Bootstrap it
.\ExternalLibraries\vcpkg\bootstrap-vcpkg.bat

3. move vcpkg.json to new vcpkg folder
move vcpkg.json ExternalLibraries\vcpkg\

4. install vcpkg.json dependencies
- cd ExternalLibraries/vcpkg
- vcpkg install --triplet x64-windows

5. Generate build files
- cd .. 
- cd ..
- cmake -B build -S . -A x64 -DCMAKE_TOOLCHAIN_FILE=ExternalLibraries/vcpkg/scripts/buildsystems/vcpkg.cmake

6. Build
cmake --build build --config Release


=> Executables will be inside MicrovoltsEmulator/Release/
=> Common.lib will be inside MicrovoltsEmulator/ExternalLibraries/CommonLib/


