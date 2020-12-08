MYAPP = dcrypt
MYAPPS = dcrypt-static 
MYAPPSRC = dcrypt.c
LDFLAGS = -lgcrypt -lgpg-error
PREFIX = /usr/local

all: dcrypt dcrypt-static

dcrypt: dcrypt.c
	$(RM) $(MYAPP)
	$(CC) $(MYAPPSRC) -o $(MYAPP) $(LDFLAGS)

dcrypt-static: dcrypt.c
	$(RM) $(MYAPPS)
	$(CC) -static $(MYAPPSRC) -o $(MYAPPS) $(LDFLAGS)

install: $(MYAPP)
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	cp $< $(DESTDIR)$(PREFIX)/bin/$(MYAPP)

uninstall:
	rm -f $(DESTDIR)$(PREFIX)/bin/$(MYAPP)

clean:
	$(RM) $(MYAPP) $(MYAPPS)

