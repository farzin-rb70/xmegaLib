#include "PersianReshaper.h"

bool isFromTheSet1(unsigned char ch)
{
  const unsigned char theSet1[47] = {
      32, '\0', 199, 194, 207, 208, 209, 210,
      184, 168, 191, 40, 41, 46, 33, 44, 58, 248, 33, 10,
      45, 35, 43, 34, 39, 37, 42, 95, 64, 36, 94, 38,
      44,47,59,60,62,61,63,91,93,92,96,123,125,126,124};
  int i = 0;
  // Serial.println("checking Set1");
  while (i < 47)
  {
    if (ch == theSet1[i])
    {
      // Serial.print(String(ch));
      // Serial.println("is from set1");
      return true;
    }

    ++i;
  }
  return false;
}

bool isFromTheSet2(unsigned char ch)
{
  const unsigned char theSet1[39] = {
      32, '\0', 191, 40, 41, 46, 33, 44, 10,
      58, 248, 33,
      45, 35, 43, 34, 39, 37, 42, 95, 64, 36, 94, 38,
      44,47,59,60,62,61,63,91,93,92,96,123,125,126,124};
  // Serial.println("checking Set2");

  int i = 0;
  while (i < 39)
  {
    if (ch == theSet1[i])
    {
      // Serial.print(String(ch));
      // Serial.println("is from set2");
      return true;
    }
    ++i;
  }
  return false;
}

int FindGlyph(unsigned char chFind)
{
  for (int i = 0; i < N_DISTINCT_CHARACTERS; i++)
  {
    if (prForms[i].AsciiCode == chFind)
    {
      return i;
      break;
    }
  }
  return -1;
}

String prReshaper(const char *Text)
{

  String prBuffer = "";
  int stat = 0;
  unsigned char pLetter = ' '; // Previous word
  unsigned char letter;        // Letter
  unsigned char nLetter;       // Next word
  unsigned char temp;

  while ((temp = *Text++))
  {
    // is Number ?
    if (temp >= '0' && temp <= '9')
    {
      // d = temp - '0';
      letter = temp;
    }
    else if (temp >= 128)
    {
      letter = *Text++;
      letter += 32;
      temp += 32;
      if (letter == 207)
      {
        if (temp == 218 || temp == 250)
        {
          letter = 144; //گ
        }
      }
      else if (letter == 166)
      {
        if (temp == 218 || temp == 250)
        { //چ
          letter = 141;
        }
        else
        {
          letter = 228; //ن
        }
      }
    }
    else
    {
      letter = temp;
    }
    //
    if (letter == 172)
    {
      if (temp == 248 || temp == 32)
      {
        letter = 44;
      }
    }
    temp = *Text++;
    if (temp >= 128)
    {
      nLetter = *Text++;
      nLetter += 32;
      temp += 32;
      if (nLetter == 207)
      {
        if (temp == 218 || temp == 250)
        {
          nLetter = 144; //گ
        }
      }
      else if (nLetter == 166)
      {
        if (temp == 218 || temp == 250)
        { //چ
          nLetter = 141;
        }
        else
        {
          nLetter = 228; //ن
        }
      }
      *Text--;
      *Text--;
    }
    else
    {
      nLetter = temp;
      *Text--;
    }
    //
    if (nLetter == 172)
    {
      if (temp == 248 || temp == 32)
      {
        nLetter = 44;
      }
    }
    int isunk = 0;
    /*
    Final: at the end of the word.
    Medial: at the middle of the word.
    Initial: at the beginning of the word.
    Isolated: the character alone (not part of a word).
    */
    if (isFromTheSet1(pLetter))
      if (isFromTheSet2(nLetter))
        stat = 0; // Isolated
      else
        stat = 1; // Initial
    else if (isFromTheSet2(nLetter))
      stat = 2; // Final
    else
      stat = 3; // Medial

    int number = FindGlyph(letter);

    switch (stat)
    {
    case 0: // Isolated
      prBuffer += (char *)(prForms[number].isoGlyph);
      break;
    case 1: // Initial
      prBuffer += (char *)(prForms[number].iniGlyph);
      break;
    case 2: // Final
      prBuffer += (char *)(prForms[number].endGlyph);
      break;
    case 3: // Medial
      prBuffer += (char *)(prForms[number].midGlyph);
      break;
    default:
      isunk = 1;
      break;
    }

    if (isunk == 0)
      pLetter = letter;
  }
  utf8rev((char *)prBuffer.c_str());
  return prBuffer;
}

void utf8rev(char *str)
{
  /* this assumes that str is valid UTF-8 */
  char *scanl, *scanr, *scanr2, c;
  /* first reverse the string */
  for (scanl = str, scanr = str + strlen(str); scanl < scanr;)
    c = *scanl, *scanl++ = *--scanr, *scanr = c;
  /* then scan all bytes and reverse each multibyte character */
  for (scanl = scanr = str; (c = *scanr++);)
  {
    if ((c & 0x80) == 0) // ASCII char
      scanl = scanr;
    else if ((c & 0xc0) == 0xc0)
    { // start of multibyte
      scanr2 = scanr;
      switch (scanr - scanl)
      {
      case 4:
        c = *scanl, *scanl++ = *--scanr, *scanr = c; // fallthrough
      case 3:                                        // fallthrough
      case 2:
        c = *scanl, *scanl++ = *--scanr, *scanr = c;
      }
      scanr = scanl = scanr2;
    }
  }
}

String utf8rev(String utf8String)
{
  uint16_t stringLength = utf8String.length();

  String reversed = utf8String;

  for (int8_t reverseCounter = stringLength - 1;
       reverseCounter >= 0;
       reverseCounter--)
  {
    reversed[stringLength - reverseCounter - 1] = utf8String[reverseCounter];
  }

  return reversed;
}

// UTF-8 strlen function
int strlen_utf8(char *s)
{
  int i = 0, j = 0;
  while (s[i])
  {
    if ((s[i] & 0xc0) != 0x80)
      j++;
    i++;
  }
  return j;
}
