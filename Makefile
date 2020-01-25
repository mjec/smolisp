# Metadata
METAPATH=$(abspath ./metadata.make)
-include $(METAPATH)
APPDATE=$(shell date -d "$$(stat --printf "%y" $(METAPATH))" "+%d %B %Y")

# Paths
PREFIX=/usr/local
SRCDIR=$(abspath ./src)
INCDIR=$(abspath ./include)
DISTDIR=$(abspath ./dist)
BINPATH=$(DISTDIR)/bin/$(APPNAME)

# Source files
SRCS=$(shell find $(SRCDIR) -name '*.c')
HEADERS=$(shell find $(INCDIR) -name '*.h')

# Derived filenames
OBJS=$(SRCS:.c=.o)
PREREQUISITES=$(SRCS:.c=.d)

# Compiler options
ifeq ($(origin CC),default)
CC=clang
endif
WARNINGFLAGS=-Wall -Wshadow -Wwrite-strings -Wmissing-prototypes -Wimplicit-fallthrough -pedantic -fstack-protector-all -fno-strict-aliasing
DEFINEFLAGS=-DAPPNAME=\"$(APPNAME)\" -DAPPVERSION=\"$(APPVERSION)\"
INCLUDEFLAGS=-iquote $(INCDIR)
LDLIBS=

# Derived compiler options
CFLAGS:=$(INCLUDEFLAGS) $(DEFINEFLAGS) $(WARNINGFLAGS) $(CFLAGS)
LDFLAGS:=$(WARNINGFLAGS) $(DEFINEFLAGS) $(LDFLAGS)

# Release build targets
.PHONY: all
all: debug

.PHONY: release
release: CFLAGS:=-O3 $(CFLAGS)
release: LDFLAGS:=-O3 -s $(LDFLAGS)
release: $(BINPATH)

.PHONY: clean
clean: cleandep cleanobj cleandist

# Development build targets
.PHONY: debug
debug: CFLAGS:=-g -DDEBUG $(CFLAGS)
debug: LDFLAGS:=-g -DDEBUG $(LDFLAGS)
debug: $(BINPATH)

.PHONY: lint
lint:
	clang-tidy --fix $(SRCS) -- $(INCLUDEFLAGS) $(DEFINEFLAGS)

.PHONY: format
format:
	clang-format -style=file -i $(SRCS) $(HEADERS)

# Invidiual source file targets
$(BINPATH): $(OBJS)
	mkdir -p $(DISTDIR)/bin
	$(CC) -o $(BINPATH) $(OBJS) $(LDFLAGS) $(LDLIBS)

-include $(PREREQUISITES)

%.d: %.c
	$(CC) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@


# Cleanup targets
.PHONY: cleandist
cleandist:
	$(RM) -rf $(DISTDIR)

.PHONY: cleandep
cleandep:
	$(RM) $(PREREQUISITES)

.PHONY: cleanobj
cleanobj:
	$(RM) $(OBJS)
