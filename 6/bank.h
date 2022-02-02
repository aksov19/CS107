#ifndef _BANK_H
#define _BANK_H

#include "semaphore.h"
#include "pthread.h"

typedef struct Bank {
  unsigned int numberBranches;
  struct       Branch  *branches;
  struct       Report  *report;

  // ADDED
  int               reportsLeftToDo;
  int               numWorkers;
  pthread_mutex_t   transferLock;
  pthread_mutex_t   reportLock;
  sem_t             nextDayLock;

} Bank;

#include "account.h"

int Bank_Balance(Bank *bank, AccountAmount *balance);

Bank *Bank_Init(int numBranches, int numAccounts, AccountAmount initAmount,
                AccountAmount reportingAmount,
                int numWorkers);

int Bank_Validate(Bank *bank);
int Bank_Compare(Bank *bank1, Bank *bank2);



#endif /* _BANK_H */
