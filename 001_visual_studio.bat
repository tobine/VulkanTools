set OLDDIR=%CD%
@cd "C:\Program Files (x86)\Microsoft Visual Studio 14.0"
call "Common7\Tools\VsDevCmd.bat"
@set PATH=C:\Program Files\CMake\bin;%PATH%
@date /t
@time /t
cd %OLDDIR%

set VK_INSTANCE_LAYERS=VK_LAYER_LUNARG_device_simulation
set VK_DEVSIM_FILENAME=%CD%\tests\devsim_test1_in_ArrayOfVkFormatProperties.json;%CD%\tests\devsim_test1_in.json
set VK_DEVSIM_DEBUG_ENABLE=1
REM set VK_DEVSIM_EXIT_ON_ERROR=1
REM set VK_LOADER_DEBUG=all

set TGT_DIR=BUILD
cmake -G "Visual Studio 14 Win64" -H. -B%TGT_DIR%
cd %TGT_DIR%
set VK_LAYER_PATH=%CD%\layers\Debug;%CD%\layersvt\Debug;
start VULKAN_TOOLS.sln
