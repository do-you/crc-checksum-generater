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
    //����֡�ĸ�������
    int fillframe(string sourcemac, string desmac, string data, string seedstring);
    //�������ַ���תʮ�������ַ���
    string binarystrtohex(string data);
    //ʮ�������ַ���ת�������ַ���
    string hexstrtobinary(string data);

    /** ��������Ƿ�Ϸ�
     *
     * @param sourcemac ԴMAC��ַ
     * @param desmac Ŀ��MAC��ַ
     * @param data ���ݲ���
     * @param seedstring ���ɶ���ʽ
     * @return int ����ÿһλ��Ӧһ������,0Ϊ��ȷ,1Ϊ����
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

