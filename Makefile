
GYP = node-gyp

all: test

clean:
	$(GYP) clean

build:
	$(GYP) configure build

test: build
	./node_modules/mocha/bin/mocha -R Progress --compilers coffee:coffee-script --colors

.PHONY: clean build test


