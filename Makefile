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
CFLAGS=-I. -I$(PATHU) -I$(PATHS) -DTEST -fPIC # -fPIC only in linux ?

SRCS = $(wildcard $(PATHS)*.c)
SRCT = $(wildcard $(PATHT)*.c)
# make provision for only object files for data structures and not the tests
SRCL = $(filter-out $(PATHS)%test.c, $(SRCS))

OBJS = $(patsubst $(PATHS)%.c, $(PATHO)%.o, $(SRCS))
OBJL = $(patsubst $(PATHS)%.c, $(PATHO)%.o, $(SRCL))
RESULTS = $(patsubst $(PATHT)Test%.c,$(PATHR)Test%.txt,$(SRCT) )

PASSED = `grep -s PASS $(PATHR)*.txt`
FAIL = `grep -s FAIL $(PATHR)*.txt`
IGNORE = `grep -s IGNORE $(PATHR)*.txt`

BUILD_PATHS = $(PATHB) $(PATHD) $(PATHO) $(PATHR) $(PATHL) ctags

test: $(BUILD_PATHS) $(RESULTS)
	@echo "-----------------------\nIGNORES:\n-----------------------"
	@echo "$(IGNORE)"
	@echo "-----------------------\nFAILURES:\n-----------------------"
	@echo "$(FAIL)"
	@echo "-----------------------\nPASSED:\n-----------------------"
	@echo "$(PASSED)"
	@echo "\nDONE"

$(PATHR)%.txt: $(PATHB)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

$(PATHB)Test%.$(TARGET_EXTENSION): $(OBJS) $(PATHO)Test%.o $(PATHO)%.o $(PATHO)unity.o #$(PATHD)Test%.d
	$(LINK) -o $@ $^

$(PATHO)%.o:: $(PATHT)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHS)%.c
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHO)%.o:: $(PATHU)%.c $(PATHU)%.h
	$(COMPILE) $(CFLAGS) $< -o $@

$(PATHD)%.d:: $(PATHT)%.c
	$(DEPEND) $@ $<

$(PATHB):
	$(MKDIR) $(PATHB)

$(PATHD):
	$(MKDIR) $(PATHD)

$(PATHO):
	$(MKDIR) $(PATHO)

$(PATHR):
	$(MKDIR) $(PATHR)

$(PATHL):
	$(MKDIR) $(PATHL)

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
