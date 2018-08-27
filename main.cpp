#include <iostream>
#include <cstdint>
#include <array>
#include "MorseCode.h"

void badUsage(int &argc, char** &argv)
{
  std::cout << argv[0] << ": bad usage\n";
  std::cout << "Try \'" << argv[0] << " --help\' for more information.\n";
}

bool checkString(const char* a, const char* b)
{
  for(std::size_t i = 0; true; i++)
  {
    if(a[i] != b[i])
    { return false; }

    if(a[i] == '\0' && b[i] == '\0')
    { break; }
  }

  return true;
}

int main(int argc, char** argv)
{
  if(argc == 1 || argc > 3)
  {
    badUsage(argc, argv);
  } else
  {
    if(checkString(argv[1], "-h") || checkString(argv[1], "--help"))
    {
      std::cout << "\n  -h, --help                        Displays Available Options \n";
      std::cout << "  -l, --list                        Displays Morse Code Translation Table \n\n";

      std::cout << "    Inputs Must Have Quotation Marks Around Them\n";
      std::cout << "    Use '.' For Dots, '-' For Dashes, And '/' For Spaces\n";
      std::cout << "  -t, --translate <input>           Automaticly Translates Input \n";
      std::cout << "  -e, --english <input>             Translates English into Morse Code \n";
      std::cout << "  -m, --morse <input>               Translates Morse Code into English \n";
    } else if(checkString(argv[1], "-l") || checkString(argv[1], "--list"))
    {
      std::cout << "Translation Table:\n";
      for(dictionary_t item : dictionary)
      {
        if(item.letter != ' ')
        {
          std::cout << "  " << item.letter << ": ";
          for(std::size_t j = 0; j < LETTER_LENGTH; j++)
          {
            if(item.translation[j] == ' ')
            { break; }
            printf("%c", item.translation[j]);
          }
          std::cout << "\n";
        } else {
          std::cout << "  Space: /\n";
        }
      }
    } else if(argc == 3)
    {
      if(checkString(argv[1], "-t") || checkString(argv[1], "--translate"))
      {
        if(isAscii(argv[2]))
        {
          std::cout << "English text detected.\n";
          asciiToMorse(argv[2]);
        } else
        {
          std::cout << "Morse Code detected.\n";
          morseToAscii(argv[2]);
        }
      } else if(checkString(argv[1], "-e") || checkString(argv[1], "--english"))
      {
        asciiToMorse(argv[2]);
      } else if(checkString(argv[1], "-m") || checkString(argv[1], "--morse"))
      {
        morseToAscii(argv[2]);
      }
    } else
    {
      badUsage(argc, argv);
    }
  }

  std::cout << std::endl;
  return 0;
}
