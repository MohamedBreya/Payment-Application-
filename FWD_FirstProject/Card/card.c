#include "card.h"


EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    scanf("%[^\n]s",cardData->cardHolderName);
    if (strlen((const char *)cardData->cardHolderName)<20|| strlen((const char *)cardData->cardHolderName)>24|| !cardData->cardHolderName )
    {
        return WRONG_NAME;
    } else
    {
        return CARD_OK;
    }
}


EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    scanf("%s",cardData->cardExpirationDate);

    if (strlen((const char *)cardData->cardExpirationDate)!=5 || !cardData->cardExpirationDate )
    {
//        printf("WRONG_EXP_DATE\n");
        return WRONG_EXP_DATE;
    } else
    {
//        printf("CARD_Date_OK\n");
        return CARD_OK;
    }
}


EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    scanf("%s",cardData->primaryAccountNumber);

    if (strlen((const char *)cardData->primaryAccountNumber)>19|| strlen((const char *)cardData->primaryAccountNumber)<16|| !cardData->primaryAccountNumber )
    {
//        printf("WRONG_PAN");
        return WRONG_PAN;
    } else
    {
//        printf("CARD_PAN_OK\n");
        return CARD_OK;
    }
}


// Mohammed
// Mohammed Ashraf Breya
// Mohammed Ashraf Mohammed Breya

//09/22
//08/22