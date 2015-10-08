#ifndef _CORE_H
#define _CORE_H

#include "crc.h"
#include <stdio.h>
#include <regex>
#include <sstream>
#include <iomanip>
#include <vector>
using namespace std;

class EthernetFrame
{
public:
    //传入帧的各个部分
    int fillframe(string sourcemac, string desmac, string data, string seedstring);
    //二进制字符串转十六进制字符串
    string binarystrtohex(string data);
    //十六进制字符串转二进制字符串
    string hexstrtobinary(string data);

    /** 结果数据是否合法
     *
     * @param sourcemac 源MAC地址
     * @param desmac 目的MAC地址
     * @param data 数据部分
     * @param seedstring 生成多项式
     * @return int 其中每一位对应一个参数,0为正确,1为错误
     *
     */
    int checkdata(string sourcemac, string desmac, string data, string seedstring);
    vector<string>* getcrcresults();
    string getcrcdata();
private:
    crcgenerater crc;
    string crcdata;
};

#endif // !_CORE_H

