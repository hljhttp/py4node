set HOME=%~dp0
cd %HOME% /d
call env.bat
start cmd.exe /K "cd /d %HOME% && npm start &&pause"