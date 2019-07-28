# Algorithms Visualized 
Various sorting algorithms visualized using SFML. 

## Prerequisites
SFML needs to be installed, to get SFML on Ubuntu or Debian use:
```
sudo apt-get install libsfml-dev
```
To get CMake, do:
```
sudo apt-get install cmake
```
## Building
Once this repo is unzipped or cloned, do:
```
cmake .
```
This will generate a Makefile, which can be used to compile the source code that will end up in `${PROJECT_SOURCE_DIR}/bin`. After the makefile is generated, run:
```
make
```
Then navigate to the `/bin` directory and execute: `./Algo-Visuals`.

# Acknowledgements
Inspiration/idea for this project came from this [video](https://www.youtube.com/watch?v=67k3I2GxTH8).
