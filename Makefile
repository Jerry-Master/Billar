CXX=g++
LIBS=-l sfml-system -l sfml-window -l sfml-graphics -l sfml-audio -l sfml-network
CFLAGS=-Wall -O2 -std=c++11 -I$(LDIR)

IDIR=include
LDIR=lib
ODIR = obj
OBJS = $(patsubst $(LDIR)/%.hpp, $(ODIR)/%.o, $(wildcard $(LDIR)/*.hpp))

main.exe: main.cpp $(OBJS)
	$(CXX) $(CFLAGS) $(LIBS) $^ -o $@

$(ODIR)/%.o: $(IDIR)/%.cpp $(LDIR)/%.hpp
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.exe *.o