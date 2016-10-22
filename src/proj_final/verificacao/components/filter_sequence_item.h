// interface definitions for VIP

#ifndef _SQI_ITEM_H_
#define _SQI_ITEM_H_

#include <systemc>

class filter_sequence_item
{
public:

  //+-----------------------------------------
  //| Data Members
  //+-----------------------------------------
  bool   data_enable;
  int     A1;
  int     A2;
  int     A3;
  int     A4;
  int     A5;
  int     A6;
  int     A7;
  int     A8;
  int     A9;

  //Output
  int   F;
  bool   data_valid;

  //+-----------------------------------------
  //| Data No Members
  //+-----------------------------------------

  filter_sequence_item(const std::string& name = "filter_sequence_item") { }

};
std::ostream & operator << (std::ostream &os, const filter_sequence_item &item) {
  return os << "instance item of ULA block";
}

#endif /* _SQI_ITEM_H_ */
