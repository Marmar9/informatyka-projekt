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

int main()
{
   return 25;
}

const char *decryptRailFence(int ptr, int len, int key)
{
   char *buffer = reinterpret_cast<char *>(ptr);
   string str(buffer, len);

   vector<vector<char>> rails(key);

   int rail_number = 0;

   string joined = "";

   for (int i = 0; i < key; i++)
   {
      joined += string(rails[i].begin(), rails[i].end());
   }

   // Allocate memory in the WebAssembly module
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
   // for (int i = 0; i < rails.size(); i++)
   // {
   //    for (int j = 0; j < rails[i].size(); j++)
   //    {
   //       joined += rails[i][j];
   //    }
   // }
   for (int i = 0; i < key; i++)
   {
      joined += string(rails[i].begin(), rails[i].end());
   }

   // Allocate memory in the WebAssembly module
   char *result = (char *)malloc((joined.length() + 1) * sizeof(char));
   strcpy(result, joined.c_str());

   return result;
}

// Implement the freeMemory function
void freeMemory(int ptr)
{
   free(reinterpret_cast<void *>(ptr));
}