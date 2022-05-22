# dummy-shell

Shell extendido de una versión trabajada en clase que soporta procesos en _background_

Trabajo realizado para el curso de sistemas operativos del periodo 2022-01 de la universidad del valle

Basado en un recurso propisiado por el profesor [John Sanabria](john.sanabria@correounivalle.edu.co) adaptado de [programiz](https://www.programiz.com/c-programming/c-strings)

## Autores 
_Forman parte de nuetro equipo:_
**Víctor Sapuyes** - [victor262108](https://github.com/victor262108) - 201925711 
**Kevin Marín** - [UserGit](https://github.com/) - 20


## Como compilar
Ubicarse en la carpeta donde se han guardado los archivos .c y .h del repositorio.

Compilar leercadena.c
`gcc -c leercadena.c`

Compilar dummy-shell.c
`gcc dummy_shell.c leercadena.o -o dummy_shell`

Ejecutar
`./dummy_shell`
