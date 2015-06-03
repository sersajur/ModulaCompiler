/*
 * ByteCode.h
 *
 *  Created on: Jun 2, 2015
 *      Author: sersajur
 */

#ifndef SRC_BYTECODE_H_
#define SRC_BYTECODE_H_

#include <ostream>
#include <vector>
#include <string>

class ByteCode {
public:
    ByteCode() {}
    virtual ~ByteCode() {}

    std::string getNextLabel() { return std::string("_label") + std::to_string(labelCount++); }
    std::string getNextTriadNumber() { return "(" + std::to_string(triadCount++) + ")"; }

    std::string emitCode(const std::string& triad) {
        auto number = getNextTriadNumber();
        code.append(number).append(" ").append(triad).append("\n");
        return number;
    }

	friend std::ostream& operator<<(std::ostream& io_os, const ByteCode& i_byteCode);

private:
    std::string code;
    int labelCount = 0;
    int triadCount = 1;
};

#endif /* SRC_BYTECODE_H_ */
