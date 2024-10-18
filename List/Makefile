CXX = g++
CXXFLAGS = -g -Wall
LDFLAGS =

TARGET = List
SOURCES = List.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
	rm -f report.aux report.log report.toc report.bbl report.blg report.synctex.gz report.out

report:
	xelatex report.tex