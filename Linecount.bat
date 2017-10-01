@echo off
cls
echo FTec Linecount funfrenzy
echo[
echo ftec-core:
Powershell.exe "(gci ftec-core/ -recurse -include *.cpp, *.h, *.glsl, *.xml | cat).Count"
echo[
echo ftec-ui:
Powershell.exe "(gci ftec-ui/ -recurse -include *.cpp, *.h, *.glsl, *.xml | cat).Count"
echo[
echo ftec-util:
Powershell.exe "(gci ftec-util/ -recurse -include *.cpp, *.h, *.glsl, *.xml | cat).Count"
echo[
echo ftec-testgame:
Powershell.exe "(gci ftec-testgame/ -recurse -include *.cpp, *.h, *.glsl, *.xml | cat).Count"
echo[
echo Total lines:
Powershell.exe "(gci ftec*/ -recurse -include *.cpp, *.h, *.glsl, *.xml | cat).Count"
echo[
echo[
echo[
echo[
pause