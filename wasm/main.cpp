#include <emscripten.h>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;
extern "C"
{
   const char *encryptRailFence(int ptr, int len, int key);
   const char *decryptRailFence(int ptr, int len, int key);
   void freeMemory(int ptr);
}

const char *decryptRailFence(int ptr, int len, int key)
{
   char *buffer = reinterpret_cast<char *>(ptr);
   string str(buffer, len);

   vector<vector<char>> rails(key);
   int rail_number = 0;
   bool down = true;

   vector<int> rail_lengths(key, 0);

   for (int i = 0; i < len; i++)
   {
      rail_lengths[rail_number]++;

      if (rail_number == key - 1)
      {
         down = false;
      }
      else if (rail_number == 0)
      {
         down = true;
      }

      if (down)
      {
         rail_number++;
      }
      else
      {
         rail_number--;
      }
   }

   int index = 0;
   for (int i = 0; i < key; i++)
   {
      for (int j = 0; j < rail_lengths[i]; j++)
      {
         rails[i].push_back(str[index++]);
      }
   }

   string joined;
   rail_number = 0;
   down = true;
   for (int i = 0; i < len; i++)
   {
      joined += rails[rail_number].front();
      rails[rail_number].erase(rails[rail_number].begin());

      if (rail_number == key - 1)
      {
         down = false;
      }
      else if (rail_number == 0)
      {
         down = true;
      }

      if (down)
      {
         rail_number++;
      }
      else
      {
         rail_number--;
      }
   }

   char *result = (char *)malloc((joined.length() + 1) * sizeof(char));
   strcpy(result, joined.c_str());

   return result;
}

const char *encryptRailFence(int ptr, int len, int key)
{
   char *buffer = reinterpret_cast<char *>(ptr);
   string str(buffer, len);

   vector<vector<char>> rails(key);

   int rail_number = 0;

   bool add = true;

   for (int i = 0; i < len; i++)
   {
      rails[rail_number].push_back(str[i]);
      if (rail_number == key - 1)
      {
         add = false;
      }
      else if (rail_number == 0)
      {
         add = true;
      }

      if (add)
      {
         rail_number++;
      }
      else
      {
         rail_number--;
      }
   }

   string joined = "";
   for (int i = 0; i < rails.size(); i++)
   {
      for (int j = 0; j < rails[i].size(); j++)
      {
         joined += rails[i][j];
      }
   }
   char *result = (char *)malloc((joined.length() + 1) * sizeof(char));
   strcpy(result, joined.c_str());

   return result;
}

void freeMemory(int ptr)
{
   free(reinterpret_cast<void *>(ptr));
}