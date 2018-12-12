# carroConceitoOpenGL
Carro Conceito em OpenGL

# Install
sudo apt-get install libpng-dev

# Run

```cpp
make carro
./carro 
```

ou então:

```cpp
g++ -I/usr/include -O2 carro.c -o carro -L/usr/lib -lglut -lGLU -lGL -lm -lpng -L/usr/X11/lib -L/usr/X11R6/lib -lX11

./carro
 
```


