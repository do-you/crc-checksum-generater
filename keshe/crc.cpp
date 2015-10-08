#include "crc.h"
#include <regex>
#include <sstream>
#include <array>


crcgenerater::crcgenerater()
{
    results = new vector<string>();
}

crcgenerater::~crcgenerater()
{
    delete results;
}

bool crcgenerater::crc8(string val, string seed)
{
    results->clear();
	
    val += string(seed.size() - 1, '0');//在末尾添加R个零
    if (!val.empty())
    {
        int i;
        for (i = 0; i < val.size()-seed.size()+1 ; i++)
        {

            if (val[i] == '0')
                continue;
            else
            {
				storage(string(val.begin() + i, val.begin() + i + seed.size()), i);//保存每一步的结果
				storage(seed, i);//保存每一步的结果
				//将生成多项式（二进制数）对信息码做除(异或)
                for (int j = 0; j < seed.size(); j++)
                    val[i + j] = val[i + j] == seed[j] ? '0' : '1';
            }
        }
        storage(string(val.end() - seed.size() + 1, val.end()),i);//保存最后的结果
        return true;
    }
    else
        return false;
}

vector<string>* crcgenerater::getresults()
{
    return results;
}

std::string crcgenerater::seedstr2seed(string seedstring)
{
    regex r;
    smatch results;
	string pattern = "[01]{2,33}";//生成多项式(二进制数)格式检测
	string pattern1 = "([xX]\\d*\\+)+1";//生成多项式格式检测
	string pattern2 = "[xX](\\d*)\\+";//搜索其中每一个项
    array<char, 33> result ;//用来保存二进制数
    for (char &x : result) x = '0';
    result[0] = '1';
    int maxpower=0, prepower=33;//maxpower为幂的最大值,prepower为前一个幂

    r = pattern;
    if (regex_match(seedstring, r))//检查多项式是否已经是二进制形式
        return seedstring;

    r = pattern1;
    if (regex_match(seedstring, r))//检查多项式的格式
    {
        r = pattern2;
        for (sregex_iterator it(seedstring.begin(), seedstring.end(), r), end_it; it != end_it; ++it)
        {
            string x = (*it)[1];
            int power = x.empty() ? 1 : stoi(x);
            maxpower = maxpower > power ? maxpower : power;
			if (power != 0 && power <= 32)//检查多项式的语法
                result[power] = '1';
            else
                return string();
        }
        decltype(result.rbegin()) begin(result.begin() + maxpower+1), end(result.begin());
        return string(begin, end);
    }
    return string();
}

int crcgenerater::checkseedstr(string seedstring)
{
    return seedstr2seed(seedstring).size();
}

void crcgenerater::storage(string val,int i)
{
    string temp(i, ' ');
    results->push_back(temp + val);
}
