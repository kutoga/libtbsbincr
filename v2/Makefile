example: example.o

.PHONY: clean

CPPFLAGS=-Wall -Wextra -Werror -O3

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

example:
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@


clean:
	$(RM) example example.o
