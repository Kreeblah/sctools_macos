
DIRS = scas scdis scboot scinfo scrd scwr

all :
	for d in $(DIRS); do (cd ../../$$d; $(MAKE) OS=$(OS) ); done

clean :
	for d in $(DIRS); do (cd ../../$$d; $(MAKE) OS=$(OS) clean ); done


