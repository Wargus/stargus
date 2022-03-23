/*
 * Panel.h
 *
 *      Author: Andreas Volz
 */

#ifndef PANEL_H_
#define PANEL_H_

class Panel
{
public:
  Panel();
  virtual ~Panel();

  int save(int width, int height);

private:
  unsigned char* CreatePanel(int width, int height);
};

#endif /* PANEL_H_ */
