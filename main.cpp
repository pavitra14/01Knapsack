#include <iostream>
#include <chrono>
#include <cstring>

using namespace std::chrono;
using namespace std;
#define N_BOUND 10000
#define W_BOUND 10000

// A utility function that returns 
// maximum of two integers 
int max(int a, int b) { return (a > b) ? a : b; } 

// Matrix required for memoization
int t[N_BOUND+1][W_BOUND+1];

int recursive_knapsack(int* wt, int* val, int w, int n)
{
  // Base Condition: Think of the least possible valid input
  if(n == 0 || w == 0)
  {
    return 0;
  }
  // Code for choice diagram
  // if item wt is less than max weight W
  if(wt[n-1] <= w)
  {
    // Return the max profit when including this item and not including this item
    return max(val[n-1] + recursive_knapsack(wt, val, w - wt[n-1], n-1), recursive_knapsack(wt, val, w, n-1));
  }
  else if(wt[n-1]>w)
  {
    // Condition when the item doesn't fit inside the box
    return recursive_knapsack(wt, val, w, n-1);
  }
  return 0;
}
int memoization_knapsack(int* wt, int* val, int w, int n)
{
  // Base Condition: Think of the least possible valid input
  if(n == 0 || w == 0)
  {
    return 0;
  }
  // Check if value exist in memoized matrix - DP
  if(t[n][w] != -1)
  {
    return t[n][w];
  }

  // Code for choice diagram
  // if item wt is less than max weight W
  if(wt[n-1] <= w)
  {
    // Return the max profit when including this item and not including this item
    // Fill t[n][w]
    return t[n][w] = max(val[n-1] + memoization_knapsack(wt, val, w - wt[n-1], n-1), memoization_knapsack(wt, val, w, n-1));
  }
  else if(wt[n-1]>w)
  {
    // Condition when the item doesn't fit inside the box
    // Fill t[n][W]
    return t[n][w] = memoization_knapsack(wt, val, w, n-1);
  }
  return 0;
}

int topdown_knapsack(int* wt, int* val, int w, int n)
{
  // Top Down Matrix of N+1 and W+1
  // 2D Dynamic Memory Allocation
  // Refer https://www.geeksforgeeks.org/dynamically-allocate-2d-array-c/
  int **td = (int **)malloc((n+1) * sizeof(int *));
  for (int i=0; i<n+1; i++)
    td[i] = (int *)malloc((w+1) * sizeof(int)); 

  // Initialisation
  // Recursion Base Condition -> Top Down Initialisation
  for(auto i=0;i<n+1;i++) {
    for(auto j=0;j<n+1;j++)
    {
      if(i == 0 || j == 0)
      {
        td[i][j]=0;
      }
    }
  }

  // Start solving all sub problems, using the result from the problem before that.
  for(int i=1;i<n+1;i++)
  {
    for(int j=1; j<n+1; j++)
    {
      // Choice diagram
      // Replace n with i 
      // Replace w with j
      if(wt[i-1]<=w)
      {
        td[i][j] = max(
          val[i-1] + td[i-1][j-wt[i-1]],
          td[i-1][j]
        );
      } else {
        td[i][j] = td[i-1][j];
      }
    }
  }

  // Return the final result, the required result
  // Obtained from solving all previous sub problems
  return td[n][w];
}

int main() {
  int n;
  int *wt = NULL, *val = NULL;
  int w;
  cin>>n;
  cin>>w;
  wt = (int*)malloc(sizeof(int) * n);
  val = (int*)malloc(sizeof(int) * n);
  for(auto i = 0; i<n; i++)
  {
    cin>>wt[i];
  }
  for(auto i = 0; i<n; i++)
  {
    cin>>val[i];
  }

  // Set all values of matrix as -1
  // #include <cstring>
  memset(t,-1,sizeof(t));

  // Run the Recursive Knapsack Solution and get the Solution
  auto start = high_resolution_clock::now();
  int recursive_profit = recursive_knapsack(wt, val, w, n); 
  auto stop = high_resolution_clock::now(); 
  auto duration_nano = duration_cast<nanoseconds>(stop - start); 
  auto duration_micro = duration_cast<microseconds>(stop - start);
  auto duration = duration_cast<seconds>(stop - start); 
  cout<<"Recursive Knapsack:"<<endl;
  cout<<"\t Profit: "<<recursive_profit<<endl;
  cout<<"\t Duration: "<<endl;
  cout<<"\t\t nanoseconds: "<<duration_nano.count()<<endl;
  cout<<"\t\t microseconds: "<<duration_micro.count()<<endl;
  cout<<"\t\t seconds: "<<duration.count()<<endl;



  // Run the Memoization DP Knapsack Solution and get the Solution
  auto start2 = high_resolution_clock::now();
  int recursive_profit2 = memoization_knapsack(wt, val, w, n); 
  auto stop2 = high_resolution_clock::now(); 
  auto duration_nano2 = duration_cast<nanoseconds>(stop2 - start2); 
  auto duration_micro2 = duration_cast<microseconds>(stop2 - start2);
  auto duration2 = duration_cast<seconds>(stop2 - start2); 
  cout<<"Memoization Knapsack:"<<endl;
  cout<<"\t Profit: "<<recursive_profit2<<endl;
  cout<<"\t Duration: "<<endl;
  cout<<"\t\t nanoseconds: "<<duration_nano2.count()<<endl;
  cout<<"\t\t microseconds: "<<duration_micro2.count()<<endl;
  cout<<"\t\t seconds: "<<duration2.count()<<endl;

  // Run the Top Down DP Knapsack Solution
  auto start3 = high_resolution_clock::now();
  int topdown_profit = topdown_knapsack(wt, val, w, n);
  auto stop3 = high_resolution_clock::now();
  auto duration_nano3 = duration_cast<nanoseconds>(stop3-start3);
  auto duration_micro3 = duration_cast<microseconds>(stop3-start3);
  auto duration3 = duration_cast<seconds>(stop3-start3);
  cout<<"Top down Knapsack:"<<endl;
  cout<<"\t Profit: "<<topdown_profit<<endl;
  cout<<"\t Duration: "<<endl;
  cout<<"\t\t nanoseconds: "<<duration_nano3.count()<<endl;
  cout<<"\t\t microseconds: "<<duration_micro3.count()<<endl;
  cout<<"\t\t seconds: "<<duration3.count()<<endl;
  
  return 0;
}
