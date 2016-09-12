#ifndef FILE_SPLITTER_H__
#define FILE_SPLITTER_H__

/********************************************************
 * FileSplitter 独立于 IProgress（通过依赖倒置DIP实现）
 *
********************************************************/

#include<string>  // std::string

class FileSplitter {
  std::string m_filePath;
  int m_fileNumber;

  IProgress* m_pIprogress // 抽象通知机制

public:
  FileSplitter(const std::string& filePath, int fileNumber, IProgress& iprogress)
    : m_filePath(filePath), m_fileNumber(fileNumber), m_pIprogress(iprogress) {
  }

  void split() {
    // 1. 读取大文件
    // 2. 分批写入小文件
    for(int i = 0; i < m_fileNumber; i++) {
        float progressValue = m_file_number;
        progressValue = (i+1)/progressValue;
        onProgress(progressValue); 
    }
  }
  
protected:
  void onProgress(float value) {  // update progress
    if (m_pIprogress != nullptr) {
      m_pIprogress->DoProgress(value);
    }
  }
};


#endif
