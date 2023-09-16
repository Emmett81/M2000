default:
	@echo "To compile M2000, use one of the following:"
	@echo " make x      - Make the Unix/X version"
	@echo " make opengl - Make the Unix/OpenGL version"

x:
	make -f Makefile.X

opengl:
	make -f Makefile.OpenGL

clean:
	rm -f *.o *~

distclean:
	make clean
	rm -f m2000

