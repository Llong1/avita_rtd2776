@echo off
@if exist "C:\Python27\python.exe" (
    @if exist "..\Tool\precompile\pch_support.py" (
        "C:\Python27\python.exe" -O ..\Tool\precompile\pch_support.py --target %1 --uv_file %2 --scaler_type %3 --keil_root %4
    )
)
