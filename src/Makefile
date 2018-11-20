D=STANDART
NAME=sumTest

run: compile
	for NUMBER in 1 2 3 4; do \
		./$(NAME)STANDARTcurve$$NUMBER 							>> result$(NAME).txt;\
		./$(NAME)PROJECTIVEcurve$$NUMBER						>> result$(NAME).txt;\
		./$(NAME)JACOBIcurve$$NUMBER							>> result$(NAME).txt;\
	done
	make clean

compile: object
	for NUMBER in 1 2 3 4; do \
		g++ $(NAME)STANDARTcurve$$NUMBER.o	 	-o $(NAME)STANDARTcurve$$NUMBER 		-lcryptopp;\
		g++ $(NAME)PROJECTIVEcurve$$NUMBER.o 	-o $(NAME)PROJECTIVEcurve$$NUMBER 		-lcryptopp;\
		g++ $(NAME)JACOBIcurve$$NUMBER.o 		-o $(NAME)JACOBIcurve$$NUMBER 			-lcryptopp;\
	done

object: $(NAME).cpp
	for NUMBER in 1 2 3 4; do \
		g++ $(NAME).cpp -c 			-o $(NAME)STANDARTcurve$$NUMBER.o 		-lcryptopp 	-D STANDART 	-D CURVE$$NUMBER;\
		g++ $(NAME).cpp -c  		-o $(NAME)JACOBIcurve$$NUMBER.o 		-lcryptopp	-D JACOBI		-D CURVE$$NUMBER;\
		g++ $(NAME).cpp -c 			-o $(NAME)PROJECTIVEcurve$$NUMBER.o 	-lcryptopp 	-D PROJECTIVE 	-D CURVE$$NUMBER;\
	done
	
clean:
	rm	-rf *.o
	rm 	-rf *STANDARTcurve*
	rm 	-rf *PROJECTIVEcurve*
	rm 	-rf *JACOBIcurve*


ecdsa: ecdsa.o
	g++ ecdsa.o -o ecdsa$(D) -lcryptopp
	rm -rf *.o
ecdsa.o : ecdsa.cpp
	g++ ecdsa.cpp -c -lcryptopp -D $(D)

sumTest: sumTest.o
	g++ sumTest.o -o sumTest$(D) -lcryptopp
	rm -rf *.o
sumTest.o : ecdsa.cpp
	g++ sumTest.cpp -c -lcryptopp -D $(D)

doublingTest: doublingTest.o
	g++ doublingTest.o -o doublingTest$(D) -lcryptopp
	rm -rf *.o
doublingTest.o : ecdsa.cpp
	g++ doublingTest.cpp -c -lcryptopp -D $(D)

