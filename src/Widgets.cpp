/*
 * Widget.cpp
 *
 *      Author: Andreas Volz
 */

#include <Palette.h>
#include "Widgets.h"
#include "Storm.h"
#include "Preferences.h"
#include "FileUtil.h"
#include "Png.h"

Widgets::Widgets(std::shared_ptr<Hurricane> hurricane) :
  Grp(hurricane)
{

}

Widgets::~Widgets()
{

}

bool Widgets::convert(const char *mpqfile, const char *arcfile,
                      const char *file, int pale)
{
  unsigned char *palp = NULL;
  unsigned char *gfup = NULL;
  unsigned char *gfup2 = NULL;
  unsigned char *image = NULL;
  int w;
  int h;
  char buf[1024];
  unsigned char *p;
  unsigned char *end;
  bool result = true;

  result = FileExists(mpqfile);

  if (result)
  {
    Storm mpq(mpqfile);
    result = mpq.extractMemory(arcfile, &gfup, NULL);
    if (result)
    {
      image = ConvertGraphic(0, gfup, &w, &h, gfup2, 0);

      // 0 and 255 are transparent
      p = image;
      end = image + w * h;
      while (p < end)
      {
        if (!*p)
        {
          *p = 0xFF;
        }
        ++p;
      }

      palp = Palettes[pale];

      free(gfup);

      Preferences &preferences = Preferences::getInstance();
      sprintf(buf, "%s/graphics/%s/", preferences.getDestDir().c_str(), file);

      sprintf(buf, "%s/graphics/%s/menu.png", preferences.getDestDir().c_str(),
              file);
      SaveImage(buf, image, palp, 1, 64, 20);

      sprintf(buf, "%s/graphics/%s/menu pressed.png",
              preferences.getDestDir().c_str(), file);
      SaveImage(buf, image, palp, 2, 64, 20);

      sprintf(buf, "%s/graphics/%s/minimap terrain disabled.png",
              preferences.getDestDir().c_str(), file);
      SaveImage(buf, image, palp, 3, 64, 20);

      sprintf(buf, "%s/graphics/%s/minimap terrain.png",
              preferences.getDestDir().c_str(), file);
      SaveImage(buf, image, palp, 4, 64, 20);

      sprintf(buf, "%s/graphics/%s/minimap terrain pressed.png",
              preferences.getDestDir().c_str(), file);
      SaveImage(buf, image, palp, 5, 64, 20);

      sprintf(buf, "%s/graphics/%s/diplomacy disabled.png",
              preferences.getDestDir().c_str(), file);
      SaveImage(buf, image, palp, 83, 64, 20);

      sprintf(buf, "%s/graphics/%s/diplomacy.png",
              preferences.getDestDir().c_str(), file);
      SaveImage(buf, image, palp, 84, 64, 20);

      sprintf(buf, "%s/graphics/%s/diplomacy pressed.png",
              preferences.getDestDir().c_str(), file);
      SaveImage(buf, image, palp, 85, 64, 20);

      sprintf(buf, "%s/graphics/%s/button left disabled 224x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 224, 104);

      sprintf(buf, "%s/graphics/%s/button left 224x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 224, 107);

      sprintf(buf, "%s/graphics/%s/button left pressed 224x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 224, 110);

      sprintf(buf, "%s/graphics/%s/button left disabled 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 104);

      sprintf(buf, "%s/graphics/%s/button left 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 107);

      sprintf(buf, "%s/graphics/%s/button left pressed 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 110);

      sprintf(buf, "%s/graphics/%s/button disabled 224x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 224, 113);

      sprintf(buf, "%s/graphics/%s/button 224x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 224, 116);

      sprintf(buf, "%s/graphics/%s/button pressed 224x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 224, 119);

      sprintf(buf, "%s/graphics/%s/button disabled 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 113);

      sprintf(buf, "%s/graphics/%s/button 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 116);

      sprintf(buf, "%s/graphics/%s/button pressed 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 119);

      sprintf(buf, "%s/graphics/%s/button right disabled 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 122);

      sprintf(buf, "%s/graphics/%s/button right 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 125);

      sprintf(buf, "%s/graphics/%s/button right pressed 104x28.png",
              preferences.getDestDir().c_str(), file);
      SaveButton(buf, image, palp, 104, 128);
    }
    else
    {
      result = false;
    }
  }

  free(image);

  return result;
}

void Widgets::SaveImage(char *name, unsigned char *image, unsigned char *palp,
                        int id, int w, int h)
{
  unsigned char *buf = (unsigned char *) malloc(w * h);
  int i;

  for (i = 0; i < h; ++i)
  {
    memcpy(buf + w * i, image + id * 28 * 64 + 64 * i, w);
  }

  Png::save(name, buf, w, h, palp, 255);

  free(buf);
}

void Widgets::SaveButton(char *name, unsigned char *image, unsigned char *palp,
                         int size, int id)
{
  unsigned char *button;
  int i, j;

  button = (unsigned char *) malloc(size * 28);

#define copyimage(dst, src) \
	for (j = 0; j < 28; ++j) { \
		memcpy((dst + size*j), (src + 64*j), 8); \
	}

  copyimage(button + 0, image + (id - 1) * 28 * 64);
  for (i = 8; i < size - 8; i += 8)
  {
    copyimage(button + i, image + id * 28 * 64);
  }
  copyimage(button + size - 8, image + (id + 1) * 28 * 64);

  for (i = 0; i < size * 28; ++i)
  {
    if (button[i] == 41)
    {
      button[i] = 255;
    }
  }

  Png::save(name, button, size, 28, palp, 255);

  free(button);
}

