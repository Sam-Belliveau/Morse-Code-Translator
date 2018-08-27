#ifndef MORSECODE_H
#define MORSECODE_H

#include <cstdint> // Data Types
#include <array> // Arrays

// This Is The Most Amount Of
// Dots And Dashes A Letter Can Have
#define LETTER_LENGTH 5

// Used To Encode Morse Code
enum MorseCode
{ End, Dot, Dash };

// Used To Store A Letter In Morse Code
class MorseLetter
{
public: // Methods
  MorseLetter(const std::array<char, LETTER_LENGTH>& input);
  MorseLetter(const char* input);
  MorseLetter(const char& input);

  void set(const MorseLetter& input);
  bool equals(const MorseLetter& b);

  char getLetter();

  void printMorse();

public: // Variables
  std::array<MorseCode, LETTER_LENGTH> data;
};

// Used To Store The Dictionary
struct dictionary_t
{
  char letter;
  MorseLetter translation;
};

// This Is Used For Translation
const dictionary_t dictionary[37] =
{
  // 0x00
  { ' ', "     " },

  // 0x01
  { 'A', ".-" },    { 'B', "-..." },  { 'C', "-.-." },
  { 'D', "-.." },   { 'E', "." },     { 'F', "..-." },
  { 'G', "--." },   { 'H', "...." },  { 'I', ".." },
  { 'J', ".---" },  { 'K', "-.-" },   { 'L', ".-.." },
  { 'M', "--" },    { 'N', "-." },    { 'O', "---" },
  { 'P', ".--." },  { 'Q', "--.-" },  { 'R', ".-." },
  { 'S', "..." },   { 'T', "-" },     { 'U', "..-" },
  { 'V', "...-" },  { 'W', ".--" },   { 'X', "-..-" },
  { 'Y', "-.--" },  { 'Z', "--.." },

  // 0x1b
  { '0', "-----" },
  { '1', ".----" },
  { '2', "..---" },
  { '3', "...--" },
  { '4', "....-" },
  { '5', "....." },
  { '6', "-...." },
  { '7', "--..." },
  { '8', "---.." },
  { '9', "----." }
};

// This Is Used To Quickly Get The Index Of A Letter
std::size_t charToIndex(const char& input);

// This Is Used To Detect Weather Its Ascii Or Morse Code
bool isAscii(const char* input);
bool isMorse(const char input);

// This Is Needed For Conversion
template<class T, std::size_t L>
void clearArray(std::array<T, L>& array, const T value = 0);

// This Is Used To Convert Text From One To Another
void morseToAscii(const char* input);
void asciiToMorse(const char* input);


#endif
