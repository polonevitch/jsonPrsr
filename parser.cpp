#include "parser.h"
#include <vector>
#include "json.hpp"
#include <string>

using json = nlohmann::json;
using namespace std;

void clearTVarr(TagValue_t* arr, int sz)
{
  if (!arr)
    return;

  for(int i=0; i<sz; i++)
  { 
    if (arr[i].tag)
      delete[] arr[i].tag;
    if (arr[i].value)
      delete[] arr[i].value;
  }
  delete[] arr;
}

void recursiveIteratate(const json& j, vector<pair<string, string>>* rv, vector<string>* ns, int arrNum)
{
  int m, n;
  m = n = 1;
  for (auto it = j.begin(); it != j.end(); ++it)
  {
    if (it->is_structured())
    {
      try
      {
        ns->push_back(it.key());
        recursiveIteratate(*it, rv, ns, 0);
        ns->pop_back();
      }
      catch (json::invalid_iterator)//element of array
      { 
        recursiveIteratate(*it, rv, ns, m++);
      }
    }
    else
    {
      string tag;
      for (const auto i : *ns)
        tag.append(i).append("_");
      if (arrNum != 0)
        tag.append(to_string(arrNum)).append("_");

      try 
      {
        tag.append(it.key());
      }
      catch (json::invalid_iterator)
      {
        tag.append(to_string(n++));
      }
      if(it.value().is_string())
        rv->push_back(make_pair(tag, it.value().get<string>()));
      else
        rv->push_back(make_pair(tag, it.value().dump()));
    }
  }
}

int parseJsonResponse(const char* jsonStr, TagValue_t** resultArray, const char* prefix)
{
  vector<pair<string, string>> resultVec;
  vector<string> nameStack;
  if(prefix)
    nameStack.push_back(prefix);
  json j;
  try
  {
    j = json::parse(jsonStr);
    recursiveIteratate(j, &resultVec, &nameStack, 0);
  }
  catch (...)
  {
    return -1;
  }
  
  int cnt, n;
  cnt = n = resultVec.size();
  (*resultArray) = new TagValue_t[cnt];
  
  for (const auto i : resultVec)
  {
    string F(i.first);
    transform(F.begin(), F.end(), F.begin(), ::toupper);
    string S(i.second);
    transform(S.begin(), S.end(), S.begin(), ::toupper);
    replace(S.begin(), S.end(), ' ', '_');

    cnt--;

    (*resultArray)[cnt].tag = new char[F.length() + 1];
    strcpy((*resultArray)[cnt].tag, F.c_str());

    (*resultArray)[cnt].value = new char[S.length() + 1];
    strcpy((*resultArray)[cnt].value, S.c_str());
  }

  return n;
}