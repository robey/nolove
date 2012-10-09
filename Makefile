
GYP = node-gyp
LLVM_HOME ?= /usr/local/llvm

all: test

clean:
	$(GYP) clean

build:
	$(GYP) configure build --llvm-home=$(LLVM_HOME)

test: build
	./node_modules/mocha/bin/mocha -R Progress --compilers coffee:coffee-script --colors

.PHONY: clean build test
