g++:=/opt/homebrew/opt/gcc/bin/g++-12
libs:=-L/opt/homebrew/opt/llvm/lib \
	-L/Users/bent/Projects/mpc/build
includes:=-I/opt/homebrew/opt/llvm/include \
	-I/usr/local/share/mpc

default:
	$(g++) $(libs) $(includes) -lmpc ./test.cpp -o app
