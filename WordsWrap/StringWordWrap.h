
#ifndef STRINGWORDWRAP_H
#define STRINGWORDWRAP_H


#include <string>
#include <vector>

using namespace std;

/**
 * @class StringWordWrap
 * @brief break string according to the specified number of characters
 * @authur lyman_li
 * @modify histories
 *      2014/05/06---new file---lyman_li
 */
class StringWordWrap
{
public:
    enum swwReturnType{
        swwReturn_Only_One_Word = -2,
        swwReturn_Input_Param_Vaild = -1,
        swwReturn_Success = 0,
    };

    StringWordWrap(const char * str);
    ~StringWordWrap();
    /**
     * @brief StartWrap break string
     * @param width the specific number of characters
     * @return if sucess,return 0,otherwise no zero
     */
    int StartWrap(unsigned int width, string &txt);


private:
    string m_strTxt;
    unsigned int lineWidth;
    vector<string> vcWords;
    /**
     * @brief CountCharNumOfWord count characters number of every words
     * @param vcChNums save characters number,out param
     * @return if sucess,return 0,otherwise no zero
     */
    int CountCharNumOfWord(vector<unsigned int> &vcChNums);

    /**
     * @brief SolveWordWrap break string
     * @param vcChNums save characters number,input param
     * @param txt out string with endline
     * @return if sucess,return 0,otherwise no zero
     */
    int SolveWordWrap(const vector<unsigned int> & vcChNums, string &txt);


    /**
     * @brief getString get out string with endline according to the p
     * @param p is used to get string
     * @param txt out string with endline
     * @return
     */
    int getString(const vector<int> &p, int n, string & txt);
};

#endif // STRINGWORDWRAP_H
