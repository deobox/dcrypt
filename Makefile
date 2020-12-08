MYAPP = dcrypt
MYAPPS = dcrypts
MYAPPSRC = dcrypt.c
LDFLAGS = -lgcrypt -lgpg-error

all: dcrypt dcrypt-static

dcrypt: dcrypt.c
        $(RM) $(MYAPP)
        $(CC) $(MYAPPSRC) -o $(MYAPP) $(LDFLAGS)

dcrypt-static: dcrypt.c
        $(RM) $(MYAPPS)
        $(CC) -static $(MYAPPSRC) -o $(MYAPPS) $(LDFLAGS)

clean:
        $(RM) $(MYAPP) $(MYAPPS)

