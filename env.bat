set HOME=%~dp0
cd %HOME% /d
call node-v8.9.4-win-x64\nodevars.bat
set AnacondaHome=%HOME%..\Miniconda2
set PATH=%AnacondaHome%\DLLs;%AnacondaHome%\Scripts;%AnacondaHome%;%AnacondaHome%\Library\bin;%AnacondaHome%\share\glew\bin;%AnacondaHome%\share\gstreamer\bin;%AnacondaHome%\share\sdl2\bin;%AnacondaHome%\share\gstreamer\libexec\gstreamer-1.0;%PATH%
set PYTHONPATH=%AnacondaHome%\Lib;%AnacondaHome%\Lib\site-packages;%AnacondaHome%\DLLs;
echo ----------------------------------------------------------------------
echo PATH:
echo %PATH%
echo **********************************************************************
echo PYTHONPATH:
echo %PYTHONPATH%
echo ----------------------------------------------------------------------