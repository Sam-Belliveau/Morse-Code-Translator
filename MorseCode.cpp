#include "MorseCode.h"

/*** Class Stuff ***/
MorseLetter::MorseLetter(const std::array<char, LETTER_LENGTH>& input)
{
  for(std::size_t i = 0; i < LETTER_LENGTH; i++)
  {
    if(input[i] == '.')
    { data[i] = MorseCode::Dot; }
    else if(input[i] == '-')
    { data[i] = MorseCode::Dash; }
    else { data[i] = MorseCode::End; }
  }
}

MorseLetter::MorseLetter(const char* input)
{
  for(std::size_t i = 0; i < LETTER_LENGTH; i++)
  {
    if(input[i] == '.')
    { data[i] = MorseCode::Dot; }
    else if(input[i] == '-')
    { data[i] = MorseCode::Dash; }
    else { data[i] = MorseCode::End; }
  }
}

MorseLetter::MorseLetter(const char& input)
{
  const std::size_t index = charToIndex(input);
  set(dictionary[index].translation);
}



void MorseLetter::set(const MorseLetter& input)
{
  for(std::size_t i = 0; i < LETTER_LENGTH; i++)
  { data[i] = input.data[i]; }
}

bool MorseLetter::equals(const MorseLetter& b)
{
  for(std::size_t i = 0; i < LETTER_LENGTH; i++)
  {
    if(data[i] != b.data[i])
    { return false; }

    if(data[i] == MorseCode::End && b.data[i] == MorseCode::End)
    { return true; }
  }

  return true;
}



void MorseLetter::printMorse()
{
  for(std::size_t i = 0; i < LETTER_LENGTH; i++)
  {
    if(data[i] == MorseCode::Dot)
    {
      printf(".");
    } else if(data[i] == MorseCode::Dash)
    {
      printf("-");
    } else if(data[i] == MorseCode::End)
    {
      return;
    }
  }
}

char MorseLetter::getLetter()
{
  for(dictionary_t test : dictionary)
  {
    if(equals(test.translation))
    {
      return test.letter;
    }
  }

  return '?';
}



/*** Letter Conversion ***/
std::size_t charToIndex(const char& input)
{
  if(input >= 'A' && input <= 'Z')
  {
    return 0x01 + (input - 'A');
  } else if(input >= 'a' && input <= 'z')
  {
    return 0x01 + (input - 'a');
  } else if(input >= '0' && input <= '9')
  {
    return 0x1b + (input - '0');
  } else { return 0x00; }
}



/*** Letter Detection ***/
bool isAscii(const char* input)
{
  // Used To Check If A Letter Is Valid
  const char morseLetters[4] = ".-/";
  std::size_t asciiCount = 0, morseCount = 0;

  for(std::size_t i = 0; input[i] != '\0'; i++)
  {
    for(char letter : morseLetters)
    {
      if(input[i] == letter)
      { morseCount++; }
    }

    if(charToIndex(input[i]) != 0x00)
    { asciiCount++; }
  }

  return asciiCount >= morseCount;
}

bool isMorse(const char input)
{ return input == ' ' || input == '.' || input == '-' || input == '/'; }


/*** Conversion ***/
template<class T, std::size_t L>
void clearArray(std::array<T, L>& array, const T value)
{
  for(std::size_t i = 0; i < L; i++)
  { array[i] = value; }
}

void morseToAscii(const char* input)
{
  for(std::size_t i = 0; input[i] != '\0'; i++)
  {
    if(!isMorse(input[i]))
    {
      printf("Error: Invalid Character '%c'\n", input[i]);
    }
  }

  printf("Translation: ");

  std::array<char, LETTER_LENGTH> buffer;
  std::size_t count = 0;

  clearArray(buffer);
  for(std::size_t i = 0; input[i] != '\0'; i++)
  {
    switch(input[i])
    {
    case ' ':
      if(count != 0)
      {
        printf("%c", MorseLetter(buffer).getLetter());
        clearArray(buffer);
        count = 0;
      }
      break;

    case '/':
      printf(" ");
      count = 0;
      break;

    case '.':
    case '-':
      buffer[count++] = input[i];
      break;
    }
  }

  if(count != 0)
  { printf("%c", MorseLetter(buffer).getLetter()); }

  printf("\n");
}

void asciiToMorse(const char* input)
{
  printf("Translation: ");

  for(std::size_t i = 0; input[i] != '\0'; i++)
  {
    if(input[i] == ' ')
    { printf("/ "); }
    else
    {
      if(charToIndex(input[i]) != 0)
      {
        MorseLetter(input[i]).printMorse();
        printf(" ");
      }
    }
  }

  printf("\n");
}
