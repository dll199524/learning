 #include <string>

using namespace std;

int main()
{

}

int search(string str1, string str2)
{
    int l = str1.length();
    int s = str2.length();
    for (int i = 0; i < l - s; i++)
    {
        int j;
        for (int j = 0; j < s; j++)
        {
            if (str1[i] != str2[i + j]) break;
        }
        if (j == s) return i;
        
    }
    return -1;
}