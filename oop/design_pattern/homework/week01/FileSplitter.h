#ifndef FILE_SPLITTER_H__
#define FILE_SPLITTER_H__

/********************************************************
 * FileSplitter 独立于 IProgress（通过依赖倒置DIP实现）
 *
********************************************************/

#include <string>  // std::string
#include <vector>  // std::vector

class FileSplitter {
  std::string m_filePath;
  int m_fileNumber;

  std::vector<IProgress*> m_vIProgress; // 抽象通知机制

public:
  FileSplitter(const std::string& filePath, int fileNumber )
    : m_filePath(filePath), m_fileNumber(fileNumber) {
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

  void addIProgress(IProgress* ip) {
    m_vIProgress.push_back(ip);
  }

  void removeIProgress(IProgress* ip) {
    // remove ip from m_vIProgress
    // it's not an efficient implementation, use it for now
    for(auto ips = m_vIProgress.begin(); ips != m_vIProgress.end(); ips++) {
      if (ip == *ips) m_vIProgress.erase(ips);
    }
  }
  
protected:
  void onProgress(float value) {  // update progress
    for (auto ip = m_vIProgress.begin(); ip != m_vIProgress.end(); ip++) {
      (*ip)->DoProgress(value);
    }
  }
};


#endif
