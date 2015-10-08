#ifndef _CRC_H
#define _CRC_H

#include <vector>
#include <string>
#include <bitset>
#include <iostream>
using namespace std;
class crcgenerater
{
public:
    crcgenerater();
    ~crcgenerater();

    /**crc校验码生成
    *
    * @param val 待生成校验码的数据,01格式
    * @param seed 生成多项式,01格式
    * @return bool 成功返回true，失败返回false
    *
    */
    bool crc8(string val, string seed = "100000111");
    vector<string>* getresults();

    /** 多项式的表达式转换成01格式
    *
    * @param 多项式 例:x8+x2+x+1
    * @return 多项式的01格式,失败返回空字符串
    *
    */
    static string seedstr2seed(string seedstring);
    static int checkseedstr(string seedstring);
private:
    //储存每一步的结果
    void storage(string val, int i);
    //结果集
    vector<string>* results;

};
#endif
