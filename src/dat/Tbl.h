/*
 * Tbl.h
 *
 *      Author: Andreas Volz
 */

#ifndef TBL_H
#define TBL_H

// Local
#include "kaitai/file_tbl.h"
#include "TblEntry.h"

// System
#include <memory>

namespace dat {



class Tbl
{
public:
  Tbl();
  virtual ~Tbl();

  std::vector<TblEntry> convertFromStream(std::shared_ptr<kaitai::kstream> ks);

private:
  void removeDoubleSpaces(std::string &str);
};

} /* namespace dat */

#endif /* TBL_H */
