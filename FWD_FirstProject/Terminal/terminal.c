#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{

// get the system time (reference "https://stackoverflow.com/questions/5141960/get-the-current-time-in-c")
    time_t t;
    time(&t);
    int day,month,year;
    day=(*localtime(&t)).tm_mday; //get day(we didn't use it)
    month=(*localtime(&t)).tm_mon+1; // get current month
    year=(*localtime(&t)).tm_year+1900; // get the current year
    termData->transactionDate[0]=day;
//    printf("%d\n",termData->transactionDate[0]);
    termData->transactionDate[1]=month;
//    printf("%d\n",termData->transactionDate[1]);
    termData->transactionDate[2]=year;
//    printf("%d\n",termData->transactionDate[2]);
    return TERMINAL_OK;
}

EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
//    check the card expire date with the current system time
char s[2];
s[0]=cardData->cardExpirationDate[0];
s[1]=cardData->cardExpirationDate[1];
int temp_mon= atoi(s);
s[0]=cardData->cardExpirationDate[3];
s[1]=cardData->cardExpirationDate[4];
int temp_year= atoi(s);
if(temp_year>((termData->transactionDate[2])%100))
{
//    printf("ok\n");
    return TERMINAL_OK;
}

else if(temp_year==((termData->transactionDate[2])%100))
{
    if (temp_mon>=((termData->transactionDate[1])%100))
    {
//        printf("ok\n");
        return TERMINAL_OK;
    }
    else if(temp_mon<((termData->transactionDate[1])%100))
    {
        printf("Expire\n");
        return EXPIRED_CARD;
    }
    else
    {
//        printf("wrong\n");
        return WRONG_DATE;
    }
}
else if(temp_year<((termData->transactionDate[2])%100))
{
    printf("Expire\n");
    return EXPIRED_CARD;
}
else
{
//    printf("wrong\n");
    return WRONG_DATE;
}

}




EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    scanf("%f",&termData->transAmount);
    if (termData->transAmount<=0)
    {
//        printf("INVALID_AMOUNT\n");
        return INVALID_AMOUNT;
    }
    else
    {
//        printf("ok\n");
        return TERMINAL_OK;
    }

}






EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->transAmount>termData->maxTransAmount)
    {
//        printf("EXCEED_MAX_AMOUNT\n");
        return EXCEED_MAX_AMOUNT;
    }
    else
    {
//        printf("ok\n");
        return TERMINAL_OK;
    }

}




EN_terminalError_t setMaxAmount(ST_terminalData_t *termData)
{
    scanf("%f",&termData->maxTransAmount);
    if (termData->maxTransAmount<=0)
    {
//        printf("INVALID_MAX_AMOUNT\n");
        return INVALID_MAX_AMOUNT;
    }
    else
    {
//        printf("set_max_ok\n");
        return TERMINAL_OK;
    }

}


