set -ex

clang examples/$1.c src/*.c \
  -I include \
  -I deps/metalang99/include \
  -fmacro-backtrace-limit=0 \
  -o example

./example
