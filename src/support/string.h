#ifndef JLE_STRING_H
#define JLE_STRING_H


#include <sstream>


#define JLE_SS(__EXPR__) (static_cast<std::ostringstream*>(&(std::ostringstream().flush() << __EXPR__))->str())




namespace jle
{



}

#endif // JLE_STRING_H