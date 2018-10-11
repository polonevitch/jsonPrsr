  typedef struct TagValue 
  {
    char *tag;
    char *value;
  } TagValue_t;

#ifdef __cplusplus
extern "C" 
{
#endif

  void clearTVarr(TagValue_t* arr, int sz);
  int parseJsonResponse(const char* jsonStr, TagValue_t** resultArray, const char* prefix);

#ifdef __cplusplus
}
#endif