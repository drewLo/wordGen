/*
  Word Gen v1.0
  Author: Drew Lough <drew.lough@gmail.com>
  A procedural word generator.
*/

//#include "phonemes.hpp"

#include <cstring>

#include <iostream>
#include <vector>
#include <string>
#include <random>

using std::vector;
using std::string;

namespace settings
{
     struct option {
          int length;
          int reps;
     };
     struct state {
    int current_phoneme_type;
    bool previous;
     };
}

vector<string> consonant = {"b","c","ch","d",
                            "f","g","gh","h",
                            "j","k","l","m","n","ng"
                            "p","ph","qu","r","s","sh","t","th",
                            "v","w","x","y","z"};

vector<string> vowel = {"a","ae","ah","ai",
                        "e","ee","ei",
                        "i","ie",
                        "o","oh","oo",
                        "u"};

int get_random_value(const int& min, const int& max)
{
     std::random_device r;
     std::default_random_engine eng(r());
     return std::uniform_int_distribution<int> {min, max} (eng);
}

string random_consonant()
{
     return consonant.at(get_random_value(0,consonant.size() - 1));
}

string random_vowel()
{
     return vowel.at(get_random_value(0,vowel.size() -1));
}

string get_first()
{
     string first_phoneme;
     int flip = get_random_value(1,2);
     if (flip == 1) {
          first_phoneme = random_consonant();
     } else if (flip == 2) {
          first_phoneme = random_vowel();
     }
     return first_phoneme;
}

string get_random_phoneme(settings::state& s)
{
     string phoneme;
     if (s.previous) {
          phoneme = random_consonant();
          s.previous = false;
     } else {
          phoneme = random_vowel();
          s.previous = true;
     }
     return phoneme;
}

vector<string> gen_word(const settings::option& o,
                        settings::state& s)
{
     vector<string> word;
     string phoneme;
     for (int i = 0; i < o.length; ++i){
          phoneme = get_random_phoneme(s);
          word.push_back(phoneme);
     }
     return word;
}

void print(const vector<string>& word){
     for (const auto& w : word) {
          std::cout << w;
     }
     std::cout << '\n';
}

static void usage(const char* name)
{
     std::cerr << "Usage: " << name << " [-h] [-r # repetitions] [-l # phonemes]\n";
}

static void help(const char* name)
{
     usage(name);
     std::cerr << R"bar(
Options:
  -h   Show this text.
  -r   Set a number of repetitions. (output multiple words).
  -l   Set a specific length of word (number of phonemes).

)bar";
     exit(0);
}

void show_error(const std::string& prompt, const char* name)
{
     std::cerr << prompt << '\n';
     usage(name);
     exit(-1);
}

// A command line argument expecting a numeric value is 'valid' if 2 characters or less.
bool is_valid_arg(const char* value) {
     return std::strlen(value) < 2;
}

int main(int argc, char** argv)
{
     settings::option opt;
     settings::state state;

     // Let default word length in # of phonemes && default reps.
     opt.length = get_random_value(2,7);
     opt.reps = 1;
     
     // argument parsing.
     for (int i = 1; i < argc; ++i) {
          if (!std::strcmp(argv[i], "-h")) {
               help(*argv);
          } else if (!std::strcmp(argv[i], "-r")) {
               ++i;
               if (i < argc && is_valid_arg(argv[i])) {
                    opt.reps = std::atoi(argv[i]);
               } else {
                    show_error("Error using -r flag: please enter a valid number (<10).", *argv);
               }
          } else if (!std::strcmp(argv[i], "-l")) {
               ++i;
               if (i < argc && is_valid_arg(argv[i])) {
                    opt.length = std::atoi(argv[i]);
               } else {
                    show_error("Error using -l flag: please enter a valid number (<10).", *argv);
               }
          } else {
               show_error("Error, unrecognized option.", *argv);
          }
     }

     for (int i = 0; i < opt.reps; ++i) {
          auto word = gen_word(opt, state);
          print(word);
     }

     return 0;
}
