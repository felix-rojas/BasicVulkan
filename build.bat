@echo off

Call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

SET includes=/Isrc /I%VULKAN_SDK%/Include
SET links=/link /LIBPATH:%VULKAN_SDK%/Lib vulkan-1.lib user32.lib
SET defines=/D DEBUG /D WINDOWS_BUILD
SET glslc_path=%~dp0\assets\shaders\glslc.exe
SET shader_path=%~dp0\assets\shaders\

echo "Building..."

cl /EHsc /Z7 /Fe"main" %includes% %defines% src\platform\win32_platform.cpp %links%

echo "Compiling shaders..."
%glslc_path% %shader_path%shader.vert -o %shader_path%shader.vert.spv
%glslc_path% %shader_path%shader.frag -o %shader_path%shader.frag.spv