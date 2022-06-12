
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

all: $(BINDIR)/static/libiffy.a $(BINDIR)/shared/libiffy.so test_iffy

test_iffy: $(BINDIR)/static/libiffy.a $(OBJECTS_TESTS)
	$(MD) $(dir $@)
	$(CC) -o $@ $^ $(LDFLAGS)

$(BINDIR)/static/libiffy.a: $(OBJECTS)
	$(MD) $(dir $@)
	$(AR) rcs $@ $^

$(BINDIR)/shared/libiffy.so: $(OBJECTS)
	$(MD) $(dir $@)
	$(CC) -shared -o $@ $^

$(OBJDIR)/%.o: %.c
	$(MD) $(dir $@)
	$(CC) -c -o $@ $(CFLAGS) $<

.PHONY: clean

clean:
	rm -rf $(OBJDIR); \
	rm -f test_iffy; \
	rm -rf $(BINDIR)

