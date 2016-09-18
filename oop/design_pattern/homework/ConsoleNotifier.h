#ifndef CONSOLE_NOTIFIER_H__
#define CONSOLE_NOTIFIER_H__

#include "IProgress.h"

class ConsoleNotifier : public IProgress {
public:
  virtual void DoProgress(float value) {
    // update the value to console 
  }
};

#endif