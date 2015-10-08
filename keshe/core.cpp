#include "core.h"
#include <WinSock2.h>

int EthernetFrame::fillframe(string sourcemac, string desmac, string data, string seedstring)
{
    crcdata.clear();

    int checkresult;
    if (!(checkresult=checkdata(sourcemac, desmac, data, seedstring)))
    {
        ostringstream len,llc;
		//长度字段,将长度转换成网络字节序在转换成01格式
        short temp = data.size() / 8;
        temp = htons(temp);
        len << bitset<16>(temp);
		//填充字段
        llc << std::setw(368) << std::left << std::setfill('0') << data;
		//整个要生成crc校验码的字段
        crcdata = hexstrtobinary(desmac) + hexstrtobinary(sourcemac) + len.str() +llc.str();
        crc.crc8(crcdata,crcgenerater::seedstr2seed(seedstring));
    }
    return checkresult;
}

std::string EthernetFrame::binarystrtohex(string data)
{
    ostringstream result;
    for (auto x = data.begin(); x != data.end();)
    {
        if (*x++ == '0')
            if (*x++ == '0')
                if (*x++ == '0')
                    if (*x++ == '0')
                        result << '0';
                    else
                        result << '1';
                else if (*x++ == '0')
                    result << '2';
                else
                    result << '3';
            else if (*x++ == '0')
                if (*x++ == '0')
                    result << '4';
                else
                    result << '5';
            else if (*x++ == '0')
                result << '6';
            else
                result << '7';
        else if (*x++ == '0')
            if (*x++ == '0')
                if (*x++ == '0')
                    result << '8';
                else
                    result << '9';
            else if (*x++ == '0')
                result << 'A';
            else
                result << 'B';
        else if (*x++ == '0')
            if (*x++ == '0')
                result << 'C';
            else
                result << 'D';
        else if (*x++ == '0')
            result << 'E';
        else
            result << 'F';
    }
    return result.str();
}

std::string EthernetFrame::hexstrtobinary(string data)
{
    ostringstream result;
    string map[] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "", "", "", "", "", "", "", "1010", "1011", "1100", "1101", "1110", "1111" };
    for (auto x : data)
        result << map[x - 48];
    return result.str();
}

int EthernetFrame::checkdata(string sourcemac, string desmac, string data, string seedstring)
{
    regex r;
    smatch results;
    int returnvalue = 0;
	string pattern1 = "[0-9A-F]{12}",pattern2="([01]{8}){0,1500}";

    r = pattern1;
    if (!regex_match(sourcemac, results, r))
        returnvalue |= 1;
    if (!regex_match(desmac, results, r))
        returnvalue |= 2;

    r = pattern2;
    if (!regex_match(data, results, r))
        returnvalue |= 4;

    if (!crcgenerater::checkseedstr(seedstring))
        returnvalue |= 8;

    return returnvalue;
}

vector<string>* EthernetFrame::getcrcresults()
{
    return crc.getresults();
}


std::string EthernetFrame::getcrcdata()
{
    return crcdata;
}
