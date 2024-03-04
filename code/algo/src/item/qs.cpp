#include <vector>
#include <qs.h>

void quicks::quicksort(std::vector<int>& vec, int left, int right){
    int cleft = left, cright = right;
    int pivor = vec[left];
    if(left < right){
        while(left < right){
            while(vec[left] <= pivor && left < cright) left++;
            while(vec[right] >= pivor && cleft < right) right--;
            if(left < right) std::swap(vec[left],vec[right]);
        }
        std::swap(vec[right],vec[cleft]);
        quicksort(vec,cleft,right-1);
        quicksort(vec,right+1,cright);

    }
}
