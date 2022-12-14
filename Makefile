MKDIR = mkdir -p --
NEXT_AUTO := $(shell find . -maxdepth 1 -type d -regex '.*[0-9]+' -printf '%f\n' | sort -rn | awk '{l=length($$1); printf "%0*d", l, $$1 + 1; exit}')
BASE := cxx

ifndef NEXT_AUTO
NEXT := 001
else
NEXT := $(NEXT_AUTO)
endif

PROBLEMS = $(shell find . -maxdepth 1 -type d -regex '.*[0-9]+')

.PHONY: all clean run next

all:
	(for i in $(PROBLEMS); do (cd "$$i"; $(MAKE) V=$(V)); done)

run:
	(for i in $(PROBLEMS); do (cd "$$i"; $(MAKE) V=$(V) run); done)

clean:
	(for i in $(PROBLEMS); do (cd "$$i"; $(MAKE) V=$(V) clean); done)

next: $(NEXT)

%:
	$(MKDIR) $@
	for i in skel.d/$(BASE)/*; do cp -a "$$i" $@/; done

$(V).SILENT:
