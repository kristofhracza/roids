# :syringe: Roids
The common man's injector

## Usage
1. Start `roids.exe`
2. Enter the *PID* of the target process
3. Press the `Inject DLL` button and select your file

## Find PID of a process
```powershell
# PROCESSNAME is `notepad` in this case
ps | findstr <PROCESSNAME>

# You will need the 6th number (22100)
239      14     3124      15124       0.11  22100   3 notepad
```

## Compiling from source
Open `roids.sln` in Visual Studio 2022, set build configuration to `Release | x64`.      
Press Build solution and you should receive `roids.exe` file.
