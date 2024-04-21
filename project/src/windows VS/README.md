## Dependencies

git

Project needs OpenCV and Tesseract to function.
https://opencv.org/releases/


## Libraries installation tutorial

- Install vcpkg
    - Create a folder for vcpkg (any path should be fine, Documents worked for me)
    - Open it in powershell
    - ```git clone https://github.com/microsoft/vcpkg.git```
    - ```cd .\vcpkg```
    - ```.\bootstrasp-vcpkg.bat```
    - ```.\vcpkg integrate install```
    - ```.\vcpkg install opencv4``` (if doesnt work, search for it first with ```.\vcpkg search opencv4```)
    - ```.\vcpkg install tesseract```
    - done, now every MSBuild C++ project should have access to OpenCV


useful - https://www.youtube.com/watch?v=0h1lC3QHLHU
(CLion automatically has vcpkg plugin, it's easier to use the gui to install libraries)
