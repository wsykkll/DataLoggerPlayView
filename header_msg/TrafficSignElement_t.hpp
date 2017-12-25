/** THIS IS AN AUTOMATICALLY GENERATED FILE.  DO NOT MODIFY
 * BY HAND!!
 *
 * Generated by lcm-gen
 **/

#ifndef __TrafficSignElement_t_hpp__
#define __TrafficSignElement_t_hpp__

#include <lcm/lcm_coretypes.h>

#include "Point_t.hpp"
#include "Point_t.hpp"
#include "METGPSInfo_Lcm.hpp"


class TrafficSignElement_t
{
    public:
        uint8_t    sampleType;

        uint8_t    eShape;

        uint8_t    eColor;

        uint8_t    sPointNum;

        uint8_t    eKeepOut;

        Point_t    objpPointPts[5];

        Point_t    objTextPts[2];

        uint8_t    ucDrawMode;

        uint8_t    ucMinFlag;

        METGPSInfo_Lcm objMETGPSInfo_Lcm;

    public:
        /**
         * Encode a message into binary form.
         *
         * @param buf The output buffer.
         * @param offset Encoding starts at thie byte offset into @p buf.
         * @param maxlen Maximum number of bytes to write.  This should generally be
         *  equal to getEncodedSize().
         * @return The number of bytes encoded, or <0 on error.
         */
        inline int encode(void *buf, int offset, int maxlen) const;

        /**
         * Check how many bytes are required to encode this message.
         */
        inline int getEncodedSize() const;

        /**
         * Decode a message from binary form into this instance.
         *
         * @param buf The buffer containing the encoded message.
         * @param offset The byte offset into @p buf where the encoded message starts.
         * @param maxlen The maximum number of bytes to read while decoding.
         * @return The number of bytes decoded, or <0 if an error occured.
         */
        inline int decode(const void *buf, int offset, int maxlen);

        /**
         * Retrieve the 64-bit fingerprint identifying the structure of the message.
         * Note that the fingerprint is the same for all instances of the same
         * message type, and is a fingerprint on the message type definition, not on
         * the message contents.
         */
        inline static int64_t getHash();

        /**
         * Returns "TrafficSignElement_t"
         */
        inline static const char* getTypeName();

        // LCM support functions. Users should not call these
        inline int _encodeNoHash(void *buf, int offset, int maxlen) const;
        inline int _getEncodedSizeNoHash() const;
        inline int _decodeNoHash(const void *buf, int offset, int maxlen);
        inline static uint64_t _computeHash(const __lcm_hash_ptr *p);
};

