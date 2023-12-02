#include <iostream>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include <cstdlib>

void solve(std::ifstream& inputFile);
unsigned short processLine(const std::string& line);
bool isDigit(char c);
unsigned short toDigit(char c);
unsigned short findFirstDigit(const std::string& line);
unsigned short findLastDigit(const std::string& line);


/*
g++ -W p01-1.cpp -o p01-1
*/

int main (int argc, char* argv[]) {

   std::ifstream inputFile;
   std::string pathToFile = "testInput.txt";

   if (argc > 1) {
      pathToFile = std::string(argv[1]);
   }

   inputFile.open(pathToFile, std::ifstream::in);

   if (!inputFile.good()) {
      std::cout << "Failed to read: " << pathToFile << std::endl;
      return EXIT_FAILURE;
   }

   solve(inputFile);

   return EXIT_SUCCESS;
}


void solve(std::ifstream& inputFile) {
   std::string line;
   int sum = 0;
   while (std::getline(inputFile, line)) {
    if (line.size() == 0) {
       continue;
    }
    sum += processLine(line);
   }

   std::cout << sum << std::endl;

}

unsigned short processLine(const std::string& line) {
   unsigned short result = 0L;

/*
  To read indivisual tokens from file
  ---
  Adam English 85
  Charlie Math 76
  Erica History 82
  Richard Science 90
  ---
  // read input
  string input;
  getline(cin, input);

  // initialize string stream
  stringstream ss(input);

  // extract input
  string name;
  string course;
  string grade;

  ss >> name >> course >> grade;
*/


   unsigned short firstDigit = findFirstDigit(line);
   unsigned short lastDigit = findLastDigit(line);
   if (firstDigit == 10 || lastDigit == 10) {
      std::cout << line << std::endl;
      std::cout << "first: "<< firstDigit << std::endl;
      std::cout << "last: "<< lastDigit << std::endl;
   }


   return firstDigit * 10 + lastDigit;
}

const std::vector<std::pair<std::string, short>>tokens = {
    {"1", 1},
    {"2", 2},
    {"3", 3},
    {"4", 4},
    {"5", 5},
    {"6", 6},
    {"7", 7},
    {"8", 8},
    {"9", 9}
};

unsigned short findFirstDigit(const std::string& line) {

   size_t posFirst = std::string::npos;
   short value = 10;

   for (auto token : tokens) {
      size_t found = line.find(token.first);
      if (found != std::string::npos && found < posFirst) {
         posFirst = found;
         value = token.second;
      }
   }

   return value;
}

unsigned short findLastDigit(const std::string& line) {
   size_t posFirst = 0;
   short value = 10;

   for (auto token : tokens) {
      size_t found = line.rfind(token.first);
      if (found != std::string::npos && found >= posFirst) {
         posFirst = found;
         value = token.second;
      }
   }

   return value;
}
