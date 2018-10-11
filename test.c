#include <stdio.h>
#include "parser.h"

int main()
{
  char js[] = "{\
    \"Success\": \"true\",\
    \"ErrorCode\" : 0,\
    \"ErrorMessage\" : \"null\",\
    \"Result\" :\
  {\
    \"CustomerPhoneNumber\": \"9734385660\",\
      \"Transactions\" :\
      [\
    {\
      \"TrackingNumber\": \"123456789012\",\
        \"PaymentStatus\" : \"Paid\",\
        \"DeliveryMethod\" : \"MOBILE WALLET\",\
        \"WireNumber\" : \"BPCCFEE-70681\",\
        \"TransferAmount\" : \"45\",\
        \"PaymentMethod\" : \"PaS\",\
        \"PaSExpirationDate\" : \"2017-08-26T20:37:50\",\
        \"PaSDisplayStatus\" : \"Pending\",\
        \"PaSTransferPrice\" : \"1000\"\
    },\
      {\
        \"TrackingNumber\":  \"111222333444\",\
        \"PaymentStatus\" : \"Unpaid\",\
        \"DeliveryMethod\" : \"HOME DELIVERY\",\
        \"WireNumber\" : \"BPCCFEE-67707\",\
        \"TransferAmount\" : \"25\",\
        \"PaymentMethod\" : \"CC\",\
        \"PaSExpirationDate\" : \"\",\
        \"PaSDisplayStatus\" : \"\",\
        \"PaSTransferPrice\" : \"\"\
      }\
      ]\
  }\
}";

  TagValue_t* res = NULL;

  int cnt = parseJsonResponse(js, &res, 0);
  if(cnt < 0)
    printf("FAIL\n");

  int r = 0;
  for (r=0; r < cnt; r++)
    printf("%s\t%s\n", res[r].tag, res[r].value);

  clearTVarr(res, cnt);

  return 0;
}