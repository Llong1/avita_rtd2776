@REM ".\Tool\build\link.bat" "$K" !P @L
@set PATH="%1C51\bin";%PATH%
@"Tool\build\auto_link.exe" --uv "%2" --target "%3" --opt 3 --sort --hex2bin ".\HexToBin.exe"
