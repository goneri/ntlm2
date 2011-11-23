##
##  Makefile -- Build procedure for sample ntlm Apache module
##  Autogenerated via ``apxs -n ntlm -g''.
##
## $Id: Makefile,v 1.3.4.1 2003/02/25 11:25:42 casz Exp $

#   the used tools
APXS=apxs2
APACHECTL=apachectl

#   the default target
all: mod_ntlm.so

#   compile the shared object file
mod_ntlm.so: mod_ntlm.c mod_ntlm.h ntlmssp.inc.c smbval/rfcnb-io.inc.c smbval/rfcnb-util.inc.c smbval/session.inc.c smbval/smbdes.inc.c smbval/smbencrypt.inc.c smbval/smblib-util.inc.c smbval/smblib.inc.c smbval/valid.inc.c smbval/byteorder.h smbval/rfcnb-common.h smbval/rfcnb-error.h smbval/rfcnb-io.h smbval/rfcnb-priv.h smbval/rfcnb-util.h smbval/rfcnb.h smbval/smblib-common.h smbval/smblib-priv.h smbval/std-defines.h smbval/std-includes.h smbval/valid.h
	$(APXS) -c -o mod_ntlm.so -Wc,-shared mod_ntlm.c

#   install the shared object file into Apache 
install: all
	$(APXS) -i -a -n 'ntlm' mod_ntlm.so

#   cleanup
clean:
	rm -f `find . -name \*.o -o -name \*.so -o -name \*~ -o -name \*.slo -o -name \*.lo -o -name \*.la`

#   simple test
test: reload
	lynx -mime_header http://localhost/ntlm

#   install and activate shared object by reloading Apache to
#   force a reload of the shared object file
reload: install restart

#   the general Apache start/restart/stop
#   procedures
start:
	$(APACHECTL) start
restart:
	$(APACHECTL) restart
stop:
	$(APACHECTL) stop
