include makefile.config
UNAME := $(shell uname)

# will need to get this cleaned
ifeq ($(OSTYPE),cygwin)
	CLEANUP = rm -f
    MKDIR = mkdir -p
    TARGET_EXTENSION=out
	SHARED_LIBRARY_EXTENSION=dll
	SHARED_LIBRARY_FLAG=-shared
else ifeq ($(OS),Windows_NT)
  ifeq ($(shell uname -s),) # not in a bash-like shell
	CLEANUP = del /F /Q
	MKDIR = mkdir
  else # in a bash-like shell, like msys
	CLEANUP = rm -f
	MKDIR = mkdir -p
  endif
	TARGET_EXTENSION=exe
	SHARED_LIBRARY_EXTENSION=dll
    SHARED_LIBRARY_FLAG=-shared
else ifeq ($(UNAME),Linux)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=out
	SHARED_LIBRARY_EXTENSION=so
	SHARED_LIBRARY_FLAG=-shared
else ifeq ($(UNAME),Darwin)
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=out
	SHARED_LIBRARY_EXTENSION=dylib
	SHARED_LIBRARY_FLAG=-dynamiclib
else
	CLEANUP = rm -f
	MKDIR = mkdir -p
	TARGET_EXTENSION=out
	SHARED_LIBRARY_EXTENSION=dylib
	SHARED_LIBRARY_FLAG=-dynamiclib
endif


.PHONY: clean
.PHONY: test

PATHU = unity/src/
PATHS = src/
PATHT = test/
PATHB = build/
PATHD = build/depends/
PATHO = build/objs/
PATHR = build/results/
PATHL = build/lib/

# CC defined in makefile.config
COMPILE=$(CC) -c -g3
LINK=$(CC) -g3
DEPEND=$(CC) -MM -MG -MF
CFLAGS=-Wall -g3 -std=c99 -I. -I$(PATHU) -I$(PATHS) -DTEST -fPIC # -fPIC only in linux ?

# All of the .c files in $(PATHS) = ./src
SRCS = $(wildcard $(PATHS)*.c)
# all of the .c files converted to .o files
OBJS = $(patsubst $(PATHS)%.c, $(PATHO)%.o, $(SRCS))

# All of the .c files in $(PATHT) = ./test
SRCT = $(wildcard $(PATHT)*.c)

# All of the Test*.c files in the test folder $(PATHT)
# Test*.c files are the files for the executable tests
SRCTX = $(wildcard $(PATHT)Test*.c)
# The Test*.c files compile to .o
OBJTX = $(patsubst $(PATHT)%.c, $(PATHO)%.o, $(SRCTX))

# All of the support files in the test folder $(PATHT)
# These are not executable and are just imported by the Test*.c files
SRCTS = $(filter-out $(PATHT)Test%.c, $(SRCT))
# The test support files compiled to .o
OBJTS = $(patsubst $(PATHT)%.c, $(PATHO)%.o, $(SRCTS))

# make provision for only object files for data structures and not the tests
SRCL = $(filter-out $(PATHS)%test.c, $(SRCS))
OBJL = $(patsubst $(PATHS)%.c, $(PATHO)%.o, $(SRCL))

# The txt files that results from the execution of the tests.
RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCTX))

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

# All the paths needed in the build directory
BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR) $(PATHL)

test: unity ctags $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"

# Creates all the results.txt files by executing all the test executables
$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

# Creates the test executables
# Requires
# 1) The test executable object file Text%.o
# 2) All the source object files $(OBJS)
# 3) All the test support object files $(OBJTS)
# 4) Unity object file $(PATHO)unity.o
$(PATHB)Test%.$(TARGET_EXTENSION): $(OBJS) $(OBJTS) $(PATHO)Test%.o  $(PATHO)unity.o # $(PATHO)%.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^

# Rule for compiling all TEST files to object files
$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

unity:
	git clone https://github.com/ThrowTheSwitch/Unity.git unity

# Rule for compiling all SOURCE files to object files
$(PATHO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

# Rule for compiling all Unity files to object files
$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

# Rule for creating depends files for all test source files
$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

# Build path creation
$(PATHB):
	$(MKDIR) $(PATHB)

# Depends path creation
$(PATHD):
	$(MKDIR) $(PATHD)

# Object path creation
$(PATHO):
	$(MKDIR) $(PATHO)

# Results path creation
$(PATHR):
	$(MKDIR) $(PATHR)

# Library path creation
$(PATHL):
	$(MKDIR) $(PATHL)

# Create ctags
ctags: $(SRCS) $(SRCT)
	-@ctags $(SRCS) $(SRCT) > /dev/null 2>&1

clean:
	$(CLEANUP) $(PATHO)*.o
	$(CLEANUP) $(PATHB)*.$(TARGET_EXTENSION)
	$(CLEANUP) $(PATHR)*.txt
	$(CLEANUP) $(PATHL)*.a
	$(CLEANUP) tags

libst: $(PATHL)lib-c-adt.a(${OBJL})

lib-c-adt.$(SHARED_LIBRARY_EXTENSION): $(OBJL)
	$(CC) $(SHARED_LIBRARY_FLAG) -o $(PATHL)$@ $^

#lib.c.adt.a: $(OBJS)
#	ar cr $(PATHL)lib.c.adt.a $(OBJS)

#TestarraylistStatic:
#	gcc -Wl, -Bstatic build/lib/lib-c-adt.a build/objs/data_structures_test.o build/objs/arraylist.o build/objs/list.o build/objs/unity.o build/objs/Testarraylist.o -o build/TalStatic.out

#TestarraylistDynamic:
	# gcc -Wl, -Bdynamic build/lib/lib-c-adt.dylib build/objs/data_structures_test.o build/objs/arraylist.o build/objs/list.o build/objs/unity.o build/objs/Testarraylist.o -o build/TalDylib.out

.PRECIOUS: $(PATHB)Test%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHD)%.d
.PRECIOUS: $(PATHO)%.o
.PRECIOUS: $(PATHR)%.txt
