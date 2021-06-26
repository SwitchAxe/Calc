.SILENT:
.PHONY: bin clean test run

bin:
	gcc main.c lib/calc.c lib/stack.c lib/queue.c -Ilib -g -o calc

test:
	gcc tests.c lib/calc.c lib/test.c lib/test_calc.c lib/queue.c lib/stack.c -Ilib -o tests && ./tests
	
clean:
	rm -f calc tests

run:
	./calc '4+5'
