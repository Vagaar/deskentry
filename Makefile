CC=gcc
LIBNAME=libdeskentry.a
SOURCES=*.c
OBJCT=$(SOURCES:.c=.o)
INCFILE=deskentry.h
LIBINSTD=/usr/lib/
INCINSTD=/usr/include/

all: objects
	ar cr $(LIBNAME) $(OBJCT)

install:
	@echo "Start installing [$(LIBNAME)] to [$(LIBINSTD)]"
	cp $(LIBNAME) $(LIBINSTD)
	@echo "Start installing [$(INCFILE)] to [$(INCINSTD)]"
	cp $(INCFILE) $(INCINSTD)
	@echo "Installing finished"

uninstall:
	@echo "Start uninstalling [$(LIBNAME)] from [$(LIBINSTD)]"
	rm -f  $(LIBINSTD)$(LIBNAME)
	@echo "Start uninstalling [$(INCFILE)] from [$(INCINSTD)]"
	rm -f  $(INCINSTD)$(INCFILE)
	@echo "Uninstalling finished"

objects:
	$(CC) -c $(SOURCES)

clean:
	rm -f *.o *.a
