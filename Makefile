include Make.defines

PROGS =	 client server

OPTIONS = -DUNIX  -DUSE_SIGACTION -DANSI


COBJECTS = 
CSOURCES = 

CPLUSOBJECTS = 

COMMONSOURCES =

CPLUSSOURCES =

all:	${PROGS}


client:	passwordBreaker.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(COMMONSOURCES) $(SOURCES)
		${CC} ${LINKOPTIONS}  $@ passwordBreaker.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


server:		passwordServer.o $(CPLUSOBJECTS) $(COBJECTS)
		${CC} ${LINKOPTIONS} $@ passwordServer.o $(CPLUSOBJECTS) $(COBJECTS) $(LIBS) $(LINKFLAGS)


.cc.o:	$(HEADERS)
	$(CPLUS) $(CPLUSFLAGS) $(OPTIONS) $<

.c.o:	$(HEADERS)
	$(CC) $(CFLAGS) $(OPTIONS) $<



backup:
	rm -f passwordBreaker.tar.gz
	tar -cf passwordBreaker.tar *
	gzip -f passwordBreaker.tar

clean:
		rm -f ${PROGS} ${CLEANFILES}

depend:
		makedepend passwordBreaker.c passwordServer.c -I/usr/lib/gcc/x86_64-linux-gnu/4.6/include $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)
#		mkdep $(CFLAGS) $(HEADERS) $(SOURCES) $(COMMONSOURCES) $(CSOURCES)

# DO NOT DELETE

passwordBreaker.o: passwordBreaker.h /usr/include/stdio.h
passwordBreaker.o: /usr/include/features.h /usr/include/stdc-predef.h
passwordBreaker.o: /usr/include/libio.h /usr/include/_G_config.h
passwordBreaker.o: /usr/include/wchar.h /usr/include/xlocale.h
passwordBreaker.o: /usr/include/stdlib.h /usr/include/alloca.h
passwordBreaker.o: /usr/include/signal.h /usr/include/time.h
passwordBreaker.o: /usr/include/errno.h /usr/include/string.h
passwordBreaker.o: /usr/include/netinet/in.h /usr/include/stdint.h
passwordBreaker.o: /usr/include/endian.h /usr/include/arpa/inet.h
passwordBreaker.o: /usr/include/netdb.h /usr/include/rpc/netdb.h
passwordBreaker.o: /usr/include/unistd.h /usr/include/getopt.h
passwordServer.o: passwordBreaker.h /usr/include/stdio.h
passwordServer.o: /usr/include/features.h /usr/include/stdc-predef.h
passwordServer.o: /usr/include/libio.h /usr/include/_G_config.h
passwordServer.o: /usr/include/wchar.h /usr/include/xlocale.h
passwordServer.o: /usr/include/stdlib.h /usr/include/alloca.h
passwordServer.o: /usr/include/signal.h /usr/include/time.h
passwordServer.o: /usr/include/errno.h /usr/include/string.h
passwordServer.o: /usr/include/netinet/in.h /usr/include/stdint.h
passwordServer.o: /usr/include/endian.h /usr/include/arpa/inet.h
passwordServer.o: /usr/include/netdb.h /usr/include/rpc/netdb.h
passwordServer.o: /usr/include/unistd.h /usr/include/getopt.h
