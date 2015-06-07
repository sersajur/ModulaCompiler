/*
 * ByteCode.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: sersajur
 */

#include "ByteCode.h"

std::ostream& operator<<(std::ostream& io_os, const ByteCode& i_byteCode) {
    return io_os << i_byteCode.code;
}
