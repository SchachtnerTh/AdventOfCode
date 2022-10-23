/*
 * =====================================================================================
 *
 *       Filename:  16.cpp
 *
 *    Description: Advent of Code 2021, day 16 
 *
 *        Version:  1.0
 *        Created:  10/21/2022 04:30:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <list>

using namespace std;

char *hexstr, *bitstr;
int hexlen, bitlen;
int sumVersions=0;

void readString(const char *file)
{
    FILE *f;
    size_t filesize;
    f = fopen(file, "r");
    fseek(f, 0L, SEEK_END);
    filesize = ftell(f);
    fseek(f, 0L, SEEK_SET);

    cout << "Input file size: " << filesize << endl;
    hexstr = new char[filesize + 1];
    bitstr = new char[filesize * 4 + 1];

    fgets(hexstr, filesize, f);
    hexlen = strlen(hexstr);
    bitlen = strlen(bitstr);
    hexstr[filesize] = 0;
    bitstr[filesize * 4] = 0;

    cout << "Der String " << hexstr << " hat die Länge " << hexlen << endl;

    for (int i=0; i < hexlen; i++)
    {
        char digit;
        if (hexstr[i] >= '0' && hexstr[i] <= '9') digit = hexstr[i] - '0';
        if (hexstr[i] >= 'A' && hexstr[i] <= 'F') digit = hexstr[i] - 'A' + 10;
        if (hexstr[i] >= 'a' && hexstr[i] <= 'f') digit = hexstr[i] - 'a' + 10;
        for (int bit=0; bit < 4; bit++)
        {
            bitstr[4 * i + bit] = ((digit & (1 << (3 - bit))) >> (3 - bit)) + '0';
        }
//        bitstr[4 * i + 0] = ((digit & (1 << 3)) >> 3) + '0';
//        bitstr[4 * i + 1] = ((digit & (1 << 2)) >> 2) + '0';
//        bitstr[4 * i + 2] = ((digit & (1 << 1)) >> 1) + '0';
//        bitstr[4 * i + 3] = ((digit & (1 << 0)) >> 0) + '0';
    }
    fclose(f);
}

class Packet
{
    public:
    int version;
    int typeID;
    long length;
    char *data;
    static Packet *Generate(char *packet);
};

int getNumber(const char *packet, int bits)
{
    int number = 0;
    for (int i=0; i < bits; i++)
    {
        number += packet[i] - '0' << (bits - i - 1);
    }
    return number;
}

class LiteralPacket : public Packet
{
    public:
    LiteralPacket(int version, int typeId, char *packet);
    int value;
    int paddingBits;
    void getValue();
};

class OperatorPacket : public Packet
{
    public:
        OperatorPacket();
        int lengthType;
        int net_length; // without padding, "length" ist full length including padding
        int data_length; // only the data, without headers or padding
        int numSubPackets;
        list<Packet *> packets;
};

OperatorPacket::OperatorPacket()
{
    //packets = new list<Packet *>;
}

void LiteralPacket::getValue()
{
    value = 0;
    // cout << "in getValue()" << endl;
    int remainingBits = strlen(data);
    // cout << "remaining Bytes" << remainingBits << endl;
    bool cont = false;
    int digit_group = 0;
    char *boolVal = new char[remainingBits + 1];
    do
    {
        int grp = getNumber(data + (5 * digit_group), 5);
        value += (grp & 15);
        if (grp & 16) 
        {
            cont = true; 
            digit_group++;
            value <<= 4;
        }
        else cont = false;
        cout << "grp:   " << (grp & 15) << endl;
    }
    while (cont);
    length = (digit_group + 1) * 5 + 6;
    //paddingBits = remainingBits - length;
    // length = remainingBits + 6;
    cout << "Value: " << value << endl << endl;
}

LiteralPacket::LiteralPacket(int version, int typeId, char *packet)
{
    this->version = version;
    this->typeID = typeId;
    int packetLength = strlen(packet);
    data = new char[packetLength + 1];
    data[packetLength] = 0;
    strncpy(data, packet, packetLength);
    cout << "Literal packet: Version: " << version << endl;
    cout << data << endl;
    getValue(); // read literal value from packet
}

Packet *Packet::Generate(char *packet)
{
    int packetLength = strlen(packet);
    int version, typeId;
    int packetPointer = 0;
    version = (packet[0] - '0' << 2) + (packet[1] - '0' << 1) + (packet[2] - '0');
    typeId = (packet[3] - '0' << 2) + (packet[4] - '0' << 1) + (packet[5] - '0');
 
    int v, t;
    v = getNumber(packet, 3);
    t = getNumber(packet + 3, 3);
    sumVersions += v;
    if (typeId == 4) {
        LiteralPacket *lp = new LiteralPacket(v, t, packet + 6 + packetPointer);
        packetPointer += lp->length;
        return lp;
    }
    else
    {
        // We have an operator packet
        if (packet[6] == '0')
        {
            OperatorPacket *op = new OperatorPacket();
            op->version = v;
            op->typeID = t;
            // op->length = packetLength;
            op->lengthType = 0;
            // next 15 bits are the total length of all sub packets in this packet
            int total_length;
            total_length = getNumber(packet + 7, 15);
            op->net_length = total_length + 7;
            op->data_length = total_length;
            op->length = total_length + 7 + 15; // Länge des Operator-Pakets, vorerst ohne die Sub-Pakete
            cout << "Operator packet: Version: " << v << ", Total length of all sub packets: " << total_length << endl;
            int packets = 0;
            while(packetPointer < total_length)
            {
                packets++;
                Packet *p = Packet::Generate(packet + 7 + 15 + packetPointer);
                packetPointer += p->length;
                // op->length += p->length; // Addiere die Länge des Sub-Pakets zur Länge des zugehörigen Operator-Pakets
                op->packets.push_back(p);
            }
            op->numSubPackets = packets;
            return op;
        }
        else
        {
            OperatorPacket *op = new OperatorPacket();
            op->version = v;
            op->typeID = t;
            op->length = 7 + 11;
            op->lengthType = 1;
            // next 11 bits are the number of sub packets in this packet
            int num_packets;
            num_packets = getNumber(packet + 7, 11);
            op->numSubPackets = num_packets;
            cout << "Operator packet: Version: " << v << ", Total cout of all sub packets: " << num_packets << endl;
            int packetPointer = 0;
            for (int i = 0; i < num_packets; i++)
            {
                Packet *p = Packet::Generate(packet + 7 + 11 + packetPointer);
                packetPointer += p->length;
                op->length += p->length; // Addiere die Länge des Sub-Pakets zur Länge des zugehörigen Operator-Pakets
                op->packets.push_back(p);
            }
            op->net_length = packetPointer + 7;
            op->data_length = packetPointer;
            return op;
        }
    }
}

void parsePacket(char *packet)
{
}

int main(int argc, char **argv)
{
    if (argc != 2)
    { 
        cout << "Input-Dateiname angeben!" << endl;
        return -1;
    }

    readString(argv[1]);
    cout << "Bit string: " << bitstr << endl;
    Packet *p = Packet::Generate(bitstr);
    cout << "Sum of versions: " << sumVersions << endl;
}
