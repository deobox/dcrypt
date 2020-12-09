MYAPP = dcrypt
MYAPPSRC = dcrypt.c
LDFLAGS = -lgcrypt -lgpg-error
PREFIX = /usr/local/bin

all: dcrypt

dcrypt: $(MYAPPSRC) 
	$(RM) $(MYAPP)
	$(CC) $(MYAPPSRC) -o $(MYAPP) $(LDFLAGS)

static: $(MYAPPSRC)
	$(RM) $(MYAPP)
	$(CC) -static $(MYAPPSRC) -o $(MYAPP) $(LDFLAGS) 

install: $(MYAPP)
	mkdir -p $(PREFIX)
	cp $< $(PREFIX)/$(MYAPP)

uninstall:
	$(RM) $(PREFIX)/$(MYAPP)

clean:
	$(RM) $(MYAPP)

