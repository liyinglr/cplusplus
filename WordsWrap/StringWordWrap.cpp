#include "StringWordWrap.h"

#include <limits.h>
#include <iostream>

StringWordWrap::StringWordWrap(const char *str)
{
    m_strTxt = "";
    m_strTxt = string(str);
    lineWidth = 0;
}

StringWordWrap::~StringWordWrap()
{
    vcWords.clear();
}

int StringWordWrap::StartWrap(unsigned int width,string & txt)
{
    if(m_strTxt.empty() || width == 0)
        return swwReturn_Input_Param_Vaild;

    lineWidth = width;

    int nres = swwReturn_Success;

    //1 count char numbers of word
    vector<unsigned int> vcChNums;
    vcWords.clear();
    nres = CountCharNumOfWord(vcChNums);
    if(nres != swwReturn_Success)
        return nres;

    if(vcWords.size() == 0)
        return swwReturn_Input_Param_Vaild;

    //word wrap
    nres = SolveWordWrap(vcChNums,txt);

    vcChNums.clear();

    return nres;
}

int StringWordWrap::CountCharNumOfWord(vector<unsigned int> &vcChNums)
{
    if(m_strTxt.empty())
        return swwReturn_Input_Param_Vaild;

    if(m_strTxt[m_strTxt.size() - 1] != ' '){
        m_strTxt += " ";
    }
    int prevPos = 0;
    int pos = m_strTxt.find(" ",prevPos);
    if(pos == -1)
        return swwReturn_Only_One_Word;

    const int punctuareNum = 5;
    string  punctuare [punctuareNum]= {",",".",";","?","!"};

    string subTmp;
    while(pos != -1){
        subTmp = m_strTxt.substr(prevPos,pos-prevPos);

        //find punctuare
        int punPos = -1;
        for(int i=0;i<punctuareNum;i++){
            punPos = subTmp.find(punctuare[i]);
            if(punPos != -1){
                break;
            }
        }

        if(punPos == -1){
            vcChNums.push_back(subTmp.size());
            vcWords.push_back(subTmp);
        }
        else{
            vcChNums.push_back(punPos+1);
            vcChNums.push_back(subTmp.size() - punPos-1);

            vcWords.push_back(subTmp.substr(0,punPos+1));
            vcWords.push_back(subTmp.substr(punPos+1,subTmp.size() - punPos));
        }

        prevPos = pos+1;
        pos = m_strTxt.find(" ",prevPos);
    }

    for(int i=0;i<vcWords.size();i++){
        cout<<vcChNums[i]<<"    "<<vcWords[i]<<endl;
    }
    return swwReturn_Success;
}


int StringWordWrap::SolveWordWrap(const vector<unsigned int> &vcChNums,string & txt)
{
    if(vcChNums.size() == 0 || lineWidth == 0 ||vcWords.size() == 0)
        return swwReturn_Input_Param_Vaild;

    unsigned int wordCnt = vcChNums.size();

    //vcExtraSpaces[i][j]表示如果把从第i到j个单词放在一行中，这行还剩余的空格数
    vector<vector<int> > vcExtraSpaces(wordCnt+1,vector<int> (wordCnt+1));
//    /*vcExtraSpaces*/.clear();

    //vcLineCost[i][j]表示如果把从第i到j个单词放在一行中,那么这行的惩罚函数的值是多少，lineCost = extraSpaces*extraSpaces
    vector<vector<int> >vcLineCost(wordCnt+1,vector<int> (wordCnt+1));
//    /*vcLineCost*/.clear();

    //vcTotalCost[i]表示安排第一到第i个单词所耗费
    vector<int> vcTotalCost(wordCnt + 1);
//    vcTotalCost.clear();

    //p[] is used to print solution
    vector<int> p(wordCnt+1);

    unsigned int i,j;

    //calculate extra spaces in asingle ine
    for(i=1;i<vcExtraSpaces.size();i++){
        vcExtraSpaces[i][i] = lineWidth - vcChNums[i-1];
        for(j = i+1;j< vcExtraSpaces.at(i).size();j++)
            vcExtraSpaces[i][j] = vcExtraSpaces[i][j-1] - vcChNums[j-1] - 1;
    }

    // Calculate line cost corresponding to the above calculated extra
    // spaces. The value lc[i][j] indicates cost of putting words from
    // word number i to j in a single line
    for(i=1;i<vcLineCost.size();i++){
        for(j=1;j<vcLineCost.at(i).size();j++){
            if(vcExtraSpaces[i][j] < 0)
                vcLineCost[i][j] = INT_MAX;
            else if(j == wordCnt && vcExtraSpaces[i][j] >= 0)
                vcLineCost[i][j] = 0;
            else
                vcLineCost[i][j] = vcExtraSpaces[i][j] * vcExtraSpaces[i][j];
        }
    }

    // Calculate minimum cost and find minimum cost arrangement.
    //  The value c[j] indicates optimized cost to arrange words
    // from word number 1 to j.
    vcTotalCost[0] = 0;
    for (j = 1; j < vcTotalCost.size(); j++)
    {
        vcTotalCost[j] = INT_MAX;
        for (i = 1; i <= j; i++)
        {
            if (vcTotalCost[i-1] != INT_MAX &&
                vcLineCost[i][j] != INT_MAX &&
                (vcTotalCost[i-1] + vcLineCost[i][j] < vcTotalCost[j])
               )
            {
                vcTotalCost[j] = vcTotalCost[i-1] + vcLineCost[i][j];
                p[j] = i;
            }
        }
    }

    //get out string
    getString(p,p.size()-1,txt);

    //release cource
    for(i=0;i<vcExtraSpaces.size();i++){
        vcExtraSpaces.at(i).clear();
        vcLineCost.at(i).clear();
    }
    vcExtraSpaces.clear();
    vcLineCost.clear();
    vcTotalCost.clear();
    p.clear();

    return swwReturn_Success;
}

int StringWordWrap::getString(const vector<int> &p, int n,string &txt)
{
    int k;
    if (p[n] == 1)
        k = 1;
    else
        k = getString(p, p[n]-1,txt) + 1;
    printf ("Line number %d: From word no. %d to %d \n", k, p[n], n);
    for(int i=p[n];i<=n;i++){
        txt += vcWords[i-1];
        txt += " ";
    }
    txt += "\n";
    return k;
}



