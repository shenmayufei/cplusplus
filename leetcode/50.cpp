/* 50. Pow(x, n)

Implement pow(x, n).

Do not consider overflow and underflow
If n == 0, return 1;
*/

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 0) {
            return 1;
        } else if (n==1) {
            return x;
        } else if (n==-1) {
            return 1/x;
        }
        if (x ==0) return 0;

        double ret = 0;
        if (n%2==0) {
            ret = myPow(x, n/2);
            ret *= ret;
        } else if (n%2==-1) {
            ret = myPow(x, (n-1)/2);
            ret *= ret;
            ret *= x;
        } else {
            ret = myPow(x, n/2);
            ret *= ret;
            ret *= x;
        }
        return ret;
    }
};