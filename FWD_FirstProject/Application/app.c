#include "app.h"

void appStart(void) {
    ST_cardData_t cardData;
    ST_transaction_t transData;
    if (getCardHolderName(&cardData) == WRONG_NAME)
    {
        printf("**WRONG_NAME**\n");
    }
    else
    {
        if (getCardExpiryDate(&cardData) == WRONG_EXP_DATE)
            printf("**WRONG_EXP_DATE**\n");
        else
        {
            if (getCardPAN(&cardData) == WRONG_PAN)
                printf("**WRONG_PAN**\n");
            else
            {
                ST_terminalData_t termData;
                if (getTransactionDate(&termData) == TERMINAL_OK)
                {
                    if (isCardExpired(&cardData, &termData) == TERMINAL_OK)
                    {
                        if (setMaxAmount(&termData) == TERMINAL_OK)
                        {
                            ST_accountsDB_t accountReference;
                            if (isValidAccount(&cardData, &accountReference) == SERVER_OK)
                            {
                                if (isBlockedAccount(&accountReference) == SERVER_OK)
                                {
                                    printf("Do you want to block the account ? ------> if Yes enter( 'Y' or 'y' ) if No enter ( 'N' or 'n' ) \n");
                                    scanf("\n");
                                    char check;
                                    scanf("%c", &check);
                                    if (check == 'Y' || check == 'y')
                                    {
                                        printf("BLOCKED DONE\n");
                                        (accountReference).state = BLOCKED;
                                    }
                                    else if (check == 'N' || check == 'n')
                                    {
                                        if (getTransactionAmount(&termData) == TERMINAL_OK)
                                        {
                                            if (isBelowMaxAmount(&termData) == TERMINAL_OK)
                                            {
                                                transData.cardHolderData = cardData;
                                                transData.terminalData = termData;
                                                transData.transactionSequenceNumber = 0;
                                                if (receiveTransactionData(&transData,&accountReference) == SERVER_OK)
                                                {
                                                    printf("**APPROVED**\n");
                                                    transData.transactionSequenceNumber++;
                                                    printf("%f\n", arr[x].balance);
                                                    arr[x].balance -= transData.terminalData.transAmount;
                                                    printf("%f\n", arr[x].balance);
                                                }

                                            }
                                            else
                                            {
                                                printf("**EXCEED_MAX_AMOUNT**\n");
//                                    printf("**Failed**\n");
                                            }
                                        }
                                        else
                                        {
                                            printf("**INVALID_AMOUNT**\n");

                                        }
                                    }
                                    else
                                    {
                                        printf("**FRAUD_CARD**\n");
                                    }
                                }
                                else
                                {
                                    printf("**DECLINED_STOLEN_CARD**\n");

                                }
                            }
                            else
                            {
                                printf("account not found\n");
                            }
                        }
                        else
                        {
                            printf("**INVALID_MAX_AMOUNT**\n");
                        }
                    }
                    else
                    {
                        printf("**WRONG_DATE**\n");
                    }

                }
            }
        }
    }

}



/*
 ************************************** old code **************************************
void appStart(void)
{
    ST_cardData_t cardData;
    if (getCardHolderName(&cardData)==WRONG_NAME)
    {
        printf("**WRONG_NAME**\n");
    }
    else
    {
        if (getCardExpiryDate(&cardData)==WRONG_EXP_DATE)
            printf("**WRONG_EXP_DATE**\n");
        else
        {
            if (getCardPAN(&cardData)==WRONG_PAN)
                printf("**WRONG_PAN**\n");
            else
            {
                ST_terminalData_t termData;
                if (getTransactionDate(&termData)==TERMINAL_OK)
                {
                    if (isCardExpired(&cardData,&termData)==TERMINAL_OK)
                    {
                        if(setMaxAmount(&termData)==TERMINAL_OK)
                        {
                            if (getTransactionAmount(&termData)==TERMINAL_OK)
                            {
                                if (isBelowMaxAmount(&termData)==TERMINAL_OK)
                                {
                                    ST_transaction_t transData;
                                    transData.cardHolderData=cardData;
                                    transData.terminalData=termData;
                                    transData.transactionSequenceNumber=0;
                                    if (receiveTransactionData(&transData)==SERVER_OK)
                                    {
                                        printf("**APPROVED**\n");
                                        transData.transactionSequenceNumber++;
//                                        printf("%f\n",arr[x].balance);
                                        arr[x].balance-=transData.terminalData.transAmount;
//                                        printf("%f\n",arr[x].balance);
                                    }
                                    else
                                    {
                                        printf("**FRAUD_CARD**\n");
                                    }
                                }
                                else
                                {
                                    printf("**EXCEED_MAX_AMOUNT**\n");
//                                    printf("**Failed**\n");
                                }
                            }
                            else
                            {
                                printf("**INVALID_AMOUNT**\n");
                            }
                        }
                        else
                            printf("**INVALID_MAX_AMOUNT**\n");
                    }
                    else
                        printf("**WRONG_DATE**\n");

                }
            }
        }
    }

}

 */
