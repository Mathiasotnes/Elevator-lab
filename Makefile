
EXECUTABLE  = elevator

COMPILER    = clang
CFLAGS      = -Wall -g -std=gnu11 -fsanitize=address
LDFLAGS     = -fsanitize=address
EXCLUDE     = '*test*'


SOURCEDIR = src
DRIVERDIR = driver
OBJECTDIR = build

SOURCES := $(patsubst $(SOURCEDIR)/%, %, $(shell find $(SOURCEDIR) -name '*.c'  ! -name $(EXCLUDE)  ! -path $(EXCLUDE)))
SOURCES += $(patsubst $(DRIVERDIR)/%, %, $(shell find $(DRIVERDIR) -name '*.c'  ! -name $(EXCLUDE)  ! -path $(EXCLUDE)))
SOURCES += main.c
OBJECTS = $(addprefix $(OBJECTDIR)/, $(SOURCES:.c=.o))

all: $(EXECUTABLE) 

rebuild: clean all
	
clean:
	rm -f $(EXECUTABLE)
	rm -rf $(OBJECTDIR)

## executable depends on object files: link them
$(EXECUTABLE): $(OBJECTS) 
	$(COMPILER) $^ -o $@ $(LDFLAGS)

## object files depend on source files: compile them
$(OBJECTDIR)/%.o: $(SOURCEDIR)/%.c
	@mkdir -p $(@D)
	$(COMPILER) -c $(CFLAGS) $< -o $@

$(OBJECTDIR)/%.o: $(DRIVERDIR)/%.c
	@mkdir -p $(@D)
	$(COMPILER) -c $(CFLAGS) $< -o $@

$(OBJECTDIR)/%.o: %.c
	@mkdir -p $(@D)
	$(COMPILER) -c $(CFLAGS) $< -o $@

.PHONY: all rebuild clean
