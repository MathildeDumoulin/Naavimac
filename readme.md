# Naavimac
## C++ / OpenGL project made for IMAC 3rd Semester

### How-to
You will need some libraries(OpenGL, Glew and SDL2). To compile:
```
mkdir build
cd build
cmake ..
make
./bin/Naavimac
```

To generate documentation, you will need doxygen and graphviz:
```
sudo apt install graphviz doxygen
```
Then go to the build directory and type:
```
cd doc
make html
cd doc-doxygen/html
firefox index.html (or any browser you want, e.g. 'google-chrome')
```