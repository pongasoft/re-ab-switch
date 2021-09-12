A/B Audio & CV Switch (Rack extension)
======================================

This project contains the full source code for the free rack extension A/B Audio & CV Switch for Reason, the music DAW produced by Reason Studios. Check the [A/B Audio & CV Switch](https://pongasoft.com/rack-extensions/ABSwitch.html) website for more details.

### Notes

* The source code is released following Reason Studios decision to open up the Rack Extension SDK platform allowing for this kind of project to be made publicly available
* It is mostly meant as an example of a fully functional RE and the code is sparsely documented. I have since used C++ more intensively (in Jamba and other VST plugins) and would probably make very different implementation decisions now, especially being more familiar with "modern" C++.
* The master branch is currently unreleased as the code has been updated to use [re-cmake](https://github.com/pongasoft/re-cmake) and RE SDK 4.2.0 but there are no new features. The advantage is that it is much easier to build and can be build on both macOS and Windows10.
* This rack extension was developed with the 3D workflow and migrated to the 2D workflow (which is the reason why the `GUI2D` directory contains the same graphics multiple times and the files `GUI2D/device_2D.lua` and `GUI2D/hdgui_2D.lua` have been generated)
* This rack extension contains the very first iteration of what became the mini framework [re-common](https://github.com/pongasoft/re-common) but has not been backported to use `re-common`

### Requirements

* This project requires CMake (minimum version 3.13) properly installed (`cmake` executable must be in your `PATH`)
* This project currently expects RE SDK 4.2.0 or 4.1.0 to be installed on the machine (it will not download it for you)
* Due to the RE SDK requirements, this project also requires python 3 to be installed
* It has been tested on macOS 10.14.6 with Xcode 9 installed
* It has been tested on Windows 10 with Visual Studio 16 2019 build tools

### Structure

* `Design` contains the Pixelmator files used to create the graphics (for the 3D workflow)
* `GUI2D` is a standard RE SDK folder which contains the images (png format) as well as `device_2D.lua` and `hdgui_2D.lua` files which defines the UI
* `Resources` is a standard RE SDK folder which contains the strings (English only) displayed in the UI
* `src/cpp` contains the C++ source code for the device
* `info.lua`, `motherboard_def.lua` and `realtime_controller.lua` are standard RE SDK files for defining the device
* `configure.py` is the python 3 script you use to configure the CMake build

### Implementation notes

* Because this device uses SDK 2.2, it uses C++11 (but be aware that it is a limited (by the SDK) version of C++11).
* The properties use a property manager (`JBoxPropertyManager`) which automatically processes the `iPropertyDiffs` provided on each batch to update the properties.
* The `Device` class represents the entry point and is the class that is the `privateState` in the C-style `JBox_Export_RenderRealtime` api. It contains 2 copies of the `DeviceState` class: one being the state from the previous batch and one the state for the current batch. At the end of the batch, the current state is copied into the previous state. This allow to see if values have changed and respond appropriately. This design inspired the first iteration of the Jamba framework (VST) but with refinement it then led to having the Property (aka Parameters in VST world) themselves hold the previous and current values which I now believe is a better design. I may retrofit this design in a future implementation...

### Note about the RE SDK location

You can install the SDK wherever you want on your system and provide it as an argument to the `configure.py` script. Or you can install (or create a link) in a default location:

* `/Users/Shared/ReasonStudios/JukeboxSDK_<RE_SDK_VERSION>/SDK` for macOS
* `C:/Users/Public/Documents/ReasonStudios/JukeboxSDK_<RE_SDK_VERSION>/SDK` for Windows

Also note that the `RE2DRender` program needs to be unzipped and is expected to be a sibling of `SDK` (can be changed as well).

Quick Starting guide
--------------------

#### Step 1 - Configure the build

Invoking the `configure.py` **creates** a `build` directory in the directory where the command is run. Although it is strongly recommended to run this command outside the source tree, the `build` directory is excluded in `.gitignore` and since everything is contained within the `build` folder it is easy to clean after the fact.

Running the `python3 configure.py -h` command will print the usage.

> #### Note
> Depending on how `python` is installed on your system you may have to invoke it differently.

> #### Note
> This script is expecting the `cmake` command line tool to be in the path (use `cmake -version` to confirm it is properly installed).

If you have setup the RE SDK in its default location, as specified above, simply run `python3 configure.py` otherwise use the `-p` option to specify its location.

#### Step 2 - Install the plugin

After running the configure script, simply go into the newly generated `build` folder and run `re.sh install` (resp. `re.bat install`). This will build the plugin and install it in its default location.

> #### Note
> Simply run `re.sh -h` (resp. `re.bat -h`) for help with the command

> #### Note
> This script is expecting the `cmake` command line tool to be in the path (use `cmake -version` to confirm it is properly installed).

#### Step 3 - Try the plugin

You can then open Recon and load the newly built `ABSwitch` rack extension (you will find it under `Utilities | pongasoft | A/B Audio & CV Switch`)

> #### Info
> The plugin will **only** appear in Recon **not** Reason 

### Changing the code, Debugging, etc...

If you want to change the code, run a debugger, etc... you can check the instructions for the [re-blank-plugin](https://github.com/pongasoft/re-blank-plugin#quick-starting-guide) which explain how to generate an XCode project, load it in an IDE, etc... 

Release notes
-------------

#### master (unreleased)

* Upgraded to use [re-cmake](https://github.com/pongasoft/re-cmake) (removed all unnecessary files  and added CMake build files) 
* Upgraded to use RE SDK 4.2.0
* Builds properly on Apple chipset
* Use [re-mock](https://github.com/pongasoft/re-mock) for testing

#### 1.2.0 - 2016/03/13

* You can now control the 2 switches (audio and CV) when the device is folded.

#### 1.1.0 - 2015/03/20

* Added labels for each input (audio and CV) on the front of the device.
* Added CV CTRL sockets for audio and CV to control the device via CV.

#### 1.0.0 - 2015/03/06

* First release.


License
-------

- This project is released under the terms of the [Apache 2.0 license](LICENSE.txt)

- This project uses the Rack extension SDK released under the [Rack Extension License agreement](RE_License.txt)
