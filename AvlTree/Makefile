CXX = g++
CXXFLAGS = -g -Wall -O2 "-Wl,--stack=5120000000"
LDFLAGS =

TARGET = test
SOURCES = test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)
	rm -f report.aux report.log report.toc report.bbl report.blg report.synctex.gz report.out

report:
	xelatex report.tex