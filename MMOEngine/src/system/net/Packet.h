/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#ifndef PACKET_H_
#define PACKET_H_

#include "../platform.h"

#ifndef PLATFORM_WIN
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif

#include "../io/ObjectInputStream.h"
#include "../io/ObjectOutputStream.h"

#include "PacketIndexOutOfBoundsException.h"

namespace sys {
  namespace net {

	class Packet : public ObjectInputStream, public ObjectOutputStream {
	public:
		static const int RAW_MAX_SIZE = 1496;

	public:
		Packet() : Stream(RAW_MAX_SIZE, RAW_MAX_SIZE), ObjectInputStream(), ObjectOutputStream() {
		}

		Packet(int size) : Stream(size, RAW_MAX_SIZE), ObjectInputStream(), ObjectOutputStream() {
		}

		virtual ~Packet() {
		}

		Packet* clone(int startoffs = 0) {
			int newSize = size() - startoffs;
			Packet* p = new Packet(newSize);

			p->writeStream(elementData + startoffs, newSize);

			return p;
		}

		// inserting methods
		inline void insertBoolean(bool val) {
			writeBoolean(val);
		}

		inline void insertByte(uint8 val) {
			writeByte(val);
		}

		inline void insertByte(int offs, uint8 val) {
			writeByte(offs, val);
		}

		inline void insertSignedByte(int8 val) {
			writeSignedByte(val);
		}

		inline void insertShort(uint16 val) {
			writeShort(val);
		}

		inline void insertSignedShort(int16 val) {
			writeSignedShort(val);
		}

		inline void insertShort(int offs, uint16 val) {
			writeShort(offs, val);
		}

		inline void insertShortNet(uint16 val) {
			writeShort(htons(val));
		}

		inline void insertInt(uint32 val) {
			writeInt(val);
		}

		inline void insertInt(int offs, uint32 val) {
			writeInt(offs, val);
		}

		inline void insertSignedInt(int32 val) {
			writeSignedInt(val);
		}

		inline void insertIntNet(uint32 val) {
			writeInt(htonl(val));
		}

		inline void insertLong(uint64 val) {
			writeLong(val);
		}

		inline void insertLong(int offs, uint64 val) {
			writeLong(offs, val);
		}

		inline void insertSignedLong(int64 val) {
			writeSignedLong(val);
		}

		inline void insertFloat(float val) {
			writeFloat(val);
		}

		void insertAscii(const char *ascii) {
			int len = strlen(ascii);

			writeShort(len);
			writeStream(ascii, len);
		}

		void insertAscii(char *ascii, int len) {
			writeShort(len);
			writeStream(ascii, len);
		}

		void insertAscii(const string& ascii) {
			int len = ascii.size();
			writeShort(len);

			writeStream(ascii.c_str(), len);
		}

		void insertUnicode(const unicode& str) {
			int len = str.size();
			writeInt(len);

			writeStream(str.u_str(), len * 2);
		}

		inline void insertStream(const char *buf, int len) {
			writeStream(buf, len);
		}

		inline void insertStream(Stream* stream) {
			writeStream(stream);
		}

		inline void insertStream(Stream* stream, int len) {
			writeStream(stream, len);
		}

		// parsing methods
		inline bool parseBoolean() {
			return readBoolean();
		}

		inline uint8 parseByte() {
			return readByte();
		}

		inline uint8 parseByte(int offs) {
			return readByte(offs);
		}

		inline int8 parseSignedByte() {
			return readSignedByte();
		}

		inline int8 parseSignedByte(int offs) {
			return readSignedByte(offs);
		}

		inline uint16 parseShort() {
			return readShort();
		}

		inline int16 parseSignedShort() {
			return readSignedShort();
		}

		inline uint16 parseShort(int offs) {
			return readShort(offs);
		}

		inline uint16 parseNetShort() {
			return ntohs(readShort());
		}

		inline uint16 parseNetShort(int offs) {
			return ntohs(readShort(offs));
		}

		inline uint32 parseInt() {
			return readInt();
		}

		inline uint32 parseInt(int offs) {
			return readInt(offs);
		}

		inline int32 parseSignedInt() {
			return readSignedInt();
		}

		inline int32 parseSignedInt(int offs) {
			return readSignedInt(offs);
		}

		inline uint64 parseLong() {
			return readLong();
		}

		inline uint64 parseLong(int offs) {
			return readLong(offs);
		}

		inline int64 parseSignedLong() {
			return readSignedLong();
		}

		inline int64 parseSignedLong(int offs) {
			return readSignedLong(offs);
		}

		inline float parseFloat() {
			return readFloat();
		}

		inline float parseFloat(int offs) {
			return readFloat(offs);
		}

		inline int parseAscii(char *ascii) {
			uint16 len = readShort();
			readStream(ascii, (int) len);

			ascii[len] = 0;
			return len;
		}

		inline void parseAscii(string& ascii) {
			uint32 len = readShort();
			shiftOffset(len);

			ascii.clear();
			ascii.append(offset - len, len);
		}

		inline void parseAscii(int offs, string& ascii) {
			uint32 len = readShort(offs);

			char* elementOffset = elementData + offs + 2;
			if (elementOffset > end)
				throw StreamIndexOutOfBoundsException(this, offs + 2);

			ascii.clear();
			ascii.append(elementOffset - len, len);
		}

		inline void parseUnicode(unicode& str) {
			uint32 len = readInt();
			shiftOffset(len * 2);

			str.clear();
			str.append((wchar_t*) (offset - len * 2), len);
		}

		inline void parseUnicode(int offs, unicode& str) {
			uint32 len = readInt(offs);

			char* elementOffset = elementData + offs + 4;
			if (elementOffset > end)
				throw StreamIndexOutOfBoundsException(this, offs + 4);

			str.clear();
			str.append((wchar_t*) (elementOffset - len * 2), len);
		}

		inline void parseStream(char *buf, int len) {
			readStream(buf, len);
		}

		inline void parseStream(Stream* stream, int len) {
			readStream(stream, len);
		}

		string toString() {
			stringstream str;
			str << "Packet [" << size() << "] " << uppercase << hex;

			for (int i = 0; i < size(); ++i) {
				unsigned int byte = ((unsigned int )elementData[i]) & 0xFF;

				if ((byte & 0xF0) == 0)
					str << "0" << byte  << " ";
				else
					str << byte  << " ";
			}

			return str.str();
		}

	};

  } // namespace net
} // namespace sys

using namespace sys::net;

#endif /*PACKET_H_*/
