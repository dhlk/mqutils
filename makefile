CC := gcc -Wall -Werror
TARGETS := mqopen mqreceive mqsend mqunlink

all: $(TARGETS)

clean:
	rm -f $(TARGETS) $(addsuffix .o, $(TARGETS))

$(TARGETS): %: %.o
	$(CC) -lrt -o $@ $^

%.o: %.c
	$(CC) -c -o $@ $^
