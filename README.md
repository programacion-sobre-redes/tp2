# Guía para compilar y ejecutar este TP

Esto es una guía para este trabajo práctico en particular. Ya que tiene una estructura un poco diferente a la de los talleres.

## Targets de CMake disponibles

Recuerden que para compilar un _target_ en particular, deben correr el comando `cmake --build build --target <target>`.

Los targets disponibles son: 

- `main`: Compila el programa principal.
- `tp_tests`: Compila los tests. Si no se compilan los tests, no se pueden correr. No hace falta correrlo manualmente, ya que se corre automáticamente al correr `ctest`.
- `all`: Compila todo. Es lo mismo que correr `cmake --build build`.
- `clean`: Borra los archivos generados por CMake. Es lo mismo que correr `cmake --build build --target clean`.

## Compilación y ejecución

Para compilar el TP, deben correr los siguientes comandos:

```bash
cmake -S . -B build
cmake --build build
```

Esto generará la carpeta `build/` y compilará el programa.

Una vez que hayan compilado el programa, pueden ejecutarlo con el siguiente comando:

```bash
./build/main <entrada> <salida> <n_threads> <filtro_1> ...
```

## Correr los tests

Para correr los tests, deben correr el siguiente comando:

```bash
cmake --build build --target tp_tests
```

Y luego, pueden correr los tests con el siguiente comando **desde la carpeta build**:

```bash
ctest --output-on-failure
```

Esto correrá todos los tests y mostrará el resultado de cada uno. Si alguno falla, se mostrará un mensaje de error con el nombre del test que falló y el motivo del fallo. Si todo sale bien, verán un mensaje que dice `100% tests passed`.
