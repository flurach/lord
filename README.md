<h1 align="center">
	<img src="logo.jpg" width="160px"/>
	<br/>
	Lord
	<br/>
	<i style="font-size: 16px">My pet programming language.</i>
</h1>


## Building

You need to install `premake5`, then do:

```sh
$ premake5 gmake
$ make
```

This builds the `_bin/lord` executable.


## Development

You can read [the docs here](_docs/read-this.md) and if you ever
happen to stuck, we probably have a tutorial for it in [here](_docs/misc/resources.md)!

For the moment, generate your build files:

- windows: `premake5 vs2019`
- linux:   `premake5 gmake`
- mac:     `premake5 xcode4`

You can then use your favoured platform (Visual studio, XCode, Linux etc.)
to build the binaries/libraries. All built files go into ___bin/__.


## Tech stack

- [premake5](https://premake.github.io/): as the build system
- [clang](https://clang.llvm.org/): as the compiler
