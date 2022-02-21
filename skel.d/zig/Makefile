PROG := $(shell basename "$$PWD")

FROM := $(shell printf '%s\n' "$(PROG)" | awk '{l=length($$1); printf "%0*d", l, $$1 - 1; exit}')

SOURCES := $(wildcard src/*.zig)

MKDIR ?= mkdir -p --
RM := rm -rf --

.PHONY: all run check edit clean import

all: $(PROG)

$(PROG): $(SOURCES)
	zig build

run: $(PROG)
	./zig-out/bin/$(PROG)

check: $(SOURCES)
	zig test $^

edit:
	vis '+vsplit src/main.zig' Makefile

clean:
	$(RM) zig-out zig-cache src/zig-cache

import:
	$(RM) ./*
	for i in ../$(FROM)/*; do cp "$$i" .; done

$(V).SILENT:
