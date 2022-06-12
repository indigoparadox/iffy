
# vim: ft=make noexpandtab

BINDIR := bin
OBJDIR := obj

OBJECTS := $(OBJDIR)/src/iffy.o
OBJECTS_TESTS := \
	$(OBJDIR)/tests/check.o \
	$(OBJDIR)/tests/chkiffy.o

MD=mkdir -v -p

CFLAGS := -Wall -Werror

test_iffy: LDFLAGS += $(shell pkg-config --libs check) -L$(BINDIR)/static/ -liffy
test_iffy: CFLAGS += -DCHECK -g

all: iffy

test_iffy: $(OBJECTS) $(OBJECTS_TESTS)
	$(MD) $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

iffy: $(OBJECTS)
	$(MD) $(dir $@)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: %.c
	$(MD) $(dir $@)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean

clean:
	rm -rf $(OBJDIR); \
	rm -f test_iffy; \
	rm -rf $(BINDIR)

