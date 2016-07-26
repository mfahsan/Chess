CXX = g++
CXXFLAGS = -std=c++1y -Wall -MMD -g
EXEC = chess -lX11
OBJECTS = piece.o ai.o grid.o textdisplay.o graphicdisplay.o main.o window.o
POBJECTS = king.o queen.o bishop.o rook.o knight.o pawn.o ai1.o ai2.o ai3.o ai4.o
DEPENDS = ${OBJECTS:.o=.d}
PDEPENDS = ${POBJECTS:.o=.d}

${EXEC}: ${OBJECTS} ${POBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${POBJECTS} -o ${EXEC}

-include ${DEPENDS} ${PDEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${POBJECTS} ${EXEC} ${PDEPENDS} ${DEPENDS}
