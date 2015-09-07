CC=gcc
OPTIONS=-Wall


if_rate		:if_rate.c
		$(CC) $(OPTIONS) if_rate.c -o if_rate;
		@echo -e 'You can type "make install" for instalation\n'

install		:
		@if ! cp -i if_rate /sbin/;then \
		echo -e 'Cannot copy "bin/if_rate" to "/sbin/", maybe you are not root\n';\
		else echo -e 'The program can be runed with "/sbin/if_rate"';\
		fi
		@echo
		
#Remove -m32 if you build on 64bits and don't have coss-compile libs	
static		:
		$(CC) $(OPTIONS) -m32 -march=i386 -static if_rate.c -o static_build_ia32/if_rate	
		@echo "See static_build/if_rate"
	
clean		:
		rm -f if_rate

