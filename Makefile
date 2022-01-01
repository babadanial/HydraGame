CXX = g++
CXXFLAGS = -std=c++14 -g -O0 -Wall -MMD -Werror=vla -Wpedantic
OBJECTS = card.o deck.o player.o hydraController.o hydraModel.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = hydra

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

%.o : %.cc
	${CXX} ${CXXFLAGS} -c $< 

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
