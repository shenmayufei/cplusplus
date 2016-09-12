#ifndef MAIN_FORM_H__
#define MAIN_FORM_H__

#include <cstdlib>  // atoi
#include <string>   // std::string

#include "IProgress.h"  // IProgress

// C++ 支持多继承，但是推荐的方式是：一个主继承，其它都是继承接口
class MainForm : public Form, public IProgress {  // Form 是类， IProgress 是接口
  TextBox* txtFilePath;
  TextBox* txtFileNumber;

  ProgressBar* progressBar;

public:
  void Button1Click() {
    std::string filePath = txtFilePath->getText();
    int number = atoi(txtFileNumber->getText().c_str());

    FileSplitter splitter(filePath, number, this);

    splitter.split();
  }

  virtual void DoProgress(float value) {
    progressBar->setValue(value);
  }

};

#endif