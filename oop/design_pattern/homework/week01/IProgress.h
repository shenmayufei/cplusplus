#ifndef IPROGRESS_H__
#define IPROGRESS_H__

class IProgress {
public:
  virtual void DoProgress(float value) = 0;
  virtual ~IProgress() {};
};

#endif