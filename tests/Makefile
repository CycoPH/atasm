# This is the bare beginnings of a regression test suite, it needs work. For
# one thing, we need `known good' binaries to compare with (as it is, we're
# not checking the actual output of atasm at all, just the return value..)

all: test

clean:
	rm -f *.bin *.65o

test:
	@echo ================================================================
	@echo "Test 1: raw output mode"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r testraw.m65 && ../src/verify testraw.bin 0b23672486b8574515a7c7728fad64bc && echo " -- 1 OK"
	@echo
	@echo "Test 2: bad -o option"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -o testraw.m65 || echo " -- 2 OK"
	@echo
	@echo "Test 3: correct -o option"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -otestraw.bin testraw.m65 && ../src/verify testraw.bin 0b23672486b8574515a7c7728fad64bc && echo " -- 3 OK"
	@echo
	@echo "Test 4: missing -u option"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -otestu.bin testu.m65 || echo " -- 4 OK"
	@echo
	@echo "Test 5: correct -u option"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -u -otestu.bin testu.m65 && ../src/verify testu.bin 1087aa68f4bfea8061cc60c4dde9acda && echo " -- 5 OK"
	@echo
	@echo "Test 6: missing -u option, but .OPT ILL in code"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -otestill.bin testill.m65 && ../src/verify testill.bin 1087aa68f4bfea8061cc60c4dde9acda && echo " -- 6 OK"
	@echo
	@echo "Test 7: correct -u option, *and* .OPT ILL in code"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -otestill.bin testill.m65 && ../src/verify testill.bin 1087aa68f4bfea8061cc60c4dde9acda && echo " -- 7 OK"
	@echo
	@echo "Test 8: missing -dfoo=1 on the command line"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -otestdfoo.bin testdfoo.m65 || echo " -- 8 OK"
	@echo
	@echo "Test 9: correct -dfoo=1 on the command line"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -dFOO=1 -otestdfoo.bin testdfoo.m65 && ../src/verify testdfoo.bin 55a54008ad1ba589aa210d2629c1df41 && echo " -- 9 OK"
	@echo
	@echo "Test 10: correct -dfoo=1+1 on the command line"
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -dFOO=1+1 -otestdfoo.bin testdfoo.m65 && ../src/verify testdfoo.bin 9e688c58a5487b8eaf69c9e1005ad0bf && echo " -- 10 OK"
	@echo
	@echo "Test 11: bad .pseudoop in source code."
	@echo "--------"
	cd ../tests && ../src/atasm -v -r -otestunkn.bin testunkn.m65 || echo " -- 11 OK"
	@echo
	@echo "Test 12: "
	@echo "--------"
	cd ../tests && ../src/atasm -oall.bin all.asm && ../src/verify all.bin d5bcde2ecfe2762bdc98ca7ab42222e3 && echo " -- 12 OK"
	@echo
	@echo "Test 13: "
	@echo "--------"
	cd ../tests && ../src/atasm -osin.bin sin.asm && ../src/verify sin.bin bb1defbfd31d446d0720b789d5585e31 && echo " -- 13 OK"
