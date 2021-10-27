#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <string>

class Preferences
{
public: // Singleton
  static Preferences& getInstance();

private: // Singleton
  Preferences() {}; // @suppress("Class members should be properly initialized")
  Preferences(const Preferences&);
  //Preferences(Preferences&);
  virtual ~Preferences() {}
  //void operator = (const Preferences&);
  
public:
  void init();

  void setVideoExtraction(bool video);
  bool getVideoExtraction();

  void setArchiveDir(const std::string &dir);
  const std::string getArchiveDir();

  // TODO: not yet used!!
  void setDataDir(const std::string &dir);
  const std::string getDataDir();

private:
  bool mVideoExtraction;
  std::string mArchiveDir;
  std::string mDataDir;
};

#endif // PREFERENCES_H
