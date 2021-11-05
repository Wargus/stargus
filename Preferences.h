#ifndef PREFERENCES_H
#define PREFERENCES_H

#include <string>

/**
**		Path to the unit graphics. (default=$DIR/graphics)
*/
#define GRAPHICS_PATH		"graphics"

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

  /**
  **		Destination directory of the data
  */
  void setDestDir(const std::string &dir);
  const std::string getDestDir();

private:
  bool mVideoExtraction;
  std::string mArchiveDir;
  std::string mDestDir;
};

#endif // PREFERENCES_H
