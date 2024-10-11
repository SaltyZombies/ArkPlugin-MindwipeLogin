# MinewipeLogin
This plugin automatically performs a mindwipe when a player takes over or "possesses" a character in Ark Ascended. This action occurs only once per server.

## Requirements
- A copy of this repository, including the AsaApi submodule located in `extern\AsaApi\`
  - `git submodules update`
- [Visual Studio 2022](https://visualstudio.microsoft.com/vs/community/)
  - Install the "Desktop development with C++" workload via the Visual Studio Installer
  - Configure Visual Studio to use vcpkg (launch the Visual Studio Developer Command Prompt under Tools -> Command Line, and enter `vcpkg integrate install`)
- An **ARK: Survival Ascended** dedicated server with AsaApi installed

## 1: Build AsaApi.lib
To create fully functional plugins, first build the AsaApi library for linking. Open `extern\AsaApi\AsaApi.sln` with Visual Studio, set the build configuration to `Release` and platform to `x64`, and build the solution. Once completed, `AsaApi.lib` will be in `extern\AsaApi\out_lib\`. The plugin project is configured to find the library there.

## 2: Install Your Plugin
After building your plugin solution, the output will be in the `out\` directory.

### [MindwipeLogin].dll
Install your plugin on an **ARK: Survival Ascended** server by placing this DLL, into the server's `ShooterGame\Binaries\Win64\ArkApi\Plugins\MindwipeLogin\` directory.

### [MindwipeLogin].dll.arkapi
A copy of your plugin DLL for easier testing. If your plugin is already loaded, drop `MindwipeLogin.dll.arkapi` into the `ShooterGame\Binaries\Win64\ArkApi\Plugins\MindwipeLogin\` directory. AsaApi will automatically reload the plugin and rename this file to `MindwipeLogin.dll`.

**Note:** Configure AsaApi's automatic plugin reloading in the server's `config.json` file.

### MindwipeLogin.pdb
Contains debug info for detailed information during debugging or crash logs. Place it in the server's `ShooterGame\Binaries\Win64\ArkApi\Plugins\MindwipeLogin\` directory, and AsaApi will move it to `ShooterGame\Binaries\Win64\`.
