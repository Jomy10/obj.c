# Obj.c

Object-Oriented programming framework for C.

```C
CLASS(MyClass) {
  int a;
  int b;
}
```

## Compiling and linking

To link and compile the library, only two cflags are needed:
```sh
-I include -I deps/metalang99/include
```

There is only one source file in the library:

```sh
clang src/impl.c -I include -I deps/metalang99/include
```

**Beaver**

The library is also provided as a [Beaver](https://github.com/jomy10/beaver) project, which can be imported in other Beaver projects.

```sh
# Building the library
beaver
```

<!--TODO: pkgconfig-->

## Examples

There are some examples in the [examples](examples) directory.

## License

MIT License
