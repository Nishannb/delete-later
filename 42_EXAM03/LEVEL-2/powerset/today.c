#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_int(char **str, int ac)
{
    int j = 1;
    while (j < ac)
    {
        int i = 0;
        if (str[j][i] == '-' || str[j][i] == '+')
            i++;
        while (str[j][i])
        {
            if (str[j][i] < '0' || str[j][i] > '9')
                return 0;
            i++;
        }
        j++;
    }
    return 1;
}

void solve(int *nums, int target, int *subset, int len, int nums_index, int sub_index, int sum)
{
    if (nums_index == len){
        if (target == sum) {
            for (int i = 0; i < sub_index; i++){
                printf("%d", subset[i]);
                if (i != sub_index - 1){
                    printf(" ");
                }
            }
            printf("\n");
        }
        return;
    }
    solve(nums, target, subset, len, nums_index + 1, sub_index, sum);
    subset[sub_index] = nums[nums_index];
    solve(nums, target, subset, len, nums_index+ 1, sub_index + 1, sum + nums[nums_index]);
}

int main(int ac, char ** av){
    if (ac > 3 || check_int(av, ac)){
        int target = atoi(av[1]);
        int *nums = malloc(sizeof(int) * (ac -2));
        for (int i = 0; i < (ac -2); i++){
            nums[i] = atoi(av[i + 2]);
        }
        int subset[(ac-2)];
        int sum = 0;
        int sub_index = 0;
        int nums_index = 0;
        int len = ac - 2;
        solve(nums, target, subset, len, nums_index, sub_index, sum);
        free(nums);
        return 0;
    }
    return 1;
}