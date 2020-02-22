A/B Audio & CV Switch (Rack extension)
======================================

This project contains the full source code for the free rack extension A/B Audio & CV Switch for Reason, the music DAW produced by Reason Studios. Check the [A/B Audio & CV Switch](https://pongasoft.com/rack-extensions/ABSwitch.html) website for more details.

Notes
-----

* The source code is released following Reason Studios decision to open up the Rack Extension SDK platform allowing for this kind of project to be made publicly available

* It is mostly meant as an example of a fully functional RE and the code is sparsely documented. I have since used C++ more intensively (in Jamba and other VST plugins) and would probably make very different implementation decisions now, especially being more familiar with "modern" C++.

* Unfortunately, the SDK does not come with a CMakefile making this project tied to a single platform (macOS being the one I am using).

* I am also not including any IDE (XCode or other) related files because of how it ends up being tied to install locations (which could be fixed as well with a CMakefile).

* This rack extension was developed with the 3D workflow and migrated to the 2D workflow (which is the reason why the `GUI2D` directory contains the same graphics multiple times and the files `GUI2D/device_2D.lua` and `GUI2D/hdgui_2D.lua` have been generated)

* This rack extension contains the very first iteration of what became the mini framework [re-common](https://github.com/pongasoft/re-common)

Requirements
------------

* This project builds on macOS (10.13.6)

* This project uses RE SDK version 2.2 (location defined in `jukebox.py` and should be changed according to your system). It has **not** been tested with a more recent version of the SDK (I do know for a fact that the options required by `build45.py` have changed since 2.2).

# Structure

* `Design` contains the Pixelmator files used to create the graphics (for the 3D workflow)

* `GUI2D` is a standard RE SDK folder which contains the images (png format) as well as `device_2D.lua` and `hdgui_2D.lua` files which defines the UI

* `Resources` is a standard RE SDK folder which contains the strings (English only) displayed in the UI

* `src/cpp` contains the C++11 source code for the device

* `info.lua`, `motherboard_def.lua` and `realtime_controller.lua` are standard RE SDK files for defining the device

* `display.lua` is the standard SDK file which contains the lua code for the UI (various custom displays)

* `build-dev.sh` and `build-prod.sh` are the main 2 scripts to build the device for dev and prod respectively. They are simple wrapper which invokes the `build45.py` script with the correct set of options

* `copy-resources.sh` is another wrapper script to only copy the resources without full rebuild (ex: when working on the UI only there is no need to rebuild/repackage the source code)

* `render2D.sh` calls the `RE2DRender` process properly (with workaround to see the output in the console). This is the step that processes the content of `GUI2D` to produce the necessary graphic files for the rack extension.

Implementation notes
--------------------

* Because this device uses SDK 2.2, it uses C++11 (but be aware that it is a limited (by the SDK) version of C++11).

* The properties use a property manager (`JBoxPropertyManager`) which automatically processes the `iPropertyDiffs` provided on each batch to update the properties.

* The `Device` class represents the entry point and is the class that is the `privateState` in the C-style `JBox_Export_RenderRealtime` api. It contains 2 copies of the `DeviceState` class: one being the state from the previous batch and one the state for the current batch. At the end of the batch, the current state is copied into the previous state. This allow to see if values have changed and respond appropriately. This design inspired the first iteration of the Jamba framework (VST) but with refinement it then led to having the Property (aka Parameters in VST world) themselves hold the previous and current values which I now believe is a better design. I may retrofit this design in a future implementation...

Building (macOS)
----------------

* Run `render2D.sh` to generate the images and files necessary for the UI. This step generates a `GUI` folder with the results.

```
> ./render2D.sh
Rendering 2D
/Volumes/Vault/Applications/JukeboxSDK_2.2/RE2DRender/RE2DRender.app/Contents/MacOS/RE2DRender /Volumes/Development/github/org.pongasoft/re-ab-switch/GUI2D /Volumes/Development/github/org.pongasoft/re-ab-switch/GUI
Deleting Intermediate folder
Deleting Output folder
[...]

+ exit 0
---- End of PostProcess log
```

* Run `build-dev.sh`

```
> ./build-dev.sh
Using /Volumes/Vault/Applications/JukeboxSDK_2.2/SDK/Tools/LLVM
product_id: com.pongasoft.ABSwitch
RACK_EXTENSION_NAME: ABSwitch

[...]

Copying resources to installDir: /Users/ypujante/Library/Application Support/Propellerhead Software/RackExtensions_Dev/ABSwitch
install_name_tool -id com.pongasoft.ABSwitch '/Users/ypujante/Library/Application Support/Propellerhead Software/RackExtensions_Dev/ABSwitch/ABSwitch.dylib'
Build finished
```

* The previous step automatically installs the newly built RE into the default folder for dev REs. You can now start Reason Recon and load the rack extension. Note that it will **not** appear in normal Reason. You need to start Reason Recon.

Release notes
-------------

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
