#include "server.h"


EN_transStat_t receiveTransactionData(ST_transaction_t *transData,ST_accountsDB_t *accountReference)
{

    if(isAmountAvailable(&(transData->terminalData),accountReference)==SERVER_OK)
    {
    //                printf("amount available\n");
        if(saveTransaction(transData)==SERVER_OK)
        {
    //                    printf("save ok\n");
            ar[transData->transactionSequenceNumber].transState=APPROVED;
            return APPROVED;
        }
        else
        {
    //                    printf("server error\n");
            return INTERNAL_SERVER_ERROR;
        }

    }
    else
    {
        printf("**DECLINED_INSUFFICIENT_FUND**\n");
        return DECLINED_INSUFFICIENT_FUND;
    }
}



EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountReference)
{
    for(int j=0;j<10;j++)
    {
        if (!strcmp(((const char *)(cardData->primaryAccountNumber)),((const char *)(arr[j].primaryAccountNumber))))
        {
            *accountReference=arr[j];
            x=j;
            return SERVER_OK;
        }
    }
    return ACCOUNT_NOT_FOUND;
}

EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountReference)
{
    if (accountReference->state==BLOCKED)
        return BLOCKED_ACCOUNT;
    else
        return SERVER_OK;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t *termData,ST_accountsDB_t *accountReference)
{
    if(termData->transAmount>accountReference->balance)
        return LOW_BALANCE;
    else
        return SERVER_OK;
}

EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
//    transData->transactionSequenceNumber=256;
    if(transData->transactionSequenceNumber>=255||transData->transactionSequenceNumber<0)
    {
        return SAVING_FAILED;
    }
    else
    {
        ar[transData->transactionSequenceNumber]=*transData;
        return SERVER_OK;
    }

}


/* ******************* old code *******************************/
/*
 *
EN_transStat_t receiveTransactionData(ST_transaction_t *transData)
{
    ST_accountsDB_t accountReference;
    if (isValidAccount(&(transData->cardHolderData),&accountReference)==SERVER_OK)
    {
//        printf("valid account\n");
        if (isBlockedAccount(&accountReference)==SERVER_OK)
        {
//            printf("running account\n");
            if(isAmountAvailable(&(transData->terminalData),&accountReference)==SERVER_OK)
            {
//                printf("amount available\n");
                if(saveTransaction(transData)==SERVER_OK)
                {
//                    printf("save ok\n");
                    ar[transData->transactionSequenceNumber].transState=APPROVED;
                    return APPROVED;
                }
                else
                {
//                    printf("server error\n");
                    return INTERNAL_SERVER_ERROR;
                }

            }
            else
            {
                printf("**DECLINED_INSUFFICIENT_FUND**\n");
                return DECLINED_INSUFFICIENT_FUND;
            }
        }
        else
        {
            printf("**DECLINED_STOLEN_CARD**\n");
            return DECLINED_STOLEN_CARD;
        }
    }
    else
    {
        printf("account not found\n");
        return  FRAUD_CARD;
    }
}

 */
