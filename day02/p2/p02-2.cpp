#include <algorithm>
#include <fstream>
#include <functional>
#include <locale>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

#include <cctype>
#include <cstdlib>

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        if (item.length() > 0) {
            elems.push_back(item);
        }
    }
    return elems;
}
// split string by char
std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}


// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

struct Sample {
   size_t red;
   size_t green;
   size_t blue;
   Sample(size_t red, size_t green, size_t blue) {
      this->red = red;
      this->green = green;
      this->blue = blue;
   }
   Sample() {
      red = green = blue = 0;
   }
   Sample(const std::string& line) : Sample() {
      //std::cout << line << std::endl;
      std::vector<std::string> values = split(line, ',');
      for (auto& v : values) {
        std::string field = trim(v);
        //std::cout << field << std::endl;
        std::size_t found = field.find(" ");
        std::string number = field.substr(0, found);
        std::string color = field.substr(found + 1);
        //std::cout << "number: " << number << std::endl;
        //std::cout << "color: " << color << std::endl;
        switch (color[0]) {
        case 'r':
           red = std::stoi(number);
           break;
        case 'g':
           green = std::stoi(number);
           break;
        case 'b':
           blue = std::stoi(number);
           break;
        }
      }
      //std::cout << "(red: " << red << ", green: " << green << ", blue: " << blue << ")" << std::endl;
   }
};

struct Game {
   size_t id;
   static Sample target;
   std::vector<Sample> samples;
   Game(const std::string& input) {
      std::size_t found = input.find(":");
      const size_t space_pos = 5;
      std::string sid = input.substr(space_pos, found - space_pos);
      //std::cout << sid << std::endl;
      //std::cout << input << std::endl;
      id = std::stoi(sid);
      std::string rest = input.substr(found + 2); // one from colon and other for space
      // Parse the rest of the string
      std::vector<std::string> s_samples = split(rest, ';');
      for (auto& s_sample : s_samples) {
        Sample s(trim(s_sample));
        samples.push_back(s);
      }
   };
   bool isPossible() {
      for (const auto& s : samples) {
         if (!test(s)) {
            return false;
         }
      }
      return true;
   };

   size_t getPower() {
       Sample minimal = calculateMinimal();
       //std::cout << "Minimal: "<< "(red: " << minimal.red << ", green: " << minimal.green <<
       //        ", blue: " << minimal.blue << ")" << std::endl;
       return minimal.red * minimal.green * minimal.blue;
   }

private:
   bool test(const Sample& sample) {
      return sample.red   <= Game::target.red &&
          sample.green <= Game::target.green &&
          sample.blue  <= Game::target.blue;
   };

   Sample calculateMinimal() {
       Sample min;

       for (const auto& s : samples) {
           if (s.red > min.red) {
               min.red = s.red;
           }
           if (s.green > min.green) {
               min.green = s.green;
           }
           if (s.blue > min.blue) {
               min.blue = s.blue;
           }
       }

       return min;
   }
};



void solve(std::ifstream& inputFile);
unsigned short processLine(const std::string& line);


Sample Game::target = {12, 13, 14};

/*
g++ -W p02-2.cpp -o p02-2
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
   size_t answer = 0;

   //Game::target = Sample(12, 13, 14);

   while (std::getline(inputFile, line)) {
    if (line.size() == 0 || line.size() == 1) {
       continue;
    }
    Game game(line);
    answer += game.getPower();
   }

   std::cout << "Answer:\n" << answer << std::endl;

}


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