int TrafficSignElement_t::encode(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;
    int64_t hash = (int64_t)getHash();

    tlen = __int64_t_encode_array(buf, offset + pos, maxlen - pos, &hash, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->_encodeNoHash(buf, offset + pos, maxlen - pos);
    if (tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int TrafficSignElement_t::decode(const void *buf, int offset, int maxlen)
{
    int pos = 0, thislen;

    int64_t msg_hash;
    thislen = __int64_t_decode_array(buf, offset + pos, maxlen - pos, &msg_hash, 1);
    if (thislen < 0) return thislen; else pos += thislen;
    if (msg_hash != getHash()) return -1;

    thislen = this->_decodeNoHash(buf, offset + pos, maxlen - pos);
    if (thislen < 0) return thislen; else pos += thislen;

    return pos;
}

int TrafficSignElement_t::getEncodedSize() const
{
    return 8 + _getEncodedSizeNoHash();
}

int64_t TrafficSignElement_t::getHash()
{
    static int64_t hash = static_cast<int64_t>(_computeHash(NULL));
    return hash;
}

const char* TrafficSignElement_t::getTypeName()
{
    return "TrafficSignElement_t";
}

int TrafficSignElement_t::_encodeNoHash(void *buf, int offset, int maxlen) const
{
    int pos = 0, tlen;

    tlen = __byte_encode_array(buf, offset + pos, maxlen - pos, &this->sampleType, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_encode_array(buf, offset + pos, maxlen - pos, &this->eShape, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_encode_array(buf, offset + pos, maxlen - pos, &this->eColor, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_encode_array(buf, offset + pos, maxlen - pos, &this->sPointNum, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_encode_array(buf, offset + pos, maxlen - pos, &this->eKeepOut, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    for (int a0 = 0; a0 < 5; a0++) {
        tlen = this->objpPointPts[a0]._encodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    for (int a0 = 0; a0 < 2; a0++) {
        tlen = this->objTextPts[a0]._encodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __byte_encode_array(buf, offset + pos, maxlen - pos, &this->ucDrawMode, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_encode_array(buf, offset + pos, maxlen - pos, &this->ucMinFlag, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->objMETGPSInfo_Lcm._encodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int TrafficSignElement_t::_decodeNoHash(const void *buf, int offset, int maxlen)
{
    int pos = 0, tlen;

    tlen = __byte_decode_array(buf, offset + pos, maxlen - pos, &this->sampleType, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_decode_array(buf, offset + pos, maxlen - pos, &this->eShape, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_decode_array(buf, offset + pos, maxlen - pos, &this->eColor, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_decode_array(buf, offset + pos, maxlen - pos, &this->sPointNum, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_decode_array(buf, offset + pos, maxlen - pos, &this->eKeepOut, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    for (int a0 = 0; a0 < 5; a0++) {
        tlen = this->objpPointPts[a0]._decodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    for (int a0 = 0; a0 < 2; a0++) {
        tlen = this->objTextPts[a0]._decodeNoHash(buf, offset + pos, maxlen - pos);
        if(tlen < 0) return tlen; else pos += tlen;
    }

    tlen = __byte_decode_array(buf, offset + pos, maxlen - pos, &this->ucDrawMode, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = __byte_decode_array(buf, offset + pos, maxlen - pos, &this->ucMinFlag, 1);
    if(tlen < 0) return tlen; else pos += tlen;

    tlen = this->objMETGPSInfo_Lcm._decodeNoHash(buf, offset + pos, maxlen - pos);
    if(tlen < 0) return tlen; else pos += tlen;

    return pos;
}

int TrafficSignElement_t::_getEncodedSizeNoHash() const
{
    int enc_size = 0;
    enc_size += __byte_encoded_array_size(NULL, 1);
    enc_size += __byte_encoded_array_size(NULL, 1);
    enc_size += __byte_encoded_array_size(NULL, 1);
    enc_size += __byte_encoded_array_size(NULL, 1);
    enc_size += __byte_encoded_array_size(NULL, 1);
    for (int a0 = 0; a0 < 5; a0++) {
        enc_size += this->objpPointPts[a0]._getEncodedSizeNoHash();
    }
    for (int a0 = 0; a0 < 2; a0++) {
        enc_size += this->objTextPts[a0]._getEncodedSizeNoHash();
    }
    enc_size += __byte_encoded_array_size(NULL, 1);
    enc_size += __byte_encoded_array_size(NULL, 1);
    enc_size += this->objMETGPSInfo_Lcm._getEncodedSizeNoHash();
    return enc_size;
}

uint64_t TrafficSignElement_t::_computeHash(const __lcm_hash_ptr *p)
{
    const __lcm_hash_ptr *fp;
    for(fp = p; fp != NULL; fp = fp->parent)
        if(fp->v == TrafficSignElement_t::getHash)
            return 0;
    const __lcm_hash_ptr cp = { p, TrafficSignElement_t::getHash };

    uint64_t hash = 0xab7475bb4fbbd002LL +
         Point_t::_computeHash(&cp) +
         Point_t::_computeHash(&cp) +
         METGPSInfo_Lcm::_computeHash(&cp);

    return (hash<<1) + ((hash>>63)&1);
}

#endif