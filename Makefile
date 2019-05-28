PROG					= gost_test
SOURCES				= gost gost89

DIROBJ    		= obj/
FILEOBJ     	= $(addsuffix .o, $(SOURCES))
PATHOBJ     	= $(addprefix $(DIROBJ), $(FILEOBJ))
CFLAGS				= 
CC						= g++

VPATH = $(DIRSOUR) $(DIROBJ)

.PHONY: all clean objdir

all: objdir Makefile $(PROG)

objdir:
	@rm -Rf $(DIROBJ)
	@mkdir $(DIROBJ)

$(PROG): $(FILEOBJ)
	$(CC) $(CFLAGS) -o $(PROG) $(addprefix $(DIROBJ), $^)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $(DIROBJ)$@

clean:
	@rm -Rf $(PROG)
	@rm -Rf $(DIROBJ)
	@rm -Rf core*

test:
	@openssl enc -aes-256-ecb -k secret -P | grep key | awk '{split($$0, arr, "="); print arr[2]}' | ./$(PROG)
