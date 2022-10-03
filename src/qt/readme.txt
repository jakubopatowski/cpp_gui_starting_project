Example of launch.json to run app in visual code


{
    // Use IntelliSense to learn about possible attributes.
    // Hover to view descriptions of existing attributes.
    // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
    "version": "0.2.0",
    "configurations": [
        {
            "name": "qt-example launch",
            "type": "cppvsdbg",
            "request": "launch",
            "program": "${workspaceFolder}/out/build/windows-msvc-debug-developer-mode/src/qt/qt-example.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}/out/build/windows-msvc-debug-developer-mode/src/qt",
            "environment": [
                {
                    "name": "PATH",
                    "value": "d:/Qt5/5.14.2/msvc2017_64/bin;${env:PATH}"
                }
            ],
            "console": "externalTerminal",
            "visualizerFile": "c:\\Users\\jakubo\\AppData\\Roaming\\Code\\User\\workspaceStorage\\590839171c5800c40569008bdafe994a\\tonka3000.qtvsctools\\qt.natvis.xml"
        }
    ]
}