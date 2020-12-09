MYAPP = dcrypt
MYAPPSRC = dcrypt.c
LDFLAGS = -lgcrypt -lgpg-error
PREFIX = /usr/local

all: dcrypt

dcrypt: dcrypt.c
	$(RM) $(MYAPP)
	$(CC) $(MYAPPSRC) -o $(MYAPP) $(LDFLAGS)

static: dcrypt.c
	$(RM) $(MYAPP)
	$(CC) -static $(MYAPPSRC) -o $(MYAPP) $(LDFLAGS) 

install: $(MYAPP)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin/$(MYAPP)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(MYAPP)

clean:
	$(RM) $(MYAPP)

