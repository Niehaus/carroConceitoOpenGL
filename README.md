# carroConceitoOpenGL
Carro Conceito em OpenGL

# Install
sudo apt-get install libpng-dev

# Run
g++ -I/usr/include -O2 jato.c -o jato -L/usr/lib -lglut -lGLU -lGL -lm -lpng -L/usr/X11/lib -L/usr/X11R6/lib -lX11
./jato
