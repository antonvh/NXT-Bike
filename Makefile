
# Config
USB=-U

# Path to the NXC compiler relative to the Makefile
NXC=../nxt/nbc
NXTCOM=../nxt/nxtcom

# Options to pass to the compiler
OPTIONS=-Z2 -EF

# Change the name of the program helloworld.rxe to be whatever you want
# to name the final executable
PROGRAM=moto

all: $(PROGRAM).rxe download

$(PROGRAM).rxe: source/$(PROGRAM).nxc Makefile
	cd source;                    \
	../$(NXC) -O=../build/$(PROGRAM).rxe \
				$(OPTIONS) \
		        $(PROGRAM).nxc

download: $(PROGRAM).rxe
	cd build;  \
	../$(NXTCOM) $(USB) $(PROGRAM).rxe
	
clean:
	/bin/rm -vf build/$(PROGRAM).rxe
		   
