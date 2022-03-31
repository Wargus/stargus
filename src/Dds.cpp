/*
 * Dds.cpp
 *
 *      Author: Andreas Volz
 */

#ifdef HAVE_IMAGEMAGICKPP

// Local
#include "Dds.h"
#include "Hurricane.h"
#include "FileUtil.h"
#include "Preferences.h"

// System
#include <Magick++.h>
#include <memory>
#include <iostream>

using namespace std;
using namespace Magick;

Dds::Dds(std::shared_ptr<Hurricane> hurricane) :
  Converter(hurricane)
{
  // TODO: might be needed for Windows/OSX regarding docu...
  //InitializeMagick(*argv);
}

Dds::~Dds()
{

}

bool Dds::convert(const std::string &arcfile, const std::string &file)
{
  bool result = true;

  shared_ptr<DataChunk> data = mHurricane->extractDataChunk(arcfile);
  if (data)
  {
    Blob blob(static_cast<void *>(data->getDataPointer()), data->getSize());
    // Construct the image object. Seperating image construction from the
    // the read operation ensures that a failure to read the image file
    // doesn't render the image object useless.
    Image image;
    try
    {
      // Read a file into image object
      image.read(blob);

      Preferences &preferences = Preferences::getInstance();
      string targetPath = preferences.getDestDir() + "/" + GRAPHICS_PATH + "/"
                          + file;

      // Write the image to a file
      CheckPath(targetPath);
      image.write(targetPath);
    }
    catch (Exception &error_)
    {
      cout << "Caught exception: " << error_.what() << endl;
      return 1;
    }
  }

  return result;
}

#endif /* HAVE_IMAGEMAGICKPP */
