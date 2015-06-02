/*
 * ByteCode.h
 *
 *  Created on: Jun 2, 2015
 *      Author: sersajur
 */

#ifndef SRC_BYTECODE_H_
#define SRC_BYTECODE_H_

#include <ostream>

class ByteCode {
public:
	ByteCode();
	virtual ~ByteCode();

	friend std::ostream& operator<<(std::ostream& io_os, const ByteCode& i_byteCode);
};

#endif /* SRC_BYTECODE_H_ */
