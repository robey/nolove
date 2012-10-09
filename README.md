
nolove
======

nolove is a binding for LLVM (libllvm) into node/v8.

## LLVM

[LLVM](http://en.wikipedia.org/wiki/LLVM) is the bottom half of a compiler.
If you hand it a partially-compiled diagram of code, it will finish compiling
and optimizing the code into something that's natively executable.

If you want to play around with little languages, or you would like to perform
JIT-style compilation of code that you've generated at runtime, libllvm is the
tool.

## Building

nolove uses gyp, with an included Makefile for running tests.

before it will build, you need to build and install libllvm. i use a configure
command like

    $ ./configure --prefix=$HOME/llvm

so that it installs into a special folder that i use only for this library,
but that isn't necessary. any installation folder should work.

after installing llvm, set your `LLVM_HOME` and build nolove:

    $ export LLVM_HOME=$HOME/llvm
    $ make test

## Using

the best example so far is the last unit test, which builds a small function
(to double a number), compiles it, and calls it, verifying that 10.0 is
doubled to 20.0.

the mapping of libllvm function names into javascript follows these rules:

- all function names are converted to "studlyCaps", which only affects a few
  functions that are still in windows "CapsFirst" form.
- any function in the global namespace that takes an `LLVMContext` or
  `Module` as its first parameter is converted to a method on `Context` or
  `Module`, to simplify the namespace.
- every other global function is inside `llvm`, and every other method is
  attached to the same class as in libllvm.

the bindings are very incomplete as of october 2012, so please submit patches
to fill in anything you miss, or file a github issue. i plan to fill them in
as i need them, but it won't hurt to pester me if you want to adjust my
priority order. :)

## Tests

there need to be more tests. it's tricky to test the bindings without testing
actual llvm functionality, but that's not really a good excuse.

## Internals

this section is just for people who want to hack on the bindings.

each libllvm class has a corresponding class in nolove -- for example,
`llvm::Module` is `LModule`. each libllvm object is wrapped inside a nolove
object, and the nolove object also contains the javascript object.

    LModule::module() // -> llvm::Module *
    LModule::handle_  // -> v8::Object

two fields on the javascript object are used to point back to the libllvm
object and the nolove object, so you can always go back and forth between the
javascript object and the nolove object.

each nolove wrapper class also contains a static `proto` field, which is the
javascript prototype used to create new js objects of the right type. i try to
mirror the libllvm class inheritance in javascript by chaining prototypes.

in v8, a "class" is really a `FunctionTemplate`. the function template is a
container for a `Function`, but functions can only be called and can only be
inspected very lightly. the `FunctionTemplate` is what generates new objects.
`FunctionTemplate` has a `PrototypeTemplate` for adding items to the
prototype.

node adds `ObjectWrap` which keeps a persistent reference to a javascript
object, and uses internal field 0 to store the c++ "this" pointer. nolove's
`NodeWrapped` extends that to store the native llvm object in internal field
1.

## License

nolove is copyright 2012 robey pointer <robeypointer@gmail.com>, and released
under the Apache 2 license, which is included in this package in the file
"LICENSE".
