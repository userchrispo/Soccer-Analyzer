CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra
INCLUDES = -Isrc/main -Isrc/inputOuput -Isrc/model -Isrc/statsF -Isrc/rankings \
	-Isrc/season -Isrc/analytics -Isrc/report

SRCS = src/main/main.cpp src/inputOuput/io.cpp src/statsF/stats.cpp \
	src/rankings/rankings.cpp src/season/season.cpp src/analytics/analytics.cpp \
	src/report/report.cpp

TARGET = soccer-analyzer

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(SRCS)

.PHONY: clean run
clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)
