<p align="center"><img src="logo.jpg" width="160px"/></p>


# Lord

> My pet programming language.


## Building

Generate build files for:

```sh
## windows
premake5 vs2019

## macos
premake5 xcode4

## linux
premake5 gmake
```


## Testing

```sh
# e2e tests
sh tests/e2e/run.sh
```


## Development

You can read [the docs here](docs/README.md) and if you ever
happen to stuck, I probably have a tutorial for it in [here](docs/misc/resources.md).


## Tech stack

- [premake5](https://premake.github.io/): as the build system
- [clang](https://clang.llvm.org/): as the compiler
