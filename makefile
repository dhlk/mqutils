CC := gcc -Wall -Werror
TARGETS := mqopen mqreceive mqsend mqunlink

all: $(TARGETS)

install:
	install -D -t "$(DESTDIR)/$(PREFIX)/bin" $(TARGETS)

clean:
	rm -f $(TARGETS) $(addsuffix .o, $(TARGETS))

$(TARGETS): %: %.o
	$(CC) -lrt -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $^
