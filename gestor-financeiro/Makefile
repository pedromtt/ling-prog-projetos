CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++98 # usando c++98
TARGET = programa

# arquivos objeto (.o) que serão gerados
OBJS = main.o ativo.o sistema.o registro.o

# compila o executavel final
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# compilar cada arquivo individualmente
main.o: main.cpp ativo.h sistema.h registro.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ativo.o: ativo.cpp ativo.h
	$(CXX) $(CXXFLAGS) -c ativo.cpp

sistema.o: sistema.cpp sistema.h
	$(CXX) $(CXXFLAGS) -c sistema.cpp

registro.o: registro.cpp registro.h
	$(CXX) $(CXXFLAGS) -c registro.cpp

# limpar os arquivos gerados
clean:
	rm -f $(OBJS) $(TARGET)