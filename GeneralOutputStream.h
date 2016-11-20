/*
 * GeneralOutputStream.h
 *
 *  Created on: Oct 26, 2016
 *      Author: siwecki
 */

#ifndef GENERALOUTPUTSTREAM_H_
#define GENERALOUTPUTSTREAM_H_


class GeneralOutputStream {
private:
	bool sendToSerial;

public:
	void setSendToSerial(bool value);
	void sendln(const char * value);
	void sendln(const char * value1, const char * value2);
	void sendln(const char * value1, const char * value2, const char * value3);
	void sendln(const char * value1, const char * value2, const char * value3, const char * value4);
	void sendln(const char * value1, int value2, int value3, int value4, int value5, int value6, int value7);
};

extern GeneralOutputStream DiagnosticOutputStream;

#endif /* GENERALOUTPUTSTREAM_H_ */
