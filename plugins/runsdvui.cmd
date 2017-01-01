cd /d "E:\Documents\Visual Studio 2015\Projects\Learn\plugins" &msbuild "plugins.vcxproj" /t:sdvViewer /p:configuration="Debug" /p:platform=Win32
exit %errorlevel% 